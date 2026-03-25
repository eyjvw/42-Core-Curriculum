import { newGameController, hitController, standController, doubleController, getGameController } from "./controllers/blackjack.ts";
import { createRoomController, joinRoomController, listRoomsController, getRoomController, startGameController, getRoomGameStateController, getMyRoomController, kickPlayerController, leaveRoomController, placeBetController, dealCardsController, gameHitController, gameStandController, gameDoubleController, newRoundController, addBotController, serializeRoom } from "./controllers/multiplayer.ts";
import { StatusCode }			from "./types/status_code.ts";
import { wsManager }			from "./services/websocketManager.ts";
import { roomManager }			from "./services/roomManager.ts";
import { getUserIdFromRequest }	from "./jwt/jwt.ts";

const routes: Record<string, (req: Request) => Promise<Response>> = {
	"POST:/api/games/blackjack/new":	newGameController,
	"POST:/api/games/blackjack/hit":	hitController,
	"POST:/api/games/blackjack/stand":	standController,
	"POST:/api/games/blackjack/double":	doubleController,
	"GET:/api/games/blackjack":			getGameController,

	"POST:/api/games/rooms/create":		createRoomController,
	"POST:/api/games/rooms/join":		joinRoomController,
	"POST:/api/games/rooms/leave":		leaveRoomController,
	"POST:/api/games/rooms/kick":		kickPlayerController,
	"GET:/api/games/rooms":				listRoomsController,
	"GET:/api/games/rooms/my-room":		getMyRoomController,
	"GET:/api/games/rooms/get":			getRoomController,
	"POST:/api/games/rooms/start":		startGameController,
	"GET:/api/games/rooms/game-state":	getRoomGameStateController,

	"POST:/api/games/rooms/bet":		placeBetController,
	"POST:/api/games/rooms/deal":		dealCardsController,
	"POST:/api/games/rooms/hit":		gameHitController,
	"POST:/api/games/rooms/stand":		gameStandController,
	"POST:/api/games/rooms/double":		gameDoubleController,
	"POST:/api/games/rooms/new-round":	newRoundController,
	"POST:/api/games/rooms/add-bot":	addBotController,
};

let wsClientCounter = 0;

const server: Bun.Server<undefined> = Bun.serve({
	port: Number(Bun.env.PORT),
	async fetch(req: Request): Promise<Response>
	{
		const url = new URL(req.url);
		const pathname = url.pathname;

		if (pathname === '/ws/game' && req.headers.get('upgrade') === 'websocket')
		{
			const clientId	= `ws_${wsClientCounter++}`;
			const userId	= url.searchParams.get('userId') || '';
			const username	= url.searchParams.get('username') || 'Guest';
			const roomId	= url.searchParams.get('roomId') || '';
			const success	= server.upgrade(req, { data: { clientId, userId, username, roomId }});

			if (success) { return (undefined as any); }
			return (new Response('WebSocket upgrade failed', { status: 400 }));
		}

		const roomWsMatch = pathname.match(/^\/api\/games\/rooms\/([^/]+)\/ws$/);
		if (roomWsMatch && req.headers.get('upgrade') === 'websocket')
		{
			const clientId	= `ws_room_${wsClientCounter++}`;
			const roomId	= roomWsMatch[1];
			const userId	= await getUserIdFromRequest(req);

			if (userId)
			{
				const room = roomManager.getRoom(roomId!);
				if (room && !room.players.has(String(userId)) && !room.spectators.has(String(userId)))
					return (new Response('You are not a member of this room', { status: 403 }));
			}

			const success	= server.upgrade(req, { data: { clientId, roomId, isRoomWs: true, userId: userId ? String(userId) : undefined }});

			if (success) { return (undefined as any); }
			return (new Response('WebSocket upgrade failed', { status: 400 }));
		}

		const handler:	((req: Request) => Promise<Response>) | undefined = routes[`${req.method}:${pathname}`];
		const response:	Response = handler ? await handler(req) : new Response("Not Found", { status: StatusCode.NOT_FOUND });
		const headers:	Headers	= new Headers(response.headers);

		return (new Response(response.body, { status: response.status, statusText: response.statusText, headers }));
	},

	websocket: {
		open(ws: WebSocket) {
			const data = ws.data as { clientId: string; userId?: string; username?: string; roomId: string; isRoomWs?: boolean };
			if (data.isRoomWs)
			{
				wsManager.registerRoomClient(ws, data.clientId, data.roomId);
				if (data.userId)
				{
					roomManager.markPlayerConnected(data.roomId, data.userId);
					const room = roomManager.getRoom(data.roomId);
					if (room) { wsManager.broadcastRoomState(data.roomId, serializeRoom(room)); }
				}
				console.log(`[WS] Room client ${data.clientId} connected to room ${data.roomId}`);
			}
			else
			{
				wsManager.registerClient(ws, data.clientId, data.userId || '', data.username || 'Guest', data.roomId);
				console.log(`[WS] Client ${data.clientId} connected to room ${data.roomId}`);
			}
		},

		message(ws: WebSocket, message: string | Buffer)
		{
			const data = ws.data as { clientId: string; isRoomWs?: boolean };
			if (typeof message === 'string') { wsManager.handleMessage(data.clientId, message); }
		},

		close(ws: WebSocket)
		{
			const data = ws.data as { clientId: string; userId?: string; roomId: string; isRoomWs?: boolean };
			if (data.isRoomWs)
			{
				wsManager.unregisterRoomClient(ws, data.roomId);
				if (data.userId)
				{
					roomManager.markPlayerDisconnected(data.roomId, data.userId);
					wsManager.broadcastPlayerDisconnected(data.roomId, data.userId);

					const room = roomManager.getRoom(data.roomId);
					if (room) { wsManager.broadcastRoomState(data.roomId, serializeRoom(room)); }

					const rid = data.roomId;
					setTimeout(() => {
						if (roomManager.allHumansDisconnected(rid))
							roomManager.deleteRoom(rid);
					}, 10000);
				}
			}
			else
			{
				wsManager.unregisterClient(data.clientId);
				if (data.userId)
				{
					roomManager.markPlayerDisconnected(data.roomId, data.userId);
					wsManager.broadcastPlayerDisconnected(data.roomId, data.userId);

					const rid = data.roomId;
					setTimeout(() => {
						if (roomManager.allHumansDisconnected(rid))
							roomManager.deleteRoom(rid);
					}, 10000);
				}
			}
			console.log(`[WS] Client ${data.clientId} disconnected`);
		},

		error(ws: WebSocket, error: Error) {
			const data = ws.data as { clientId: string };
			console.error(`[WS] Error on client ${data.clientId}:`, error);
			ws.close();
		},
	},
});

setInterval(() => {
	roomManager.handleDisconnectedPlayers();
	roomManager.cleanupOldRooms();
	roomManager.getAllRooms().forEach((room) => {
		wsManager.broadcastRoomState(room.id, serializeRoom(room));
	});
}, 5000);

process.on("SIGTERM", (): void => {
	server.stop();
	process.exit(0);
});

console.log(`Game service running on ${server.port}`);

import type { RoomMessage }	from '../types/multiplayer.ts';
import { roomManager }		from './roomManager.ts';

interface WSClient
{
	ws:			Bun.ServerWebSocket<unknown>;
	userId:		string;
	username:	string;
	roomId:		string;
}

interface RoomWSClient
{
	ws:		Bun.ServerWebSocket<unknown>;
	roomId:	string;
}

export class WebSocketManager
{
	private clients: Map<string, WSClient>				= new Map();
	private roomWSClients: Map<string, Set<Bun.ServerWebSocket<unknown>>>	= new Map();
	private roomSubscriptions: Map<string, Set<string>>	= new Map();

	registerClient(ws: Bun.ServerWebSocket<unknown>, clientId: string, userId: string, username: string, roomId: string): void
	{
		this.clients.set(clientId, { ws, userId, username, roomId });

		if (!this.roomSubscriptions.has(roomId)) { this.roomSubscriptions.set(roomId, new Set()); }
		this.roomSubscriptions.get(roomId)!.add(clientId);

		this.sendToClient(clientId, {
			type:		'join',
			roomId,
			payload:	{ message: 'Connected to room' },
		});
	}

	unregisterClient(clientId: string): void
	{
		const client = this.clients.get(clientId);
		if (!client) { return; }

		const subscribers = this.roomSubscriptions.get(client.roomId);
		if (subscribers) { subscribers.delete(clientId); }
		if (subscribers && subscribers.size === 0) { this.roomSubscriptions.delete(client.roomId); }

		this.clients.delete(clientId);
	}

	registerRoomClient(ws: Bun.ServerWebSocket<unknown>, clientId: string, roomId: string): void {
		if (!this.roomWSClients.has(roomId)) { this.roomWSClients.set(roomId, new Set()); }
		this.roomWSClients.get(roomId)!.add(ws);
	}

	unregisterRoomClient(ws: Bun.ServerWebSocket<unknown>, roomId: string): void {
		const clients = this.roomWSClients.get(roomId);
		if (clients) { clients.delete(ws); }
		if (clients && clients.size === 0) { this.roomWSClients.delete(roomId); }
	}

	sendToClient(clientId: string, message: RoomMessage): void
	{
		const client = this.clients.get(clientId);
		if (client && client.ws.readyState === WebSocket.OPEN) { client.ws.send(JSON.stringify(message)); }
	}

	broadcastToRoom(roomId: string, message: RoomMessage): void
	{
		const subscribers = this.roomSubscriptions.get(roomId);
		if (!subscribers) { return; }

		subscribers.forEach((clientId) => { this.sendToClient(clientId, message); });
	}

	broadcastGameState(roomId: string, gameState: unknown): void
	{
		this.broadcastToRoom(roomId, {
			type:		'game_state',
			roomId,
			payload:	gameState,
			timestamp:	Date.now(),
		});

		const roomWSClients = this.roomWSClients.get(roomId);
		if (roomWSClients)
		{
			const message = JSON.stringify({
				type:		'game_state',
				payload:	gameState,
			});
			roomWSClients.forEach((ws) => { if (ws.readyState === WebSocket.OPEN) { ws.send(message); }});
		}
	}

	broadcastRoomState(roomId: string, roomState: unknown): void {
		this.broadcastToRoom(roomId, {
			type:		'room_state',
			roomId,
			payload:	roomState,
			timestamp:	Date.now(),
		});

		const roomWSClients = this.roomWSClients.get(roomId);
		if (roomWSClients) {
			const message = JSON.stringify({
				type: 'room-update',
				room: roomState,
				code: (roomState as any).code,
			});
			roomWSClients.forEach((ws) => { if (ws.readyState === WebSocket.OPEN) { ws.send(message); }});
		}
	}

	broadcastKick(roomId: string, kickedUserId: string): void
	{
		const roomWSClients = this.roomWSClients.get(roomId);
		if (roomWSClients)
		{
			const message = JSON.stringify({ type: 'player_kicked', payload: { kickedUserId }});
			roomWSClients.forEach((ws) => { if (ws.readyState === WebSocket.OPEN) { ws.send(message); }});
		}
	}

	broadcastError(roomId: string, error: string): void
	{
		this.broadcastToRoom(roomId, {
			type:		'error',
			roomId,
			payload:	{ error },
			timestamp:	Date.now(),
		});
	}

	broadcastPlayerDisconnected(roomId: string, playerId: string): void
	{
		this.broadcastToRoom(roomId, {
			type:		'player_disconnected',
			roomId,
			playerId,
			payload:	{ message: `Player ${playerId} disconnected` },
			timestamp:	Date.now(),
		});
	}

	getRoomClients(roomId: string): WSClient[]
	{
		const subscribers = this.roomSubscriptions.get(roomId);
		if (!subscribers) { return []; }

		return (Array.from(subscribers)
			.map((clientId) => this.clients.get(clientId))
			.filter((client) => client !== undefined) as WSClient[]);
	}

	handleMessage(clientId: string, messageStr: string): void
	{
		try
		{
			const message: RoomMessage	= JSON.parse(messageStr);
			const client				= this.clients.get(clientId);
			if (!client) { return; }

			if (!message.roomId)
			{
				this.sendToClient(clientId, {
					type:		'error',
					roomId:		'',
					payload:	{ error: 'Missing roomId' },
				});
				return;
			}

			const now	= Date.now();
			const room	= roomManager.getRoom(message.roomId);
			if (room)
			{
				const player = room.players.get(client.userId) || room.spectators.get(client.userId);
				if (player) { roomManager.updatePlayerPing(message.roomId, client.userId); }
			}
		}
		catch (error)
		{
			console.error('WebSocket message parse error:', error);
			this.sendToClient(clientId, {
				type:		'error',
				roomId:		'',
				payload:	{ error: 'Invalid message format' },
			});
		}
	}
}

export const wsManager = new WebSocketManager();

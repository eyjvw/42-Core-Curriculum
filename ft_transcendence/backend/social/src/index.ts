import { StatusCode }				from "./types/status_code.ts";
import { jwtVerify }				from "jose";
import { eq }						from "drizzle-orm";
import * as friendsDB				from "../db/schemas/friends.ts";
import * as messagesDB				from "../db/schemas/messages.ts";
import * as queries					from "../db/schemas/getters.ts";
import { stats }					from "../db/schemas/stats.ts";
import { db }						from "../db/init.ts";

const secret = new TextEncoder().encode(Bun.env.JWT_SECRET || "dev_only");

async function getUidFromRequest(req: Request): Promise<number | null>
{
	try
	{
		const cookie = req.headers.get("cookie");
		if (!cookie) return null;

		const token = cookie.match(/token=([^;]+)/)?.[1];
		if (!token) return null;

		const { payload } = await jwtVerify(token, secret);
		return Number((payload as { uid: string }).uid);
	}
	catch { return null; }
}

function json(data: unknown, status: number = StatusCode.OK): Response
{
	return new Response(JSON.stringify(data), {
		status,
		headers: { "Content-Type": "application/json" }
	});
}

const onlineUsers = new Map<number, Set<ServerWebSocket<{ uid: number }>>>();

type ServerWebSocket<T> = Bun.ServerWebSocket<T>;

function isOnline(uid: number): boolean		{ return onlineUsers.has(uid) && onlineUsers.get(uid)!.size > 0; }

function getSocketsForUser(uid: number): Set<ServerWebSocket<{ uid: number }>> | undefined
{
	return onlineUsers.get(uid);
}

function sendToUser(uid: number, payload: object): void
{
	const sockets = getSocketsForUser(uid);
	if (!sockets) return;
	const msg = JSON.stringify(payload);
	for (const ws of sockets) ws.send(msg);
}

async function notifyFriendsOfStatus(uid: number, type: "friend_online" | "friend_offline"): Promise<void>
{
	const friendsList = await friendsDB.getFriends(uid);
	const [user] = await queries.getUserByID(uid);
	if (!user) return;

	const payload = { type, user: { id: uid, username: user.username, avatarUrl: user.avatar_url } };
	for (const f of friendsList)
		sendToUser(f.id, payload);
}

async function notifyUser(targetUid: number, type: string, data: object): Promise<void>
{
	sendToUser(targetUid, { type, ...data });
}

async function getFriendsHandler(req: Request): Promise<Response>
{
	const uid = await getUidFromRequest(req);
	if (!uid) return json({ error: "Unauthorized" }, StatusCode.UNAUTHORIZED);

	const friendsList = await friendsDB.getFriends(uid);
	return json({
		friends: friendsList.map(f => ({
			id:			f.id,
			username:	f.username,
			avatarUrl:	f.avatarUrl,
			isActive:	isOnline(f.id)
		}))
	});
}

async function getRequestsHandler(req: Request): Promise<Response>
{
	const uid = await getUidFromRequest(req);
	if (!uid) return json({ error: "Unauthorized" }, StatusCode.UNAUTHORIZED);

	const received	= await friendsDB.getReceivedRequests(uid);
	const sent		= await friendsDB.getSentRequests(uid);

	return json({
		received: received.map(r => ({ id: r.id, username: r.username, avatarUrl: r.avatarUrl })),
		sent:     sent.map(s => ({ id: s.id, username: s.username, avatarUrl: s.avatarUrl }))
	});
}

async function sendRequestHandler(req: Request): Promise<Response>
{
	const uid = await getUidFromRequest(req);
	if (!uid) return json({ error: "Unauthorized" }, StatusCode.UNAUTHORIZED);

	const body = await req.json() as { username?: string };
	if (!body.username) return json({ error: "Username required" }, StatusCode.BAD_REQUEST);

	const [target] = await queries.getUserByUSERNAME(body.username);
	if (!target)		return json({ error: "User not found" }, StatusCode.NOT_FOUND);
	if (target.id === uid)	return json({ error: "Cannot add yourself" }, StatusCode.BAD_REQUEST);

	if (await friendsDB.areFriends(uid, target.id))
		return json({ error: "Already friends" }, StatusCode.CONFLICT);
	if (await friendsDB.hasPendingRequest(uid, target.id))
		return json({ error: "Request already pending" }, StatusCode.CONFLICT);

	await friendsDB.addRequest(uid, target.id);

	const [sender] = await queries.getUserByID(uid);
	if (sender)
		notifyUser(target.id, "friend_request_received", { user: { id: uid, username: sender.username, avatarUrl: sender.avatar_url } });

	return json({ success: true }, StatusCode.CREATED);
}

async function acceptRequestHandler(req: Request): Promise<Response>
{
	const uid = await getUidFromRequest(req);
	if (!uid) return json({ error: "Unauthorized" }, StatusCode.UNAUTHORIZED);

	const body = await req.json() as { senderId?: number };
	if (!body.senderId) return json({ error: "senderId required" }, StatusCode.BAD_REQUEST);

	await friendsDB.acceptRequest(uid, body.senderId);

	const [accepter] = await queries.getUserByID(uid);
	if (accepter)
		notifyUser(body.senderId, "friend_request_accepted", { user: { id: uid, username: accepter.username, avatarUrl: accepter.avatar_url, isActive: isOnline(uid) } });

	notifyUser(uid, "friend_request_accepted", { user: { id: body.senderId, username: (await queries.getUserByID(body.senderId))[0]?.username, avatarUrl: (await queries.getUserByID(body.senderId))[0]?.avatar_url, isActive: isOnline(body.senderId) } });

	return json({ success: true });
}

async function refuseRequestHandler(req: Request): Promise<Response>
{
	const uid = await getUidFromRequest(req);
	if (!uid) return json({ error: "Unauthorized" }, StatusCode.UNAUTHORIZED);

	const body = await req.json() as { senderId?: number };
	if (!body.senderId) return json({ error: "senderId required" }, StatusCode.BAD_REQUEST);

	await friendsDB.refuseRequest(uid, body.senderId);
	return json({ success: true });
}

async function removeFriendHandler(req: Request): Promise<Response>
{
	const uid = await getUidFromRequest(req);
	if (!uid) return json({ error: "Unauthorized" }, StatusCode.UNAUTHORIZED);

	const body = await req.json() as { friendId?: number };
	if (!body.friendId) return json({ error: "friendId required" }, StatusCode.BAD_REQUEST);

	await friendsDB.delFriend(uid, body.friendId);

	notifyUser(body.friendId, "friend_removed", { userId: uid });

	return json({ success: true });
}

async function cancelRequestHandler(req: Request): Promise<Response>
{
	const uid = await getUidFromRequest(req);
	if (!uid) return json({ error: "Unauthorized" }, StatusCode.UNAUTHORIZED);

	const body = await req.json() as { receiverId?: number };
	if (!body.receiverId) return json({ error: "receiverId required" }, StatusCode.BAD_REQUEST);

	await friendsDB.delRequest(uid, body.receiverId);

	notifyUser(body.receiverId, "friend_request_cancelled", { userId: uid });

	return json({ success: true });
}

async function getProfileHandler(req: Request, targetId: number): Promise<Response>
{
	const uid = await getUidFromRequest(req);
	if (!uid) return json({ error: "Unauthorized" }, StatusCode.UNAUTHORIZED);

	const [target] = await queries.getUserByID(targetId);
	if (!target) return json({ error: "User not found" }, StatusCode.NOT_FOUND);

	const [userStats] = await db.select().from(stats).where(eq(stats.user_id, targetId)).limit(1);

	const isFriend      = await friendsDB.areFriends(uid, targetId);
	const hasPending    = await friendsDB.hasPendingRequest(uid, targetId);

	return json({
		profile: {
			id:          target.id,
			username:    target.username,
			avatarUrl:   target.avatar_url,
			bio:         target.bio ?? null,
			isOnline:    isOnline(targetId),
			createdAt:   target.created_at,
			coins:       target.coins ?? 0,
			isFriend,
			hasPending,
			stats: userStats ? {
				gamesPlayed:     userStats.games_played ?? 0,
				gamesWon:        userStats.games_won ?? 0,
				gamesLost:       userStats.games_lost ?? 0,
				blackjacksWon:   userStats.blackjacks_won ?? 0,
				blackjackLosses: userStats.blackjack_losses ?? 0,
				rouletteWins:    userStats.roulette_wins ?? 0,
				rouletteLosses:  userStats.roulette_losses ?? 0,
			} : null,
		}
	});
}

const routes: Record<string, (req: Request) => Promise<Response>> = {
	"GET:/api/social/friends":			getFriendsHandler,
	"GET:/api/social/friends/requests":	getRequestsHandler,
	"POST:/api/social/friends/request":	sendRequestHandler,
	"POST:/api/social/friends/accept":	acceptRequestHandler,
	"POST:/api/social/friends/refuse":	refuseRequestHandler,
	"POST:/api/social/friends/cancel":	cancelRequestHandler,
	"DELETE:/api/social/friends":		removeFriendHandler,
}

const server = Bun.serve<{ uid: number }>({
	port: Number(Bun.env.PORT),

	async fetch(req: Request, server): Promise<Response>
	{
		const url = new URL(req.url);

		if (url.pathname === "/ws/social")
		{
			const uid = await getUidFromRequest(req);
			if (!uid)
				return new Response("Unauthorized", { status: 401 });

			const upgraded = server.upgrade(req, { data: { uid } });
			if (!upgraded)
				return new Response("WebSocket upgrade failed", { status: 500 });
			return undefined as unknown as Response;
		}

		const profileMatch = url.pathname.match(/^\/api\/social\/profile\/(\d+)$/);
		if (profileMatch && req.method === "GET")
		{
			const response = await getProfileHandler(req, Number(profileMatch[1]));
			const headers = new Headers(response.headers);
			return new Response(response.body, { status: response.status, statusText: response.statusText, headers });
		}

		const handler = routes[`${req.method}:${url.pathname}`];
		const response = handler ? await handler(req) : new Response("Not Found", { status: StatusCode.NOT_FOUND });
		const headers = new Headers(response.headers);

		return new Response(response.body, { status: response.status, statusText: response.statusText, headers });
	},

	websocket: {
		sendPings: false,
		idleTimeout: 35,

		async open(ws)
		{
			const { uid } = ws.data;
			if (!onlineUsers.has(uid))
				onlineUsers.set(uid, new Set());
			const wasOffline = onlineUsers.get(uid)!.size === 0;
			onlineUsers.get(uid)!.add(ws);

			if (wasOffline)
				await notifyFriendsOfStatus(uid, "friend_online");

			const friendsList = await friendsDB.getFriends(uid);
			const onlineIds = friendsList.filter(f => isOnline(f.id)).map(f => f.id);
			ws.send(JSON.stringify({ type: "friends_online", userIds: onlineIds }));

			console.log(`WS open: user ${uid} (${onlineUsers.get(uid)!.size} tab(s))`);
		},

		async close(ws)
		{
			const { uid } = ws.data;
			const sockets = onlineUsers.get(uid);
			if (sockets)
			{
				sockets.delete(ws);
				if (sockets.size === 0)
				{
					onlineUsers.delete(uid);
					await notifyFriendsOfStatus(uid, "friend_offline");
				}
			}
			console.log(`WS close: user ${uid}`);
		},

		message(ws, msg)
		{
			if (msg === "ping")
			{
				ws.send("pong");
				return;
			}

			try
			{
				const data = JSON.parse(String(msg));

				if (data.type === "chat_send" && typeof data.to === "number" && typeof data.content === "string")
				{
					const { uid } = ws.data;
					const content = data.content.trim().slice(0, 2000);
					if (!content) return;

					(async () => {
						const areFriends = await friendsDB.areFriends(uid, data.to);
						if (!areFriends) return;

						const row = await messagesDB.addMessage(uid, data.to, content);
						const [sender] = await queries.getUserByID(uid);
						const payload = {
							type:       "chat_message",
							id:         row.id,
							from:       uid,
							to:         data.to,
							content:    row.content,
							createdAt:  row.createdAt,
							username:   sender?.username ?? "Unknown",
						};

						sendToUser(data.to, payload);
						sendToUser(uid, payload);
					})();
				}
				else if (data.type === "chat_history" && typeof data.friendId === "number")
				{
					const { uid } = ws.data;
					(async () => {
						const areFriends = await friendsDB.areFriends(uid, data.friendId);
						if (!areFriends) return;

						const rows = await messagesDB.getConversation(uid, data.friendId, 50);
						ws.send(JSON.stringify({
							type:     "chat_history",
							friendId: data.friendId,
							messages: rows.reverse(),
						}));
					})();
				}
			}
			catch {}
		},
	},
});

process.on("SIGTERM", (): void => {
	server.stop();
	process.exit(0);
});

console.log(`Social running on ${server.port}`);

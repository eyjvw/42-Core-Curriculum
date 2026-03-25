import { getUserIdFromRequest }	from '../jwt/jwt.ts';
import { roomManager }			from '../services/roomManager.ts';
import { wsManager }			from '../services/websocketManager.ts';
import { BotPlayer }			from '../services/botPlayer.ts';
import * as responses			from '../utils/responses.ts';
import * as queries				from '../../../db/schemas/getters.ts';
import { createGame, getGameState, calculateWinnings, hit, stand, doubleDown, createMultiplayerGame, multiplayerHit, multiplayerStand, multiplayerDouble, getMultiplayerGameState } from '../blackjack/engine.ts';
import type { GameRoom }		from '../types/multiplayer.ts';
import { hasActiveSoloGame }	from './blackjack.ts';

type BaseContext = { userId: any };

async function validateRequest(req: Request):										Promise<BaseContext | Response>;
async function validateRequest(req: Request, opts: { withUser: true }):				Promise<(BaseContext & { user: any }) | Response>;
async function validateRequest(req: Request, opts: { withRoomFromBody: true }):		Promise<(BaseContext & { room: GameRoom; body: any }) | Response>;
async function validateRequest(req: Request, opts: { withRoomFromQuery: true }):	Promise<(BaseContext & { room: GameRoom }) | Response>;
async function validateRequest(req: Request, opts: { withUser?: boolean; withRoomFromBody?: boolean; withRoomFromQuery?: boolean } = {} ): Promise<any>
{
	const userId = await getUserIdFromRequest(req);
	if (!userId)	{ return (responses.unauthorized()); }

	const result: any = { userId };

	if (opts.withUser)
	{
		const [user] = await queries.getUserByID(userId);
		if (!user) { return (responses.notFound('User not found')); }
		result.user = user;
	}

	if (opts.withRoomFromBody)
	{
		const body	= await req.json();
		if (!body.roomId)	{ return (responses.badRequest('Missing roomId'));	}
		const room	= roomManager.getRoom(body.roomId);
		if (!room)			{ return (responses.notFound('Room not found'));	}
		result.body	= body;
		result.room	= room;
	}

	if (opts.withRoomFromQuery)
	{
		const url		= new URL(req.url);
		const roomId	= url.searchParams.get('roomId');
		if (!roomId)	{ return (responses.badRequest('Missing roomId'));	}
		const room		= roomManager.getRoom(roomId);
		if (!room)		{ return (responses.notFound('Room not found'));	}
		result.room		= room;
	}

	return (result);
}

function broadcastPlayerTurn(roomId: string, game: any): void
{
	const current = game.players[game.currentPlayerIndex];
	if (current)
	{
		wsManager.broadcastToRoom(roomId, {
			type:		'player_turn',
			roomId:		roomId,
			playerId:	current.id,
			payload:	{ currentPlayerId: current.id },
			timestamp:	Date.now(),
		});
	}
}

function initAndBroadcastGame(room: GameRoom, roomId: string): any
{
	const game			= createMultiplayerGame(room.players);
	room.currentGame	= game;
	room.status			= 'playing';
	room.updatedAt		= new Date();

	wsManager.broadcastRoomState(roomId, serializeRoom(room));
	wsManager.broadcastGameState(roomId, getMultiplayerGameState(game));
	broadcastPlayerTurn(roomId, game);

	return (game);
}

function allBetsPlaced(room: GameRoom): boolean
{
	let hasEligible = false;
	for (const [, player] of room.players)
	{
		if (player.balance <= 0) continue;
		hasEligible = true;
		if (player.bet <= 0) return false;
	}
	return hasEligible;
}

function autoBetBots(room: GameRoom, roomId: string): void
{
	room.players.forEach(player =>
	{
		if (BotPlayer.isBot(player.id) && player.balance > 0)
		{
			const minBet	= 10;
			const maxBet	= Math.min(100, player.balance);
			player.bet		= Math.max(minBet, Math.floor(Math.random() * maxBet));
		}
	});
	wsManager.broadcastRoomState(roomId, serializeRoom(room));

	if (allBetsPlaced(room))
	{
		setTimeout(() => {
			if (room.status === 'betting')
			{
				const game = initAndBroadcastGame(room, roomId);
				autoBotPlay(room, roomId);
			}
		}, 500);
	}
}

async function autoBotPlay(room: GameRoom, roomId: string): Promise<void>
{
	if (!room.currentGame || room.currentGame.status !== 'playing') return;

	const game = room.currentGame;
	const current = game.players[game.currentPlayerIndex];
	if (!current || !BotPlayer.isBot(current.id)) return;

	await new Promise(r => setTimeout(r, BotPlayer.DECISION_DELAY));

	while (room.currentGame && room.currentGame.status === 'playing')
	{
		const curr = room.currentGame.players[room.currentGame.currentPlayerIndex];
		if (!curr || !BotPlayer.isBot(curr.id)) break;

		const total = curr.hand.total;
		try
		{
			if (total < BotPlayer.HIT_THRESHOLD)
				multiplayerHit(room.currentGame, curr.id);
			else
				multiplayerStand(room.currentGame, curr.id);
		}
		catch { break; }

		room.updatedAt = new Date();
		wsManager.broadcastGameState(roomId, getMultiplayerGameState(room.currentGame));

		if (room.currentGame.status === 'finished')
		{
			room.status = 'finished';
			await updatePlayerBalances(room);
			wsManager.broadcastRoomState(roomId, serializeRoom(room));
			return;
		}

		broadcastPlayerTurn(roomId, room.currentGame);

		const next = room.currentGame.players[room.currentGame.currentPlayerIndex];
		if (next && BotPlayer.isBot(next.id))
			await new Promise(r => setTimeout(r, BotPlayer.DECISION_DELAY));
	}
}

async function handleGameAction(req: Request, actionFn: (game: any, userId: string) => void): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withRoomFromBody: true });
		if (ctx instanceof Response) { return (ctx); }
		const { userId, room, body } = ctx;

		if (!room.currentGame)			return responses.badRequest('No active game');
		if (room.status !== 'playing')	return responses.badRequest('Game not in progress');

		try { actionFn(room.currentGame, String(userId)); }
		catch (e: any) { return responses.badRequest(e.message); }

		room.updatedAt = new Date();
		wsManager.broadcastGameState(body.roomId, getMultiplayerGameState(room.currentGame));

		if (room.currentGame.status === 'finished')
		{
			room.status = 'finished';
			await updatePlayerBalances(room);
			wsManager.broadcastRoomState(body.roomId, serializeRoom(room));
		}
		else
		{
			broadcastPlayerTurn(body.roomId, room.currentGame);
			autoBotPlay(room, body.roomId);
		}

		return (responses.success({ game: getMultiplayerGameState(room.currentGame)}));
	}
	catch (err)
	{
		console.error('Error in game action:', err);
		return responses.serverError();
	}
}

export async function createRoomController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withUser: true });
		if (ctx instanceof Response) return ctx;
		const { userId, user } = ctx;

		if (hasActiveSoloGame(userId))
			return responses.badRequest('You have an active solo game. Finish it first.');

		const existingRoom = roomManager.getRoomByUserId(String(userId));
		if (existingRoom)
			return responses.badRequest('You already have an active room. Leave it first.');

		const room = roomManager.createRoom(String(userId), user.username || `Player${userId}`, 5);

		return (responses.created({
			roomId: room.id,
			code: room.code,
			room: serializeRoom(room),
		}));
	}
	catch (err)
	{
		console.error('Error in createRoomController:', err);
		return (responses.serverError());
	}
}

export async function addBotController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withRoomFromBody: true });
		if (ctx instanceof Response) return ctx;
		const { userId, room } = ctx;

		if (room.hostId !== String(userId))
			return responses.badRequest('Only the host can add a bot');
		if (room.status !== 'waiting')
			return responses.badRequest('Can only add a bot while waiting');
		if (room.players.size >= room.maxPlayers)
			return responses.badRequest('Room is full');

		const bot = BotPlayer.createBotPlayer();
		room.players.set(bot.id, bot);
		wsManager.broadcastRoomState(room.id, serializeRoom(room));

		return responses.success({ room: serializeRoom(room) });
	}
	catch (err)
	{
		console.error('Error in addBotController:', err);
		return responses.serverError();
	}
}

export async function joinRoomController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withUser: true });
		if (ctx instanceof Response) return ctx;
		const { userId, user } = ctx;

		if (hasActiveSoloGame(userId))
			return responses.badRequest('You have an active solo game. Finish it first.');

		const body = (await req.json()) as { roomId?: string; code?: string };
		
		let room = null;
		if (body.code)
		{
			room = roomManager.getRoomByCode(body.code);
			if (!room) { return (responses.badRequest('Invalid room code')); }
		}
		else if (body.roomId)
		{
			room = roomManager.getRoom(body.roomId);
			if (!room) { return (responses.badRequest('Room not found')); }
		}
		else
			return responses.badRequest('Missing roomId or code');

		const existingRoom = roomManager.getRoomByUserId(String(userId));
		if (existingRoom && existingRoom.id !== room.id)
			return (responses.badRequest('You already have an active room. Leave it first.'));

		const result = roomManager.joinRoom(room.id, String(userId), user.username || `Player${userId}`, user.coins || 0);

		if (typeof result === 'string')
			return (responses.badRequest(result));

		wsManager.broadcastRoomState(room.id, serializeRoom(result));

		return (responses.success({
			roomId: result.id,
			code: result.code,
			room: serializeRoom(result),
		}));
	}
	catch (err)
	{
		console.error('Error in joinRoomController:', err);
		return (responses.serverError());
	}
}

export async function listRoomsController(req: Request): Promise<Response>
{
	try
	{
		const rooms = roomManager.getAllRooms().map((room) => ({
			id:				room.id,
			hostId:			room.hostId,
			status:			room.status,
			playerCount:	room.players.size,
			maxPlayers:		room.maxPlayers,
			spectatorCount:	room.spectators.size,
			createdAt:		room.createdAt,
		}));

		return (responses.success({ rooms }));
	}
	catch (err)
	{
		console.error('Error in listRoomsController:', err);
		return (responses.serverError());
	}
}

export async function getRoomController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withRoomFromQuery: true });
		if (ctx instanceof Response) return ctx;
		const { room } = ctx;

		return (responses.success({ room: serializeRoom(room), }));
	}
	catch (err)
	{
		console.error('Error in getRoomController:', err);
		return (responses.serverError());
	}
}

export async function startGameController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withRoomFromBody: true });
		if (ctx instanceof Response) return ctx;
		const { userId, room, body } = ctx;

		if (room.hostId !== String(userId)) { return (responses.badRequest('Only host can start game'));	}
		if (room.players.size < 1)			{ return (responses.badRequest('No players in room'));			}
		if (room.status !== 'waiting')		{ return responses.badRequest('Game already in progress');		}

		room.status		= 'betting';
		room.updatedAt	= new Date();
		room.players.forEach(player => { player.bet = 0; });

		autoBetBots(room, body.roomId);

		return (responses.success({
			status: 'betting',
			room: serializeRoom(room),
		}));
	}
	catch (err)
	{
		console.error('Error in startGameController:', err);
		return (responses.serverError());
	}
}

export async function placeBetController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withRoomFromBody: true });
		if (ctx instanceof Response) return ctx;
		const { userId, room, body } = ctx;

		if (body.bet === undefined)					{ return (responses.badRequest('Missing bet'));							}
		if (room.status !== 'betting')				{ return (responses.badRequest('Not in betting phase'));				}

		const player = room.players.get(String(userId));
		if (!player)								{ return (responses.badRequest('You are not a player in this room'));	}
		if (body.bet < 1)							{ return (responses.badRequest('Bet must be at least 1'));				}
		if (body.bet > player.balance)				{ return (responses.badRequest('Insufficient balance'));				}

		player.bet		= body.bet;
		room.updatedAt	= new Date();

		wsManager.broadcastRoomState(body.roomId, serializeRoom(room));

		if (allBetsPlaced(room))
		{
			setTimeout(() => {
				if (room.status === 'betting')
				{
					const game = initAndBroadcastGame(room, body.roomId);
					autoBotPlay(room, body.roomId);
				}
			}, 500);
		}

		return (responses.success({
			bet: player.bet,
			balance: player.balance,
		}));
	}
	catch (err)
	{
		console.error('Error in placeBetController:', err);
		return (responses.serverError());
	}
}

export async function dealCardsController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withRoomFromBody: true });
		if (ctx instanceof Response) { return (ctx); }
		const { userId, room, body } = ctx;

		if (room.hostId !== String(userId))	{ return (responses.badRequest('Only host can deal cards'));			}
		if (room.status !== 'betting')		{ return (responses.badRequest('Not in betting phase'));				}

		let playersWithBets = 0;
		room.players.forEach(player => { if (player.bet > 0) { playersWithBets++; }});
		if (playersWithBets === 0)			{ return responses.badRequest('At least one player must place a bet');	}

		const game = initAndBroadcastGame(room, body.roomId);

		return (responses.success({
			gameId: game.id,
			game: getMultiplayerGameState(game),
		}));
	}
	catch (err)
	{
		console.error('Error in dealCardsController:', err);
		return (responses.serverError());
	}
}

export async function gameHitController(req: Request):		Promise<Response>	{ return handleGameAction(req, multiplayerHit);		}
export async function gameStandController(req: Request):	Promise<Response>	{ return handleGameAction(req, multiplayerStand);	}
export async function gameDoubleController(req: Request):	Promise<Response>	{ return handleGameAction(req, multiplayerDouble);	}

export async function newRoundController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withRoomFromBody: true });
		if (ctx instanceof Response) { return (ctx); }
		const { userId, room, body } = ctx;

		if (room.hostId !== String(userId))	{ return (responses.badRequest('Only host can start new round')); }
		if (room.status !== 'finished')		{ return (responses.badRequest('Current game not finished')); }
		if (room.currentGame)				{ room.gameHistory.push(room.currentGame); }

		room.currentGame	= null;
		room.status			= 'betting';
		room.updatedAt		= new Date();

		room.players.forEach(player => { player.bet = 0; });

		autoBetBots(room, body.roomId);

		return responses.success({
			status: 'betting',
			message: 'New round started',
		});
	}
	catch (err)
	{
		console.error('Error in newRoundController:', err);
		return responses.serverError();
	}
}

async function updatePlayerBalances(room: any): Promise<void>
{
	if (!room.currentGame) { return; }

	for (const playerState of room.currentGame.players)
	{
		const player = room.players.get(playerState.id);
		if (!player) { continue ; }
		player.balance = playerState.balance;
		if (playerState.id && !BotPlayer.isBot(playerState.id))
		{
			try			{ await queries.updateUserCoins(parseInt(playerState.id), playerState.balance); }
			catch (e)	{ console.error('Failed to update user coins:', e); }
		}
	}
}

export async function getRoomGameStateController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withRoomFromQuery: true });
		if (ctx instanceof Response) { return (ctx); }
		const { room } = ctx;

		if (!room.currentGame)
		{
			return (responses.success({
				game:	null,
				status:	room.status,
			}));
		}

		return (responses.success({
			game:	getMultiplayerGameState(room.currentGame),
			status:	room.status,
		}));
	}
	catch (err)
	{
		console.error('Error in getRoomGameStateController:', err);
		return responses.serverError();
	}
}

export function serializeRoom(room: any)
{
	return {
		id:					room.id,
		code:				room.code,
		hostId:				room.hostId,
		status:				room.status,
		maxPlayers:			room.maxPlayers,
		playerCount:		room.players.size,
		spectatorCount:		room.spectators.size,
		players:			Array.from(room.players.values()).map((p: any) => ({
			id:				p.id,
			username:		p.username,
			role:			p.role,
			balance:		p.balance,
			bet:			p.bet,
			isConnected:	p.isConnected,
		})),
		spectators:			Array.from(room.spectators.values()).map((s: any) => ({
			id:				s.id,
			username:		s.username,
			role:			s.role,
			isConnected:	s.isConnected,
		})),
		gameId:				room.currentGame?.id,
		gameStatus:			room.currentGame?.status,
		game:				room.currentGame ? getMultiplayerGameState(room.currentGame) : null,
		createdAt:			room.createdAt,
	};
}

export async function getMyRoomController(req: Request): Promise<Response>
{
	try 
	{
		const ctx = await validateRequest(req);
		if (ctx instanceof Response) { return (ctx); }
		const { userId } = ctx;

		const room = roomManager.getRoomByUserId(String(userId));
		if (!room) { return responses.success({ room: null }); }

		roomManager.markPlayerConnected(room.id, String(userId));

		return responses.success({room: serializeRoom(room), code: room.code});
	}
	catch (err)
	{
		console.error('Error in getMyRoomController:', err);
		return responses.serverError();
	}
}

export async function kickPlayerController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withRoomFromBody: true });
		if (ctx instanceof Response)	{ return (ctx); }
		const { userId, room, body } = ctx;
		if (!body.targetUserId)			{ return (responses.badRequest('Missing targetUserId')); }

		const targetUserId	= String(body.targetUserId);
		const result		= roomManager.kickPlayer(room.id, String(userId), targetUserId);
		if (typeof result === 'string') { return (responses.badRequest(result)); }

		wsManager.broadcastRoomState(body.roomId, serializeRoom(result));
		wsManager.broadcastToRoom(body.roomId, {
			type:		'player_kicked' as any,
			roomId:		body.roomId,
			playerId:	targetUserId,
			payload:	{ kickedUserId: targetUserId },
			timestamp:	Date.now(),
		});

		wsManager.broadcastKick(body.roomId, targetUserId);
		return (responses.success({room: serializeRoom(result)}));
	}
	catch (err)
	{
		console.error('Error in kickPlayerController:', err);
		return (responses.serverError());
	}
}

export async function leaveRoomController(req: Request): Promise<Response>
{
	try
	{
		const ctx = await validateRequest(req, { withRoomFromBody: true });
		if (ctx instanceof Response) { return (ctx); }
		const { userId, room, body } = ctx;

		const success = roomManager.leaveRoom(body.roomId, String(userId));
		if (!success) { return (responses.badRequest('Failed to leave room')); }

		const updatedRoom = roomManager.getRoom(body.roomId);
		if (updatedRoom)
		{
			let hasHuman = false;
			for (const [, p] of updatedRoom.players)
			{
				if (!BotPlayer.isBot(p.id)) { hasHuman = true; break; }
			}
			if (!hasHuman)
			{
				roomManager.deleteRoom(body.roomId);
			}
			else
			{
				wsManager.broadcastToRoom(body.roomId, {
					type:		'leave',
					roomId:		body.roomId,
					playerId:	String(userId),
					payload:	{ playerId: String(userId) },
					timestamp:	Date.now(),
				});
				wsManager.broadcastRoomState(body.roomId, serializeRoom(updatedRoom));
			}
		}

		return (responses.success({ message: 'Left room successfully' }));
	}
	catch (err)
	{
		console.error('Error in leaveRoomController:', err);
		return (responses.serverError());
	}
}

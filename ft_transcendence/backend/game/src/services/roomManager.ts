import type { GameRoom, Player, PlayerRole } from '../types/multiplayer.ts';
import { BotPlayer } from './botPlayer.ts';

const DISCONNECT_TIMEOUT = 30000;
const AFK_TIMEOUT = 60000;

export class RoomManager
{
	private rooms: Map<string, GameRoom> = new Map();
	private userToRoom: Map<string, string> = new Map();
	private codeToRoom: Map<string, string> = new Map();

	private removePlayerFromActiveGame(room: GameRoom, userId: string): void
	{
		if (!room.currentGame)		{ return; }

		const removedIndex = room.currentGame.players.findIndex((player) => player.id === userId);
		if (removedIndex === -1)	{ return; }

		room.currentGame.players.splice(removedIndex, 1);

		if (room.currentGame.players.length === 0)
		{
			room.currentGame.currentPlayerIndex = 0;
			room.currentGame.status	= 'finished';
			room.status				= 'finished';
			return;
		}

		if (room.currentGame.currentPlayerIndex > removedIndex)						{ room.currentGame.currentPlayerIndex--; }
		if (room.currentGame.currentPlayerIndex >= room.currentGame.players.length) { room.currentGame.currentPlayerIndex = 0; }
		if (room.currentGame.status === 'playing')
		{
			const currentPlayer = room.currentGame.players[room.currentGame.currentPlayerIndex];
			if (!currentPlayer || currentPlayer.status !== 'playing')
			{
				const nextPlayableIndex = room.currentGame.players.findIndex((player) => player.status === 'playing');
				if (nextPlayableIndex === -1)
				{
					room.currentGame.status = 'finished';
					room.status = 'finished';
				}
				else { room.currentGame.currentPlayerIndex = nextPlayableIndex; }
			}
		}
	}

	private generateRoomCode(): string
	{
		const chars	= 'ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789';
		let code	= '';
		for (let i = 0; i < 6; i++)
			code += chars.charAt(Math.floor(Math.random() * chars.length));
		if (this.codeToRoom.has(code)) { return this.generateRoomCode(); }
		return code;
	}

	createRoom(hostId: string, hostUsername: string, maxPlayers: number = 5): GameRoom
	{
		const roomId = crypto.randomUUID();
		const code = this.generateRoomCode();
		const room: GameRoom = {
			id:			roomId,
			code,
			hostId,
			status:			'waiting',
			maxPlayers:		Math.min(5, maxPlayers),
			players:		new Map(),
			spectators:		new Map(),
			currentGame:	null,
			gameHistory:	[],
			createdAt:		new Date(),
			updatedAt:		new Date(),
		};

		room.players.set(hostId, {
			id:				hostId,
			username:		hostUsername,
			role:			'player',
			balance:		1000,
			bet:			0,
			isConnected:	true,
			lastPing:		Date.now(),
		});

		this.rooms.set(roomId, room);
		this.userToRoom.set(hostId, roomId);
		this.codeToRoom.set(code, roomId);

		return (room);
	}

	getRoom(roomId: string): GameRoom | null { return (this.rooms.get(roomId) || null); }
	getRoomByUserId(userId: string): GameRoom | null
	{
		const roomId = this.userToRoom.get(userId);
		return roomId ? this.rooms.get(roomId) || null : null;
	}

	getRoomByCode(code: string): GameRoom | null
	{
		const roomId = this.codeToRoom.get(code);
		return roomId ? this.rooms.get(roomId) || null : null;
	}

	joinRoom(roomId: string, userId: string, username: string, balance: number): GameRoom | string
	{
		const room = this.rooms.get(roomId);
		if (!room) { return ('Room not found'); }

		if (room.players.has(userId))
		{
			const player		= room.players.get(userId)!;
			player.isConnected	= true;
			player.lastPing		= Date.now();
			room.updatedAt		= new Date();
			return (room);
		}
		if (room.spectators.has(userId))
		{
			const spectator			= room.spectators.get(userId)!;
			spectator.isConnected	= true;
			spectator.lastPing		= Date.now();
			room.updatedAt			= new Date();
			return (room);
		}

		if (room.status !== 'waiting')
			return ('Cannot join a game in progress');

		if (room.players.size >= room.maxPlayers) { return ('Room is full'); }

		room.players.set(userId, {
			id:				userId,
			username,
			role:			'player',
			balance,
			bet:			0,
			isConnected:	true,
			lastPing:		Date.now(),
		});

		this.userToRoom.set(userId, roomId);
		room.updatedAt = new Date();
		return (room);
	}

	leaveRoom(roomId: string, userId: string): boolean
	{
		const room = this.rooms.get(roomId);
		if (!room) { return false; }

		this.removePlayerFromActiveGame(room, userId);

		const isPlayer		= room.players.delete(userId);
		const isSpectator	= room.spectators.delete(userId);
		this.userToRoom.delete(userId);

		if (room.players.size === 0 && room.spectators.size === 0)
		{
			this.codeToRoom.delete(room.code);
			this.rooms.delete(roomId);
			return (true);
		}

		if (isPlayer && room.hostId === userId && room.players.size > 0)
		{
			let newHost: string | undefined;
			for (const [id] of room.players)
			{
				if (!BotPlayer.isBot(id)) { newHost = id; break; }
			}
			if (!newHost) newHost = room.players.keys().next().value;
			if (newHost) { room.hostId = newHost; }
		}

		room.updatedAt = new Date();
		return (true);
	}

	markPlayerDisconnected(roomId: string, userId: string): void
	{
		const room = this.rooms.get(roomId);
		if (!room) { return; }

		const player = room.players.get(userId) || room.spectators.get(userId);
		if (player)
		{
			player.isConnected	= false;
			player.lastPing		= Date.now();
		}
	}

	allHumansDisconnected(roomId: string): boolean
	{
		const room = this.rooms.get(roomId);
		if (!room) { return true; }

		for (const [, player] of room.players)
		{
			if (!BotPlayer.isBot(player.id) && player.isConnected)
				return false;
		}
		for (const [, spectator] of room.spectators)
		{
			if (spectator.isConnected)
				return false;
		}
		return true;
	}

	deleteRoom(roomId: string): void
	{
		const room = this.rooms.get(roomId);
		if (!room) { return; }

		room.players.forEach((_, id) => this.userToRoom.delete(id));
		room.spectators.forEach((_, id) => this.userToRoom.delete(id));
		this.codeToRoom.delete(room.code);
		this.rooms.delete(roomId);
		console.log(`[Room] Room ${roomId} deleted (all players disconnected)`);
	}

	markPlayerConnected(roomId: string, userId: string): void
	{
		const room = this.rooms.get(roomId);
		if (!room) { return; }

		const player = room.players.get(userId) || room.spectators.get(userId);
		if (player)
		{
			player.isConnected	= true;
			player.lastPing		= Date.now();
		}
	}

	reconnectPlayer(userId: string): GameRoom | null
	{
		const roomId = this.userToRoom.get(userId);
		if (!roomId)	{ return (null); }

		const room = this.rooms.get(roomId);
		if (!room)		{ return (null); }

		const player = room.players.get(userId) || room.spectators.get(userId);
		if (player)
		{
			player.isConnected	= true;
			player.lastPing		= Date.now();
			room.updatedAt		= new Date();
		}

		return (room);
	}

	kickPlayer(roomId: string, hostId: string, targetUserId: string): GameRoom | string
	{
		const room = this.rooms.get(roomId);
		if (!room)							{ return 'Room not found';				}
		if (room.hostId !== hostId)			{ return 'Only host can kick players';	}
		if (hostId === targetUserId)		{ return 'Cannot kick yourself';		}

		const isPlayer		= room.players.has(targetUserId);
		const isSpectator	= room.spectators.has(targetUserId);

		if (!isPlayer && !isSpectator) { return ('Player not found in room'); }

		this.removePlayerFromActiveGame(room, targetUserId);

		room.players.delete(targetUserId);
		room.spectators.delete(targetUserId);
		this.userToRoom.delete(targetUserId);

		room.updatedAt = new Date();
		return (room);
	}

	updatePlayerPing(roomId: string, userId: string): void
	{
		const room = this.rooms.get(roomId);
		if (!room)	{ return; }

		const player = room.players.get(userId) || room.spectators.get(userId);
		if (player) { player.lastPing = Date.now(); }
	}

	getDisconnectedPlayers(roomId: string): Map<string, Player>
	{
		const room = this.rooms.get(roomId);
		if (!room) { return new Map(); }

		const disconnected	= new Map<string, Player>();
		const now			= Date.now();

		room.players.forEach((player, userId) => {
			if (!player.isConnected && !BotPlayer.isBot(userId) && now - player.lastPing > DISCONNECT_TIMEOUT)
				disconnected.set(userId, player);
		});

		return (disconnected);
	}

	startGame(roomId: string): GameRoom | string
	{
		const room = this.rooms.get(roomId);
		if (!room)						{ return ('Room not found'); }
		if (room.status !== 'waiting')	{ return ('Game already started'); }
		if (room.players.size < 1)		{ return ('No players in room'); }

		room.status		= 'betting';
		room.updatedAt	= new Date();
		return (room);
	}

	finishGame(roomId: string): GameRoom | string
	{
		const room = this.rooms.get(roomId);
		if (!room) { return ('Room not found'); }
		if (!room.currentGame) { return ('No active game'); }

		room.currentGame.status	= 'finished' as 'finished';
		room.status				= 'finished';
		room.gameHistory.push(room.currentGame);
		room.updatedAt			= new Date();

		return (room);
	}

	getAllRooms(): GameRoom[] { return Array.from(this.rooms.values()); }

	cleanupOldRooms(): void
	{
		const now		= Date.now();
		const maxAge	= 5 * 60 * 1000;

		for (const [roomId, room] of this.rooms.entries())
		{
			if (room.players.size === 0 && room.spectators.size === 0 && now - room.updatedAt.getTime() > maxAge)
				this.rooms.delete(roomId);
		}
	}

	handleDisconnectedPlayers(): void
	{
		for (const [roomId, room] of this.rooms.entries())
		{
			const disconnected = this.getDisconnectedPlayers(roomId);
			disconnected.forEach((player) => {
				this.removePlayerFromActiveGame(room, player.id);
				room.players.delete(player.id);
				room.spectators.delete(player.id);
				this.userToRoom.delete(player.id);
			});

			if (room.players.size === 0 && room.spectators.size === 0)
				this.rooms.delete(roomId);
		}
	}
}

export const roomManager = new RoomManager();

import type { BlackjackGame, BlackjackHand, Card } from './blackjack.ts';

export type PlayerRole = 'player' | 'spectator' | 'bot';
export type RoomStatus = 'waiting' | 'betting' | 'playing' | 'finished';

export interface Player {
	id: string;
	username: string;
	role: PlayerRole;
	balance: number;
	bet: number;
	isConnected: boolean;
	lastPing: number;
	wsClient?: WebSocket;
}

export interface MultiplayerPlayerState {
	id: string;
	username: string;
	hand: BlackjackHand;
	bet: number;
	balance: number;
	status: 'betting' | 'playing' | 'standing' | 'busted' | 'blackjack' | 'finished';
	result?: 'win' | 'lose' | 'push' | 'blackjack';
	winnings?: number;
}

export interface MultiplayerGameState {
	id: string;
	dealerHand: BlackjackHand;
	dealerHidden: boolean;
	players: MultiplayerPlayerState[];
	currentPlayerIndex: number;
	deck: Card[];
	status: 'betting' | 'dealing' | 'playing' | 'dealer_turn' | 'finished';
	createdAt: Date;
}

export interface GameRoom {
	id: string;
	code: string;
	hostId: string;
	status: RoomStatus;
	maxPlayers: number;
	players: Map<string, Player>;
	spectators: Map<string, Player>;
	currentGame: MultiplayerGameState | null;
	gameHistory: MultiplayerGameState[];
	createdAt: Date;
	updatedAt: Date;
	winnerId?: string;
	winnings?: Map<string, number>;
}

export interface RoomMessage {
	type: 'join' | 'leave' | 'bet' | 'hit' | 'stand' | 'double' | 'game_state' | 'error' | 'room_state' | 'player_disconnected' | 'game_finished' | 'player_kicked' | 'player_turn' | 'all_players_done';
	roomId: string;
	playerId?: string;
	payload?: unknown;
	timestamp?: number;
}

export interface BotConfig {
	hitThreshold: number;
	name: string;
}

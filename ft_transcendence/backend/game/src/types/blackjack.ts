export type Suit = 'hearts' | 'diamonds' | 'clubs' | 'spades';
export type Rank = 'A' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | '10' | 'J' | 'Q' | 'K';

export interface Card {
	suit: Suit;
	rank: Rank;
	value: number;
}

export interface BlackjackHand {
	cards: Card[];
	total: number;
	isSoft: boolean;
	isBlackjack: boolean;
	isBusted: boolean;
}

export interface BlackjackGame {
	id: string;
	playerId: string;
	playerHand: BlackjackHand;
	dealerHand: BlackjackHand;
	deck: Card[];
	bet: number;
	status: 'betting' | 'playing' | 'dealer_turn' | 'finished';
	result: 'pending' | 'player_win' | 'dealer_win' | 'push' | 'blackjack';
	createdAt: Date;
}

export interface GameState {
	gameId: string;
	playerHand: { cards: Card[]; total: number; isBusted: boolean };
	dealerHand: { cards: Card[]; total: number; isBusted: boolean; hidden?: boolean };
	status: string;
	result: string;
	bet: number;
}

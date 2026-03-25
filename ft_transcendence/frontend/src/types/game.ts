export type Suit = 'hearts' | 'diamonds' | 'clubs' | 'spades';
export type Rank = 'A' | '2' | '3' | '4' | '5' | '6' | '7' | '8' | '9' | '10' | 'J' | 'Q' | 'K' | '?';

export interface Card
{
	suit:	Suit;
	rank:	Rank;
	value:	number;
}

export interface Hand
{
	cards:		Card[];
	total:		number;
	isBusted:	boolean;
	hidden?:	boolean;
}

export interface GameState
{
	gameId:		string;
	playerHand:	Hand;
	dealerHand:	Hand;
	status:		'betting' | 'playing' | 'dealer_turn' | 'finished';
	result:		'pending' | 'player_win' | 'dealer_win' | 'push' | 'blackjack';
	bet:		number;
}

export interface BlackjackResponse
{
	game:		GameState | null;
	balance?:	number;
	winnings?:	number;
	error?:		string;
}

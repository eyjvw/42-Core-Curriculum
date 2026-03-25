import type { Card, Suit, Rank, BlackjackHand, BlackjackGame, GameState } from '../types/blackjack.ts';

const SUITS: Suit[] = ['hearts', 'diamonds', 'clubs', 'spades'];
const RANKS: Rank[] = ['A', '2', '3', '4', '5', '6', '7', '8', '9', '10', 'J', 'Q', 'K'];

function getCardValue(rank: Rank): number
{
	if (rank === 'A')					return (11);
	if (['K', 'Q', 'J'].includes(rank))	return (10);

	return (parseInt(rank));
}

export function createDeck(): Card[]
{
	const deck: Card[] = [];
	for (const suit of SUITS)
	{
		for (const rank of RANKS)
			deck.push({ suit, rank, value: getCardValue(rank) });
	}
	return (shuffleDeck(deck));
}

export function shuffleDeck(deck: Card[]): Card[]
{
	const shuffled = [...deck];
	for (let i = shuffled.length - 1; i > 0; i--)
	{
		const j = Math.floor(Math.random() * (i + 1));
		[shuffled[i], shuffled[j]] = [shuffled[j]!, shuffled[i]!];
	}
	return (shuffled);
}

export function calculateHand(cards: Card[]): BlackjackHand
{
	let total	= 0;
	let aces	= 0;

	for (const card of cards)
	{
		total += card.value;
		if (card.rank === 'A') { aces++; }
	}

	while (total > 21 && aces > 0)
	{
		total -= 10;
		aces--;
	}

	return {
		cards,
		total,
		isSoft:			aces > 0 && total <= 21,
		isBlackjack:	cards.length === 2 && total === 21,
		isBusted:		total > 21
	};
}

export function drawCard(deck: Card[]): Card
{
	const card = deck.pop();
	if (!card) { throw new Error('Deck is empty'); }

	return (card);
}

export function createGame(playerId: string, bet: number): BlackjackGame
{
	const deck = createDeck();
	const playerCards: Card[] = [drawCard(deck), drawCard(deck)];
	const dealerCards: Card[] = [drawCard(deck), drawCard(deck)];

	const game: BlackjackGame = {
		id:			crypto.randomUUID(),
		playerId,
		playerHand:	calculateHand(playerCards),
		dealerHand:	calculateHand(dealerCards),
		deck,
		bet,
		status:		'playing',
		result:		'pending',
		createdAt:	new Date()
	};

	if (game.playerHand.isBlackjack)
	{
		if (game.dealerHand.isBlackjack)
		{
			game.status = 'finished';
			game.result = 'push';
		}
		else
		{
			game.status = 'finished';
			game.result = 'blackjack';
		}
	}
	else if (game.dealerHand.isBlackjack)
	{
		game.status = 'finished';
		game.result = 'dealer_win';
	}

	return game;
}

export function hit(game: BlackjackGame): BlackjackGame
{
	if (game.status !== 'playing')
		throw (new Error('Cannot hit - game is not in playing state'));

	const newCard = drawCard(game.deck);
	game.playerHand = calculateHand([...game.playerHand.cards, newCard]);

	if (game.playerHand.isBusted)
	{
		game.status = 'finished';
		game.result = 'dealer_win';
	}

	return (game);
}

export function stand(game: BlackjackGame): BlackjackGame
{
	if (game.status !== 'playing')
		throw (new Error('Cannot stand - game is not in playing state'));

	game.status = 'dealer_turn';

	while (game.dealerHand.total < 17)
	{
		const newCard	= drawCard(game.deck);
		game.dealerHand	= calculateHand([...game.dealerHand.cards, newCard]);
	}

	game.status = 'finished';

	if (game.dealerHand.isBusted)
		game.result = 'player_win';
	else if (game.dealerHand.total > game.playerHand.total)
		game.result = 'dealer_win';
	else if (game.dealerHand.total < game.playerHand.total)
		game.result = 'player_win';
	else
		game.result = 'push';

	return (game);
}

export function doubleDown(game: BlackjackGame): BlackjackGame
{
	if (game.status !== 'playing' || game.playerHand.cards.length !== 2)
		throw (new Error('Cannot double down'));

	game.bet		*= 2;
	const newCard	= drawCard(game.deck);
	game.playerHand	= calculateHand([...game.playerHand.cards, newCard]);

	if (game.playerHand.isBusted)
	{
		game.status = 'finished';
		game.result = 'dealer_win';

		return (game);
	}

	return (stand(game));
}

export function getGameState(game: BlackjackGame, hideDealer: boolean = true): GameState
{
	const dealerCards = hideDealer && game.status === 'playing'
		? [game.dealerHand.cards[0]!, { suit: 'spades' as Suit, rank: '?' as Rank, value: 0 }]
		: game.dealerHand.cards;

	const dealerTotal = hideDealer && game.status === 'playing'
		? game.dealerHand.cards[0]!.value
		: game.dealerHand.total;

	return {
		gameId:			game.id,
		playerHand: {
			cards:		game.playerHand.cards,
			total:		game.playerHand.total,
			isBusted:	game.playerHand.isBusted
		},
		dealerHand: {
			cards:		dealerCards,
			total:		dealerTotal,
			isBusted:	game.dealerHand.isBusted,
			hidden:		hideDealer && game.status === 'playing'
		},
		status:			game.status,
		result:			game.result,
		bet:			game.bet
	};
}

export function calculateWinnings(game: BlackjackGame): number
{
	switch (game.result)
	{
		case 'blackjack':
			return (Math.floor(game.bet * 2.5));
		case 'player_win':
			return (game.bet * 2);
		case 'push':
			return (game.bet);
		default:
			return (0);
	}
}

import type { MultiplayerGameState, MultiplayerPlayerState, Player } from '../types/multiplayer.ts';

export function createMultiplayerGame(players: Map<string, Player>): MultiplayerGameState
{
	const deck										= createDeck();
	const playerStates: MultiplayerPlayerState[]	= [];

	players.forEach((player) => {
		if ((player.role === 'player' || player.role === 'bot') && player.bet > 0)
		{
			const cards = [drawCard(deck), drawCard(deck)];
			const hand = calculateHand(cards);
			
			playerStates.push({
				id:			player.id,
				username:	player.username,
				hand,
				bet:		player.bet,
				balance:	player.balance - player.bet,
				status:		hand.isBlackjack ? 'blackjack' : 'playing',
			});
		}
	});

	const dealerCards	= [drawCard(deck), drawCard(deck)];
	const dealerHand	= calculateHand(dealerCards);

	const game: MultiplayerGameState = {
		id:					crypto.randomUUID(),
		dealerHand,
		dealerHidden:		true,
		players:			playerStates,
		currentPlayerIndex:	0,
		deck,
		status:				'playing',
		createdAt:			new Date(),
	};

	while (game.currentPlayerIndex < game.players.length && 
		   (game.players[game.currentPlayerIndex]?.status === 'blackjack' || 
		    game.players[game.currentPlayerIndex]?.status === 'busted'))
		game.currentPlayerIndex++;

	if (game.currentPlayerIndex >= game.players.length)
	{
		game.status = 'dealer_turn';
		finishMultiplayerGame(game);
	}

	return (game);
}

export function multiplayerHit(game: MultiplayerGameState, playerId: string): MultiplayerGameState
{
	const playerIndex = game.players.findIndex(p => p.id === playerId);
	if (playerIndex === -1)							{ throw (new Error('Player not found'));					}
	if (playerIndex !== game.currentPlayerIndex)	{ throw (new Error('Not your turn'));						}
	if (game.status !== 'playing')					{ throw (new Error('Game not in playing state'));			}

	const player = game.players[playerIndex]!;
	if (player.status !== 'playing')				{ throw (new Error('Cannot hit - already done'));			}

	const newCard	= drawCard(game.deck);
	player.hand		= calculateHand([...player.hand.cards, newCard]);

	if (player.hand.isBusted)
	{
		player.status =		'busted';
		player.result =		'lose';
		player.winnings =	0;
		advanceToNextPlayer(game);
	}

	return (game);
}

export function multiplayerStand(game: MultiplayerGameState, playerId: string): MultiplayerGameState
{
	const playerIndex = game.players.findIndex(p => p.id === playerId);
	if (playerIndex === -1)							{ throw (new Error('Player not found'));					}
	if (playerIndex !== game.currentPlayerIndex)	{ throw (new Error('Not your turn'));						}
	if (game.status !== 'playing')					{ throw (new Error('Game not in playing state'));			}

	const player = game.players[playerIndex]!;
	if (player.status !== 'playing')				{ throw new Error('Cannot stand - already done');			}

	player.status = 'standing';
	advanceToNextPlayer(game);

	return (game);
}

export function multiplayerDouble(game: MultiplayerGameState, playerId: string): MultiplayerGameState
{
	const playerIndex = game.players.findIndex(p => p.id === playerId);
	if (playerIndex === -1)							{ throw (new Error('Player not found'));					}
	if (playerIndex !== game.currentPlayerIndex)	{ throw (new Error('Not your turn'));						}
	if (game.status !== 'playing')					{ throw (new Error('Game not in playing state'));			}

	const player = game.players[playerIndex]!;
	if (player.status !== 'playing')				{ throw (new Error('Cannot double - already done'));		}
	if (player.hand.cards.length !== 2)				{ throw (new Error('Can only double on first two cards'));	}
	if (player.balance < player.bet)				{ throw (new Error('Insufficient balance to double'));		}

	player.balance	-= player.bet;
	player.bet		*= 2;

	const newCard	= drawCard(game.deck);
	player.hand		= calculateHand([...player.hand.cards, newCard]);

	if (player.hand.isBusted)
	{
		player.status = 'busted';
		player.result = 'lose';
		player.winnings = 0;
	}
	else { player.status = 'standing'; }

	advanceToNextPlayer(game);
	return (game);
}

function advanceToNextPlayer(game: MultiplayerGameState): void
{
	game.currentPlayerIndex++;

	while (game.currentPlayerIndex < game.players.length)
	{
		const player = game.players[game.currentPlayerIndex];
		if (player && (player.status === 'playing'))
			break;
		game.currentPlayerIndex++;
	}

	if (game.currentPlayerIndex >= game.players.length)
	{
		game.status = 'dealer_turn';
		finishMultiplayerGame(game);
	}
}

function finishMultiplayerGame(game: MultiplayerGameState): void
{
	game.dealerHidden	= false;
	const activePlayers	= game.players.filter(p => p.status !== 'busted');

	if (activePlayers.length > 0)
	{
		while (game.dealerHand.total < 17)
		{
			const newCard	= drawCard(game.deck);
			game.dealerHand	= calculateHand([...game.dealerHand.cards, newCard]);
		}
	}

	game.players.forEach(player => {
		if (player.status === 'busted')
		{
			player.result	= 'lose';
			player.winnings	= 0;
			player.status	= 'finished';
		}
		else if (player.status === 'blackjack')
		{
			if (game.dealerHand.isBlackjack)
			{
				player.result	= 'push';
				player.winnings	= player.bet;
			}
			else
			{
				player.result	= 'blackjack';
				player.winnings	= Math.floor(player.bet * 2.5);
			}
			player.balance	+= player.winnings;
			player.status	= 'finished';
		}
		else
		{
			if (game.dealerHand.isBusted)
			{
				player.result	= 'win';
				player.winnings	= player.bet * 2;
			}
			else if (game.dealerHand.total > player.hand.total)
			{
				player.result	= 'lose';
				player.winnings	= 0;
			}
			else if (game.dealerHand.total < player.hand.total)
			{
				player.result	= 'win';
				player.winnings	= player.bet * 2;
			}
			else
			{
				player.result	= 'push';
				player.winnings	= player.bet;
			}
			player.balance	+= player.winnings || 0;
			player.status	= 'finished';
		}
	});

	game.status = 'finished';
}

export function getMultiplayerGameState(game: MultiplayerGameState): any
{
	const dealerCards = game.dealerHidden
		? [game.dealerHand.cards[0]!, { suit: 'spades' as Suit, rank: '?' as Rank, value: 0 }]
		: game.dealerHand.cards;

	const dealerTotal = game.dealerHidden
		? game.dealerHand.cards[0]!.value
		: game.dealerHand.total;

	return {
		gameId:			game.id,
		dealerHand: {
			cards:		dealerCards,
			total:		dealerTotal,
			isBusted:	game.dealerHidden ? false : game.dealerHand.isBusted,
			hidden:		game.dealerHidden,
		},
		players: game.players.map(p => ({
			id:				p.id,
			username:		p.username,
			hand: {
				cards:		p.hand.cards,
				total:		p.hand.total,
				isBusted:	p.hand.isBusted,
			},
			bet:			p.bet,
			balance:		p.balance,
			status:			p.status,
			result:			p.result,
			winnings:		p.winnings,
		})),
		currentPlayerId:	game.players[game.currentPlayerIndex]?.id || null,
		currentPlayerIndex:	game.currentPlayerIndex,
		status:				game.status,
		createdAt:			game.createdAt,
	};
}

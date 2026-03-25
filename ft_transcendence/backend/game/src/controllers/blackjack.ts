import type	{ BlackjackGame }													from '../types/blackjack.ts';
import { getUserIdFromRequest }													from '../jwt/jwt.ts';
import { createGame, hit, stand, doubleDown, getGameState, calculateWinnings }	from '../blackjack/engine.ts';
import * as responses															from '../utils/responses.ts';
import * as queries																from '../../../db/schemas/getters.ts';
import { roomManager }														from '../services/roomManager.ts';

const activeGames: Map<string, BlackjackGame>	= new Map();
const userGames: Map<number, string>			= new Map();

export function hasActiveSoloGame(userId: number): boolean
{
	const gameId = userGames.get(userId);
	if (!gameId) return false;
	const game = activeGames.get(gameId);
	return !!(game && game.status !== 'finished');
}

export async function newGameController(req: Request): Promise<Response>
{
	try
	{
		const userId = await getUserIdFromRequest(req);
		if (!userId) { return (responses.unauthorized()); }

		const existingRoom = roomManager.getRoomByUserId(String(userId));
		if (existingRoom)
			return (responses.badRequest('You are in a multiplayer room. Leave it first.'));

		const existingGameId = userGames.get(userId);
		if (existingGameId && activeGames.has(existingGameId))
		{
			const existingGame = activeGames.get(existingGameId)!;
			if (existingGame.status !== 'finished')
				return (responses.badRequest('You already have an active game. Finish it first.'));
		}

		const body	= await req.json() as { bet?: number };
		const bet	= body.bet ?? 10;

		if (bet < 1 || bet > 10000)
			return (responses.badRequest('Invalid bet amount (1-10000)'));

		const [user] = await queries.getUserByID(userId);
		if (!user)				{ return (responses.notFound('User not found')); }
		if (user.coins! < bet)	{ return (responses.badRequest('Insufficient balance')); }

		await queries.updateUserCoins(userId, user.coins! - bet);

		const game = createGame(userId.toString(), bet);
		activeGames.set(game.id, game);
		userGames.set(userId, game.id);

		if (game.status === 'finished')
		{
			const winnings = calculateWinnings(game);
			if (winnings > 0)
			{
				const [updatedUser] = await queries.getUserByID(userId);
				await queries.updateUserCoins(userId, updatedUser!.coins! + winnings);
			}
		}

		return (responses.created({
			game: getGameState(game),
			balance: (await queries.getUserByID(userId))[0]?.coins
		}));
	}
	catch (err)
	{
		console.error('Error in newGameController:', err);
		return (responses.serverError());
	}
}

export async function hitController(req: Request): Promise<Response>
{
	try
	{
		const userId = await getUserIdFromRequest(req);
		if (!userId)	{ return (responses.unauthorized()); }

		const gameId = userGames.get(userId);
		if (!gameId)	{ return (responses.notFound('No active game')); }

		const game = activeGames.get(gameId);
		if (!game)		{ return (responses.notFound('Game not found')); }

		if (game.status !== 'playing')
			return (responses.badRequest('Cannot hit - game is not in playing state'));

		hit(game);

		return (responses.success({
			game: getGameState(game, game.status === 'playing'),
			balance: (await queries.getUserByID(userId))[0]?.coins
		}));
	}
	catch (err)
	{
		console.error('Error in hitController:', err);
		return (responses.serverError());
	}
}

export async function standController(req: Request): Promise<Response>
{
	try
	{
		const userId = await getUserIdFromRequest(req);
		if (!userId) { return (responses.unauthorized()); }

		const gameId = userGames.get(userId);
		if (!gameId) { return (responses.notFound('No active game')); }

		const game = activeGames.get(gameId);
		if (!game) { return (responses.notFound('Game not found')); }

		if (game.status !== 'playing')
			return responses.badRequest('Cannot stand - game is not in playing state');

		stand(game);

		const winnings = calculateWinnings(game);
		if (winnings > 0)
		{
			const [user] = await queries.getUserByID(userId);
			await queries.updateUserCoins(userId, user!.coins! + winnings);
		}

		return (responses.success({
			game: getGameState(game, false),
			balance: (await queries.getUserByID(userId))[0]?.coins,
			winnings
		}));
	}
	catch (err)
	{
		console.error('Error in standController:', err);
		return (responses.serverError());
	}
}

export async function doubleController(req: Request): Promise<Response>
{
	try
	{
		const userId = await getUserIdFromRequest(req);
		if (!userId)	{ return (responses.unauthorized()); }

		const gameId = userGames.get(userId);
		if (!gameId)	{ return (responses.notFound('No active game')); }

		const game = activeGames.get(gameId);
		if (!game)		{ return (responses.notFound('Game not found')); }

		if (game.status !== 'playing' || game.playerHand.cards.length !== 2)
			return responses.badRequest('Cannot double down');

		const [user] = await queries.getUserByID(userId);
		if (!user) { return (responses.notFound('User not found')); }
		if (user.coins! < game.bet)
			return responses.badRequest('Insufficient balance for double down');

		await queries.updateUserCoins(userId, user.coins! - game.bet);

		doubleDown(game);

		const winnings = calculateWinnings(game);
		if (winnings > 0)
		{
			const [updatedUser] = await queries.getUserByID(userId);
			await queries.updateUserCoins(userId, updatedUser!.coins! + winnings);
		}

		return (responses.success({
			game: getGameState(game, false),
			balance: (await queries.getUserByID(userId))[0]?.coins,
			winnings
		}));
	}
	catch (err)
	{
		console.error('Error in doubleController:', err);
		return (responses.serverError());
	}
}

export async function getGameController(req: Request): Promise<Response>
{
	try
	{
		const userId = await getUserIdFromRequest(req);
		if (!userId)	{ return (responses.unauthorized()); }

		const gameId = userGames.get(userId);
		if (!gameId)	{ return (responses.success({ game: null })); }

		const game = activeGames.get(gameId);
		if (!game)		{ return (responses.success({ game: null })); }

		return (responses.success({
			game: getGameState(game, game.status === 'playing'),
			balance: (await queries.getUserByID(userId))[0]?.coins
		}));
	}
	catch (err)
	{
		console.error('Error in getGameController:', err);
		return (responses.serverError());
	}
}

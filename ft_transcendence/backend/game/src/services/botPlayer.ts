import type { BlackjackGame }	from '../types/blackjack.ts';
import { hit, stand }			from '../blackjack/engine.ts';

let botCounter = 0;

export class BotPlayer {
	static readonly BOT_PREFIX = 'bot_';
	static readonly HIT_THRESHOLD = 17;
	static readonly DECISION_DELAY = 2000;

	static isBot(id: string): boolean { return id.startsWith(this.BOT_PREFIX); }

	static shouldHit(playerTotal: number):		boolean						{ return (playerTotal < this.HIT_THRESHOLD); }
	static executeAction(game: BlackjackGame):	'hit' | 'stand' | 'none'	{ if (game.status !== 'playing' || game.playerId !== game.playerId) { return 'none'; }

		const botHand = game.playerHand;

		if (botHand.isBusted)				{ return ('stand'); }
		if (this.shouldHit(botHand.total))	{ return ('hit'); }
		else								{ return ('stand'); }
	}

	static async playGame(game: BlackjackGame): Promise<void>
	{
		while (game.status === 'playing' && game.playerId === game.playerId)
		{
			const action = this.executeAction(game);

			if (action === 'none') { break; }

			await new Promise((resolve) => setTimeout(resolve, this.DECISION_DELAY));

			if (action === 'hit')			{ hit(game); }
			else if (action === 'stand')	{ stand(game); }
		}
	}

	static createBotPlayer()
	{
		botCounter++;
		const botId = `${this.BOT_PREFIX}${botCounter}`;
		const names = ['Dealer Bot', 'Lucky Bot', 'Card Shark', 'Ace Bot', 'Wild Bot'];
		const name = names[(botCounter - 1) % names.length]!;

		return {
			id:				botId,
			username:		name,
			role:			'bot' as const,
			balance:		10000,
			bet:			0,
			isConnected:	true,
			lastPing:		Date.now(),
		};
	}
}

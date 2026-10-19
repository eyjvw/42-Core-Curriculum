import { users }						from "./users";
import { sqliteTable, integer, text }	from "drizzle-orm/sqlite-core";
import { eq, sql }						from "drizzle-orm";
import { db }							from "../init";

export const stats = sqliteTable("stats", {
	id:					integer("id").primaryKey({ autoIncrement: true }),
	user_id:			integer("user_id").notNull().references(() => users.id),
	points:				integer("points").default(0),
	games_played:		integer("games_played").default(0),
	games_won:			integer("games_won").default(0),
	games_lost:			integer("games_lost").default(0),
	blackjacks_won:		integer("blackjacks_won").default(0),
	blackjack_losses:	integer("blackjack_losses").default(0),
	roulette_wins:		integer("roulette_wins").default(0),
	roulette_losses:	integer("roulette_losses").default(0),
	created_at:			text("created_at").default("CURRENT_TIMESTAMP"),
	updated_at:			text("updated_at").default("CURRENT_TIMESTAMP")
});

export function recordBlackjackResult(userId: number, outcome: "win" | "loss" | "push"): void
{
	const won	= outcome === "win" ? 1 : 0;
	const lost	= outcome === "loss" ? 1 : 0;

	db.transaction((tx) => {
		const row = tx.select({ id: stats.id }).from(stats).where(eq(stats.user_id, userId)).get();

		if (!row)
			tx.insert(stats).values({
				user_id:			userId,
				games_played:		1,
				games_won:			won,
				games_lost:			lost,
				blackjacks_won:		won,
				blackjack_losses:	lost,
				created_at:			sql`CURRENT_TIMESTAMP`,
				updated_at:			sql`CURRENT_TIMESTAMP`
			}).run();
		else
			tx.update(stats).set({
				games_played:		sql`${stats.games_played} + 1`,
				games_won:			sql`${stats.games_won} + ${won}`,
				games_lost:			sql`${stats.games_lost} + ${lost}`,
				blackjacks_won:		sql`${stats.blackjacks_won} + ${won}`,
				blackjack_losses:	sql`${stats.blackjack_losses} + ${lost}`,
				updated_at:			sql`CURRENT_TIMESTAMP`
			}).where(eq(stats.id, row.id)).run();
	});
}

import { drizzle }	from "drizzle-orm/bun-sqlite";
import { Database }	from "bun:sqlite";

const sqlite = new Database("/app/data/sqlite.db");
export const db = drizzle(sqlite);

db.run("PRAGMA busy_timeout = 5000;");
db.run("PRAGMA foreign_keys = ON;");
db.run("PRAGMA journal_mode = WAL;");
db.run("PRAGMA synchronous = NORMAL;");
db.run("PRAGMA temp_store = MEMORY;");
db.run("PRAGMA cache_size = -20000;");
db.run("PRAGMA page_size = 4096;");
db.run("PRAGMA auto_vacuum = INCREMENTAL;");

db.transaction((): void => {
	db.run(`
		CREATE TABLE IF NOT EXISTS users (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			username TEXT NOT NULL UNIQUE,
			bio TEXT,
			email TEXT NOT NULL UNIQUE,
			password_hash TEXT,
			avatar_url TEXT,
			is_active INTEGER DEFAULT 0,
			a2f_secret TEXT,
			created_at TEXT DEFAULT CURRENT_TIMESTAMP,
			updated_at TEXT DEFAULT CURRENT_TIMESTAMP,
			language TEXT DEFAULT 'en',
			coins INTEGER DEFAULT 1000
		)
	`);

	const tableInfo		= sqlite.prepare("PRAGMA table_info(users)").all() as any[];
	const columnNames	= tableInfo.map((c: any) => c.name);

	if (!columnNames.includes("coins"))
	{
		try			{ db.run("ALTER TABLE users ADD COLUMN coins INTEGER DEFAULT 1000"); }
		catch (e)	{ console.error("Migration error (coins):", e); }
	}
	if (!columnNames.includes("a2f_secret"))
	{
		try			{ db.run("ALTER TABLE users ADD COLUMN a2f_secret TEXT"); }
		catch (e)	{ console.error("Migration error (a2f_secret):", e); }
	}
	if (!columnNames.includes("a2f_active"))
	{
		try			{ db.run("ALTER TABLE users ADD COLUMN a2f_active INTEGER DEFAULT 0"); }
		catch (e)	{ console.error("Migration error (a2f_active):", e); }
	}

	try
	{
		db.run(`UPDATE users SET created_at = datetime('now') WHERE created_at = 'CURRENT_TIMESTAMP' OR created_at IS NULL`);
		db.run(`UPDATE users SET updated_at = datetime('now') WHERE updated_at = 'CURRENT_TIMESTAMP' OR updated_at IS NULL`);
	}
	catch (e) { console.error("Migration error (fix timestamps):", e); }

	db.run(`
		CREATE TABLE IF NOT EXISTS stats (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			user_id INTEGER NOT NULL REFERENCES users(id),
			points INTEGER DEFAULT 0,
			games_played INTEGER DEFAULT 0,
			games_won INTEGER DEFAULT 0,
			games_lost INTEGER DEFAULT 0,
			blackjacks_won INTEGER DEFAULT 0,
			blackjack_losses INTEGER DEFAULT 0,
			roulette_wins INTEGER DEFAULT 0,
			roulette_losses INTEGER DEFAULT 0,
			created_at TEXT DEFAULT CURRENT_TIMESTAMP,
			updated_at TEXT DEFAULT CURRENT_TIMESTAMP
		)
	`);

	db.run(`
		CREATE TABLE IF NOT EXISTS points_history (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			stat_id INTEGER NOT NULL REFERENCES stats(id),
			"change" INTEGER NOT NULL,
			reason TEXT NOT NULL,
			game_type TEXT,
			created_at TEXT DEFAULT CURRENT_TIMESTAMP
		)
	`);

	db.run(`
		CREATE TABLE IF NOT EXISTS friends (
			user_id INTEGER NOT NULL REFERENCES users(id),
			friend_id INTEGER NOT NULL REFERENCES users(id),
			PRIMARY KEY (user_id, friend_id)
		)
	`);

	db.run(`
		CREATE TABLE IF NOT EXISTS friend_requests (
			sender_id INTEGER NOT NULL REFERENCES users(id),
			receiver_id INTEGER NOT NULL REFERENCES users(id),
			PRIMARY KEY (sender_id, receiver_id)
		)
	`);

	db.run(`
		CREATE TABLE IF NOT EXISTS messages (
			id INTEGER PRIMARY KEY AUTOINCREMENT,
			sender_id INTEGER NOT NULL REFERENCES users(id),
			receiver_id INTEGER NOT NULL REFERENCES users(id),
			content TEXT NOT NULL,
			created_at TEXT DEFAULT CURRENT_TIMESTAMP
		)
	`);
	db.run(`CREATE INDEX IF NOT EXISTS idx_messages_conversation ON messages(sender_id, receiver_id)`);
});

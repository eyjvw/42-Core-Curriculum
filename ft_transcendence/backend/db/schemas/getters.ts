import { db }       from "../init"
import { users }    from "./users"
import { eq }       from "drizzle-orm"

export function	setA2FSecretByID(id: number, secret: { base32: string })	{ return (db.update(users).set({ a2f_secret: secret.base32 }).where(eq(users.id, id))); }
export function getUserByID(id: number)										{ return (db.select().from(users).where(eq(users.id, id)).limit(1)); }
export function getUserByEMAIL(email: string)								{ return (db.select().from(users).where(eq(users.email, email)).limit(1)); }
export function getUserByUSERNAME(username: string)							{ return (db.select().from(users).where(eq(users.username, username)).limit(1)); }

export function updateUserCoins(id: number, coins: number)					{ return (db.update(users).set({ coins }).where(eq(users.id, id))); }

import { sqliteTable, integer, text }	from "drizzle-orm/sqlite-core";
import { sql }							from "drizzle-orm";

export const users = sqliteTable("users", {
	id:				integer("id").primaryKey({ autoIncrement: true }),
	username:		text("username").notNull().unique(),
	email:			text("email").notNull().unique(),
	password_hash:	text("password_hash"),
	avatar_url:		text("avatar_url"),
	is_active:		integer("is_active").default(0),
	a2f_secret:		text("a2f_secret"),
	a2f_active:		integer("a2f_active").default(0),
	created_at:		text("created_at").default(sql`(CURRENT_TIMESTAMP)`),
	updated_at:		text("updated_at").default(sql`(CURRENT_TIMESTAMP)`),
	language:		text("language").default("en"),
	coins:			integer("coins").default(1000),
	bio:			text("bio"),
});

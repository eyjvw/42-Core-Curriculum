import { sqliteTable, integer, text }	from "drizzle-orm/sqlite-core";
import { sql, eq, or, and, desc }		from "drizzle-orm";
import { users }						from "./users";
import { db }							from "../init";

export const messages = sqliteTable("messages", {
	id:			integer("id").primaryKey({ autoIncrement: true }),
	senderId:	integer("sender_id").notNull().references(() => users.id),
	receiverId:	integer("receiver_id").notNull().references(() => users.id),
	content:	text("content").notNull(),
	createdAt:	text("created_at").default(sql`(CURRENT_TIMESTAMP)`),
});

export async function addMessage(senderId: number, receiverId: number, content: string)
{
	const [row] = await db.insert(messages).values({ senderId, receiverId, content }).returning();
	return row;
}

export async function getConversation(userA: number, userB: number, limit = 50)
{
	return db
		.select({
			id:			messages.id,
			senderId:	messages.senderId,
			receiverId:	messages.receiverId,
			content:	messages.content,
			createdAt:	messages.createdAt,
		})
		.from(messages)
		.where(
			or(
				and(eq(messages.senderId, userA), eq(messages.receiverId, userB)),
				and(eq(messages.senderId, userB), eq(messages.receiverId, userA)),
			)
		)
		.orderBy(desc(messages.createdAt))
		.limit(limit);
}

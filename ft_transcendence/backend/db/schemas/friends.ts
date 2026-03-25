import { sqliteTable, integer, primaryKey }	from "drizzle-orm/sqlite-core";
import { and, eq, or }						from "drizzle-orm"
import { users }							from "./users";
import { db }								from "../init";

export const friends = sqliteTable("friends", {
	userId:		integer("user_id").notNull().references(() => users.id),
	friendId:	integer("friend_id").notNull().references(() => users.id)
}, (t) => ({ pk: primaryKey({ columns: [t.userId, t.friendId] }) }) );

export const friend_requests = sqliteTable("friend_requests", {
	senderId:	integer("sender_id").notNull().references(() => users.id),
	receiverId:	integer("receiver_id").notNull().references(() => users.id)
}, (t) => ({ pk: primaryKey({ columns: [t.senderId, t.receiverId] })}));

export async function addFriend(userId: number, friendId: number)
{
	await db.insert(friends).values({userId, friendId});
	await db.insert(friends).values({ userId: friendId, friendId: userId});
}

export async function delFriend(userId: number, friendId: number)
{
	await db.delete(friends).where(and(eq(friends.userId, userId), eq(friends.friendId, friendId)));
	await db.delete(friends).where(and(eq(friends.userId, friendId), eq(friends.friendId, userId)));
}

export async function acceptRequest(accepterId: number, senderId: number)
{
	await delRequest(senderId, accepterId);
	await addFriend(accepterId, senderId);
}

export async function refuseRequest(refuserId: number, senderId: number)	{ await delRequest(senderId, refuserId); }
export async function addRequest(senderId: number, receiverId: number)		{ await db.insert(friend_requests).values({ senderId, receiverId }) }
export async function delRequest(senderId: number, receiverId: number)		{ await db.delete(friend_requests).where(and(eq(friend_requests.senderId, senderId), eq(friend_requests.receiverId, receiverId))); }

export async function getFriends(userId: number)
{
	return db
		.select({ id: users.id, username: users.username, avatarUrl: users.avatar_url, isActive: users.is_active })
		.from(friends)
		.innerJoin(users, eq(friends.friendId, users.id))
		.where(eq(friends.userId, userId));
}

export async function getReceivedRequests(userId: number)
{
	return db
		.select({ id: users.id, username: users.username, avatarUrl: users.avatar_url })
		.from(friend_requests)
		.innerJoin(users, eq(friend_requests.senderId, users.id))
		.where(eq(friend_requests.receiverId, userId));
}

export async function getSentRequests(userId: number)
{
	return db
		.select({ id: users.id, username: users.username, avatarUrl: users.avatar_url })
		.from(friend_requests)
		.innerJoin(users, eq(friend_requests.receiverId, users.id))
		.where(eq(friend_requests.senderId, userId));
}

export async function areFriends(userId: number, friendId: number): Promise<boolean>
{
	const rows = await db.select().from(friends).where(and(eq(friends.userId, userId), eq(friends.friendId, friendId))).limit(1);
	return rows.length > 0;
}

export async function hasPendingRequest(senderId: number, receiverId: number): Promise<boolean>
{
	const rows = await db.select().from(friend_requests).where(
		or(
			and(eq(friend_requests.senderId, senderId), eq(friend_requests.receiverId, receiverId)),
			and(eq(friend_requests.senderId, receiverId), eq(friend_requests.receiverId, senderId))
		)
	).limit(1);
	return rows.length > 0;
}

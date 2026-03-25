import { verifyJWT }	from "../jwt/jwt";
import { StatusCode }	from "../types/status_code.ts";
import * as errors		from "../utils/errors.ts"
import * as queries		from "../../db/schemas/getters.ts"

export async function meController(req: Request): Promise<Response>
{
	try
	{
		const cookie: string | null = req.headers.get("cookie");
		if (!cookie) return new Response(JSON.stringify({ user: null }), { status: StatusCode.OK });

		const token: string | undefined = cookie.match(/token=([^;]+)/)?.[1];
		if (!token) return new Response(JSON.stringify({ user: null }), { status: StatusCode.OK });

		const { uid }: Record<string, string> = await verifyJWT(token);
		const [user] = await queries.getUserByID(Number(uid));
		if (!user) return new Response(JSON.stringify({ user: null }), { status: StatusCode.OK });

		return new Response(JSON.stringify({
			user: {
				id:				user.id,
				username:		user.username,
				email:			user.email,
				avatarUrl:		user.avatar_url,
				isActive:		Boolean(user.is_active),
				language:		user.language,
				coins:			user.coins,
				a2fActive:		Boolean(user.a2f_active)
			}
		}), { status: StatusCode.OK });
	}
	catch(err: unknown)
	{
		return new Response(JSON.stringify({ user: null }), { status: StatusCode.OK });
	}
}

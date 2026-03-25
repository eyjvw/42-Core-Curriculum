import { loginSchema, type LoginInput } from "../validators/auth";
import { db }							from "../../db/init";
import { users }						from "../../db/schemas/users";
import { compare }						from "bcrypt";
import { z, type ZodSafeParseResult }	from "zod";
import { eq, or }						from "drizzle-orm";
import { createJWT }					from "../jwt/jwt";
import { StatusCode }					from "../types/status_code.ts";
import { validate2FACode }				from "./a2f.ts";
import * as errors						from "../utils/errors.ts";

const findUser = (identifier: string) => { return db.select().from(users).where(or(eq(users.email, identifier), eq(users.username, identifier))).limit(1); };

export async function loginController(req: Request): Promise<Response>
{
	try
	{
		const parsed: ZodSafeParseResult<LoginInput> = loginSchema.safeParse(await req.json());
		if (!parsed.success) return (errors.parsing(parsed));

		const { email, password, a2f_code }: LoginInput & { a2f_code?: string }	= parsed.data;
		const identifier: string				= email;
		const user								= await findUser(identifier);

		if (user.length < 1) return (errors.invalidCred());

		const correctPass: boolean = await compare(password, user[0]!.password_hash);
		if (!correctPass) return (errors.invalidCred());

		if (user[0]!.a2f_active === 1)
		{
			if (!a2f_code) return (errors.a2fCodeRequired());
			if (!user[0]!.a2f_secret || !validate2FACode(user[0]!.a2f_secret, a2f_code))
				return (errors.a2fInvalidCode());
		}
	
		return new Response(JSON.stringify({ success: true }), {
			status: StatusCode.OK,
			headers: { "Set-Cookie": `token=${await createJWT(user[0]!.id.toString()!)}; HttpOnly; Secure; Path=/; SameSite=Lax` }
		});
	}
	catch(err: unknown)
	{
		console.error(err);
		return (errors.server());
	}
}

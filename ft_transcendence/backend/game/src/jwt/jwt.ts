import { jwtVerify, type JWTPayload, type JWTVerifyResult } from "jose";

if (!Bun.env.JWT_SECRET || /change_?me/i.test(Bun.env.JWT_SECRET))
	throw new Error("JWT_SECRET environment variable not set (or still the .env.example placeholder)");

const secret = new TextEncoder().encode(Bun.env.JWT_SECRET);

export async function verifyJWT(token: string): Promise<{ uid: string }>
{
	const { payload }: JWTVerifyResult<JWTPayload> = await jwtVerify(token, secret);
	return (payload as { uid: string });
}

export async function getUserIdFromRequest(req: Request): Promise<number | null>
{
	try
	{
		const cookie: string | null = req.headers.get("cookie");
		if (!cookie)	{ return (null); }

		const token: string | undefined = cookie.match(/(?:^|;\s*)token=([^;]+)/)?.[1];
		if (!token)		{ return (null); }

		const { uid } = await verifyJWT(token);
		return (Number(uid));
	}
	catch { return (null); }
}

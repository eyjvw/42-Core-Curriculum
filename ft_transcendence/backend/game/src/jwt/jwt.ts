import { jwtVerify, type JWTPayload, type JWTVerifyResult } from "jose";

const secret = new TextEncoder().encode(Bun.env.JWT_SECRET || "dev_only");

if (!Bun.env.JWT_SECRET)
	console.warn("JWT_SECRET environment variable not set. Using default insecure key.");

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

		const token: string | undefined = cookie.match(/token=([^;]+)/)?.[1];
		if (!token)		{ return (null); }

		const { uid } = await verifyJWT(token);
		return (Number(uid));
	}
	catch { return (null); }
}

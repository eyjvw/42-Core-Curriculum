import { SignJWT, jwtVerify, type JWTPayload, type JWTVerifyResult } from "jose";

if (!Bun.env.JWT_SECRET || /change_?me/i.test(Bun.env.JWT_SECRET))
	throw new Error("JWT_SECRET environment variable not set (or still the .env.example placeholder)");

const secret = new TextEncoder().encode(Bun.env.JWT_SECRET);

export async function createJWT(uid: string): Promise<string>
{
	return await new SignJWT({ uid })
	.setProtectedHeader({ alg: "HS256" })
	.setIssuedAt()
	.setExpirationTime("7d")
	.sign(secret);
}

export async function verifyJWT(token: string): Promise<{ uid: string }>
{
	const { payload }: JWTVerifyResult<JWTPayload> = await jwtVerify(token, secret);
	return payload as { uid: string };
}
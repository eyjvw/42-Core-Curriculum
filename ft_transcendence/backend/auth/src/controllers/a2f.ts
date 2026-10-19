import * as OTPAuth		from "otpauth";
import { toDataURL }	from "qrcode";
import { db }			from "../../db/init";
import { users }		from "../../db/schemas/users";
import { eq }			from "drizzle-orm";
import { verifyJWT }	from "../jwt/jwt";
import { StatusCode }	from "../types/status_code";
import * as errors		from "../utils/errors";
import * as queries		from "../../db/schemas/getters";

export async function enable2FA(req: Request): Promise<Response>
{
	try
	{
		const cookie	= req.headers.get("cookie");
		const token		= cookie?.match(/(?:^|;\s*)token=([^;]+)/)?.[1];
		if (!token) return (errors.unauthorized());

		const { uid }	= await verifyJWT(token);
		const [user]	= await queries.getUserByID(Number(uid));
		if (!user) return (errors.userNotFound());
		if (user.a2f_active === 1) return (errors.a2fAlreadyEnabled());

		const secret	= new OTPAuth.Secret({ size: 20 });
		const totp		= new OTPAuth.TOTP({
			issuer: "ft_transcendence",
			label: user.email,
			secret,
		});

		await queries.setA2FSecretByID(user.id, secret);

		const uri		= totp.toString();

		return new Response(JSON.stringify({
			secret: secret.base32,
			uri,
			qr: await toDataURL(uri)
		}), { status: StatusCode.OK });
	}
	catch (err)
	{
		console.error(err);
		return (errors.server());
	}
}

export async function verify2FA(req: Request): Promise<Response>
{
	try
	{
		const cookie	= req.headers.get("cookie");
		const token		= cookie?.match(/(?:^|;\s*)token=([^;]+)/)?.[1];
		if (!token) return (errors.unauthorized());

		const { uid }	= await verifyJWT(token);
		const [user]	= await queries.getUserByID(Number(uid));
		if (!user?.a2f_secret) return errors.a2fNotSetup();

		const { code }	= await req.json() as { code?: string };
		if (!code) return (errors.a2fCodeRequired());

		const totp = new OTPAuth.TOTP({ secret: OTPAuth.Secret.fromBase32(user.a2f_secret) });
		if (totp.validate({ token: code, window: 1 }) === null)
			return (errors.a2fInvalidCode());

		await db.update(users).set({ a2f_active: 1 }).where(eq(users.id, user.id));
		return (new Response(JSON.stringify({ success: true }), { status: StatusCode.OK }));
	}
	catch (err)
	{
		console.error(err);
		return (errors.server());
	}
}

export async function disable2FA(req: Request): Promise<Response>
{
	try
	{
		const cookie	= req.headers.get("cookie");
		const token		= cookie?.match(/(?:^|;\s*)token=([^;]+)/)?.[1];
		if (!token) return (errors.unauthorized());

		const { uid }	= await verifyJWT(token);
		const [user]	= await queries.getUserByID(Number(uid));
		if (!user) return (errors.userNotFound());

		if (user.a2f_active === 1)
		{
			const { code }	= await req.json() as { code?: string };
			if (typeof code !== "string" || !code) return (errors.a2fCodeRequired());
			if (!user.a2f_secret || !validate2FACode(user.a2f_secret, code))
				return (errors.a2fInvalidCode());
		}

		await db.update(users).set({ a2f_active: 0, a2f_secret: null }).where(eq(users.id, user.id));
		return (new Response(JSON.stringify({ success: true }), { status: StatusCode.OK }));
	}
	catch (err)
	{
		console.error(err);
		return (errors.server());
	}
}

export function validate2FACode(secret: string, code: string): boolean
{
	const totp = (new OTPAuth.TOTP({ secret: OTPAuth.Secret.fromBase32(secret) }));
	return (totp.validate({ token: code, window: 1 }) !== null);
}

import { loginController }					from "./controllers/login.ts";
import { logoutController }					from "./controllers/logout.ts";
import { meController }						from "./controllers/me.ts";
import { updateProfileController }			from "./controllers/profile.ts";
import { registerController }				from "./controllers/register.ts";
import { enable2FA, verify2FA, disable2FA }	from "./controllers/a2f.ts";
import { StatusCode }						from "./types/status_code.ts";

const routes: Record<string, (req: Request) => Promise<Response>> = {
	"GET:/api/auth/me": meController,
	"PUT:/api/auth/profile": updateProfileController,
	"POST:/api/auth/logout": logoutController,

	"POST:/api/auth/login": loginController,
	"POST:/api/auth/register": registerController,

	"POST:/api/auth/2fa/enable": enable2FA,
	"POST:/api/auth/2fa/verify": verify2FA,
	"POST:/api/auth/2fa/disable": disable2FA,
}

const server: Bun.Server<undefined> = Bun.serve({
	port: Number(Bun.env.PORT),
	async fetch(req: Request): Promise<Response>
	{
		const handler: ((req: Request) => Promise<Response>) | undefined = routes[`${req.method}:${new URL(req.url).pathname}`];
		const response: Response = handler ? await handler(req) : new Response("Not Found", { status: StatusCode.NOT_FOUND });
		const headers: Headers = new Headers(response.headers);

		return new Response(response.body, { status: response.status, statusText: response.statusText, headers });
	}
});

process.on("SIGTERM", (): void => {
    server.stop();
    process.exit(0);
});

console.log(`Auth running on ${server.port}`);

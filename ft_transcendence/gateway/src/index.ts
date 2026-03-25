import		{ StatusCode }											from "./types/status_code.ts";
import		{ detectInjection }										from "./waf/sql/detect.ts";
import type	{ RateLimitResult }										from "./types/ratelimit_result.ts";
import		{ applyRateLimitHeaders, checkRateLimit, getClientId }	from "./waf/ratelimit/limiter.ts";

function applyCors(req: Request, headers: Headers = new Headers()): Headers
{
    const requestOrigin: string | null = req.headers.get("Origin");

    if (requestOrigin)
    {
        try
        {
            const origin      = new URL(requestOrigin);
            const allowedPort = Bun.env.FRONTEND_PORT || "3000";
            const gatewayPort = String(Bun.env.PORT || "8000");
            const externalPort = Bun.env.EXTERNAL_PORT || allowedPort;
            if (origin.port === allowedPort || origin.port === gatewayPort || origin.port === externalPort)
            {
                headers.set("Access-Control-Allow-Origin", requestOrigin);
                headers.set("Access-Control-Allow-Credentials", "true");
            }
        }
        catch {}
    }

    headers.set("Access-Control-Allow-Methods", "GET, POST, PUT, DELETE, OPTIONS");
    headers.set("Access-Control-Allow-Headers", req.headers.get("Access-Control-Request-Headers") ?? "Content-Type, Authorization");
    headers.set("Access-Control-Expose-Headers", "Set-Cookie");
    headers.set("Vary", "Origin");

    return (headers);
}

const getResponse =			(str: string | null, stat: number, req: Request):	Response => { return (new Response(str,	{ status: stat, headers: applyCors(req) })); };
const getWebSock  =			async (req: Request, url: URL):						Response => { return (await Bun.fetch(Bun.env.WS_ROUTE! + url.pathname + url.search, req)); };
const getUpstream =			async (path: string, req: Request):					Response => { return (await Bun.fetch(path, { method: req.method, headers: req.headers, body: req.body })); };
const successfulResponse =	(upstream: Response, headers: Headers):				Response => { return (new Response(upstream.body, { status: upstream.status, statusText: upstream.statusText, headers })); };

function serverError		(req: Request): Response { return (getResponse("Internal Server Error", 500, req)); };
function targetNotFound		(req: Request):	Response { return (getResponse("Not Found", StatusCode.NOT_FOUND ?? 404, req)); };
function unavailableStream	(req: Request): Response { return (getResponse("Upstream service unavailable", StatusCode.BAD_GATEWAY, req)); };
function handleOption		(req: Request):	Response { return (getResponse(null, StatusCode.NO_CONTENT ?? 204, req)); };
function handleInjection	(req: Request):	Response { return (getResponse("Forbidden", StatusCode.FORBIDDEN ?? 403, req)); };
function tooManyRequest		(req: Request, rl: RateLimitResult): Response
{
	const headers: Headers = applyCors(req);
	applyRateLimitHeaders(headers, rl);

	return (new Response("Too Many Requests", { status: StatusCode.TOO_MANY_REQUESTS ?? 429, headers }));
}

function buildUpstreamWsUrl(route: string, pathname: string, search: string): string
{
	const base = route.replace(/^http/, "ws");
	return base + pathname + search;
}

const server = Bun.serve<{ upstream: WebSocket | null; cookie: string; pathname: string; search: string; target?: string }>({
    port: Number(Bun.env.PORT),
    async fetch(req: Request): Promise<Response | undefined> {
        try
		{
			let headers:	Headers;
            let upstream:	Response;
            let target:		string | undefined;
            const url:		URL =						new URL(req.url);

			if (url.pathname === "/ws/social")
			{
				const cookie = req.headers.get("cookie") || "";
				const upgraded = server.upgrade(req, {
					data: { upstream: null, cookie, pathname: url.pathname, search: url.search }
				});
				if (!upgraded)
					return getResponse("WebSocket upgrade failed", 500, req);
				return undefined;
			}

			if (url.pathname.match(/^\/api\/games\/rooms\/[^/]+\/ws$/))
			{
				const cookie = req.headers.get("cookie") || "";
				const upgraded = server.upgrade(req, {
					data: { upstream: null, cookie, pathname: url.pathname, search: url.search, target: Bun.env.GAMES_ROUTE }
				});
				if (!upgraded)
					return getResponse("WebSocket upgrade failed", 500, req);
				return undefined;
			}

			if (req.headers.get("upgrade")?.toLowerCase() === "websocket" && !url.pathname.startsWith("/api") && !url.pathname.startsWith("/ws"))
			{
				const frontendRoute = (Bun.env.FRONTEND_ROUTE || "http://frontend:3000").replace(/^http/, "ws");
				try
				{
					const upstreamUrl = frontendRoute + url.pathname + url.search;
					const cookie = req.headers.get("cookie") || "";
					const upgraded = server.upgrade(req, {
						data: { upstream: null, cookie, pathname: url.pathname, search: url.search, target: Bun.env.FRONTEND_ROUTE }
					});
					if (!upgraded)
						return getResponse("WebSocket upgrade failed", 500, req);
					return undefined;
				}
				catch { return getResponse("WebSocket proxy failed", 502, req); }
			}

			if (url.pathname.startsWith("/ws"))
				return (await getWebSock(req, url));

			const rl: RateLimitResult | null = url.pathname.startsWith("/api") ? checkRateLimit(getClientId(req)) : null;
			if (rl && !rl.allowed)
				return (tooManyRequest(req, rl));
            if (req.method === "OPTIONS")
				return (handleOption(req));
            if (detectInjection(url.search))
				return (handleInjection(req));

			if (url.pathname.startsWith("/api/auth"))
                target = Bun.env.AUTH_ROUTE;
            else if (url.pathname.startsWith("/api/social"))
                target = Bun.env.SOCIAL_ROUTE;
            else if (url.pathname.startsWith("/api/games"))
                target = Bun.env.GAMES_ROUTE;
            if (!target)
			{
				const frontendRoute = Bun.env.FRONTEND_ROUTE || "http://frontend:3000";
				try
				{
					return await fetch(frontendRoute + url.pathname + url.search, {	
						method: req.method,
						headers: req.headers,
						body: req.body,
					});
				}
				catch
				{
					return (targetNotFound(req));
				}
			}

            try
			{
				upstream = await getUpstream(target + url.pathname + url.search, req);
            }
			catch (err: unknown)
			{
                console.error("Upstream service error:", err);
				return (unavailableStream(req));
            }

            headers = applyCors(req, new Headers(upstream.headers));
			if (rl) applyRateLimitHeaders(headers, rl);

			return (successfulResponse(upstream, headers));
        }
		catch (err: unknown)
		{
            console.error("Gateway crash:", err);
			return (serverError(req));
        }
    },

	websocket: {
		sendPings: false,
		perMessageDeflate: false,
		idleTimeout: 45,

		open(ws)
		{
			const upstreamRoute = ws.data.target || Bun.env.SOCIAL_ROUTE!;
			const upstreamUrl = buildUpstreamWsUrl(
				upstreamRoute,
				ws.data.pathname,
				ws.data.search
			);

			const upstreamWs = new WebSocket(upstreamUrl, {
				headers: { cookie: ws.data.cookie }
			} as any);

			ws.data.upstream = upstreamWs;

			upstreamWs.onmessage = (event) => {
				try { ws.send(typeof event.data === "string" ? event.data : new Uint8Array(event.data as ArrayBuffer)); }
				catch {}
			};

			upstreamWs.onclose = () => {
				console.log(`WS upstream closed for ${ws.data.pathname}`);
				try { ws.close(); } catch {}
			};

			upstreamWs.onerror = (err) => {
				console.error(`WS upstream error for ${ws.data.pathname}:`, err);
				try { ws.close(); } catch {}
			};
		},

		message(ws, msg)
		{
			const upstream = ws.data.upstream;
			if (upstream && upstream.readyState === WebSocket.OPEN)
				upstream.send(msg);
		},

		close(ws)
		{
			const upstream = ws.data.upstream;
			if (upstream)
			{
				upstream.onclose = null;
				upstream.onerror = null;
				upstream.onmessage = null;
				if (upstream.readyState === WebSocket.OPEN || upstream.readyState === WebSocket.CONNECTING)
					upstream.close();
			}
			ws.data.upstream = null;
		},
	},
});

process.on("SIGTERM", (): void => {
    server.stop();
    process.exit(0);
});

console.log(`Gateway running on HTTP port ${Bun.env.PORT}`);

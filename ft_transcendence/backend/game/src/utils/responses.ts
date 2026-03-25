import { StatusCode } from "../types/status_code.ts";

export function unauthorized(): Response {
	return new Response(JSON.stringify({ error: "Unauthorized" }), { 
		status: StatusCode.UNAUTHORIZED,
		headers: { "Content-Type": "application/json" }
	});
}

export function badRequest(message: string = "Bad request"): Response {
	return new Response(JSON.stringify({ error: message }), { 
		status: StatusCode.BAD_REQUEST,
		headers: { "Content-Type": "application/json" }
	});
}

export function notFound(message: string = "Not found"): Response {
	return new Response(JSON.stringify({ error: message }), { 
		status: StatusCode.NOT_FOUND,
		headers: { "Content-Type": "application/json" }
	});
}

export function serverError(): Response {
	return new Response(JSON.stringify({ error: "Internal server error" }), { 
		status: StatusCode.INTERNAL_SERVER_ERROR,
		headers: { "Content-Type": "application/json" }
	});
}

export function success(data: unknown = {}): Response {
	return new Response(JSON.stringify(data), { 
		status: StatusCode.OK,
		headers: { "Content-Type": "application/json" }
	});
}

export function created(data: unknown = {}): Response {
	return new Response(JSON.stringify(data), { 
		status: StatusCode.CREATED,
		headers: { "Content-Type": "application/json" }
	});
}

import { StatusCode }					from "../types/status_code.ts";
import { z, type ZodSafeParseResult }	from "zod";

const errorResponse = (errStr: string, code: number):		Response => { return (new Response(JSON.stringify({ error: errStr }), { status: code }))};

export const userTaken = (): 								Response => { return (errorResponse("Email or username already in use",	StatusCode.BAD_REQUEST));			};
export const parsing = (parsed: ZodSafeParseResult<any>):	Response => { return (errorResponse(z.treeifyError(parsed.error),		StatusCode.BAD_REQUEST));			};
export const unauthorized = (): 							Response => { return (errorResponse("Unauthorized",						StatusCode.UNAUTHORIZED));			};
export const noCookie = (): 								Response => { return (errorResponse("No Cookie",						StatusCode.BAD_REQUEST));			};
export const noUpdates = (): 								Response => { return (errorResponse("No updates",						StatusCode.BAD_REQUEST));			};
export const userNotFound = (): 							Response => { return (errorResponse("User not found",					StatusCode.NOT_FOUND));				};
export const usernameTaken = (): 							Response => { return (errorResponse("Username already in use",			StatusCode.BAD_REQUEST));			};
export const emailTaken = (): 								Response => { return (errorResponse("Email already in use",				StatusCode.BAD_REQUEST));			};
export const invalidCred = ():								Response => { return (errorResponse("Invalid credentials",				StatusCode.UNAUTHORIZED));			};

export const server = (): 									Response => { return (errorResponse("Server Error",						StatusCode.INTERNAL_SERVER_ERROR));	};
export const userNorFoundCreated = ():						Response => { return (errorResponse("User not found or created",		StatusCode.INTERNAL_SERVER_ERROR));	};
export const failedCreatingUser = ():						Response => { return (errorResponse("Failed to create user",			StatusCode.INTERNAL_SERVER_ERROR)); };
export const a2fNotSetup = ():								Response => { return (errorResponse("2FA not setup",					StatusCode.BAD_REQUEST));			};
export const a2fCodeRequired = ():							Response => { return (errorResponse("2FA code required",				StatusCode.BAD_REQUEST));			};
export const a2fInvalidCode = ():							Response => { return (errorResponse("Invalid 2FA code",				StatusCode.UNAUTHORIZED));				};

import { forbiddenPatterns } from "../../types/patterns";

export function detectInjection(str: string): boolean
{
    let decoded: string;

    try { decoded = decodeURIComponent(str.replace(/\+/g, " ")); }
    catch { return (true); }
    return (forbiddenPatterns.some((rx: RegExp) => rx.test(decoded)));
}
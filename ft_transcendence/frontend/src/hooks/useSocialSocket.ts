import { useEffect, useRef, useState, useCallback } from 'react';

export type ChatMessage = {
  id:        number;
  from:      number;
  to:        number;
  content:   string;
  createdAt: string;
  username:  string;
};

export type SocialEvent =
  | { type: 'friends_online';            userIds: number[] }
  | { type: 'friend_online';             user: { id: number; username: string; avatarUrl: string | null } }
  | { type: 'friend_offline';            user: { id: number; username: string; avatarUrl: string | null } }
  | { type: 'friend_request_received';   user: { id: number; username: string; avatarUrl: string | null } }
  | { type: 'friend_request_accepted';   user: { id: number; username: string; avatarUrl: string | null; isActive: boolean } }
  | { type: 'friend_request_cancelled';  userId: number }
  | { type: 'friend_removed';            userId: number }
  | { type: 'chat_message';              id: number; from: number; to: number; content: string; createdAt: string; username: string }
  | { type: 'chat_history';              friendId: number; messages: ChatMessage[] };

interface UseSocialSocketReturn {
  onlineIds:    Set<number>;
  lastEvent:    SocialEvent | null;
  connected:    boolean;
  sendChatMessage: (to: number, content: string) => void;
  requestChatHistory: (friendId: number) => void;
}

const PING_INTERVAL  = 25_000;
const PONG_TIMEOUT   = 10_000;
const RECONNECT_BASE = 2_000;
const RECONNECT_MAX  = 30_000;

export function useSocialSocket(loggedIn: boolean): UseSocialSocketReturn {
  const wsRef                        = useRef<WebSocket | null>(null);
  const [onlineIds, setOnlineIds]    = useState<Set<number>>(new Set());
  const [lastEvent, setLastEvent]    = useState<SocialEvent | null>(null);
  const [connected, setConnected]    = useState(false);
  const reconnectTimer               = useRef<ReturnType<typeof setTimeout> | null>(null);
  const pingTimer                    = useRef<ReturnType<typeof setInterval> | null>(null);
  const pongTimer                    = useRef<ReturnType<typeof setTimeout> | null>(null);
  const mountedRef                   = useRef(true);
  const retriesRef                   = useRef(0);

  const clearTimers = useCallback(() => {
    if (reconnectTimer.current) { clearTimeout(reconnectTimer.current);  reconnectTimer.current = null; }
    if (pingTimer.current)      { clearInterval(pingTimer.current);      pingTimer.current = null; }
    if (pongTimer.current)      { clearTimeout(pongTimer.current);       pongTimer.current = null; }
  }, []);

  const connect = useCallback(() => {
    if (!loggedIn) return;
    if (wsRef.current && (wsRef.current.readyState === WebSocket.OPEN || wsRef.current.readyState === WebSocket.CONNECTING))
      return;

    const protocol    = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
    const ws          = new WebSocket(`${protocol}//${window.location.host}/ws/social`);

    ws.onopen = () => {
      if (!mountedRef.current) { ws.close(); return; }
      setConnected(true);
      retriesRef.current = 0;

      pingTimer.current = setInterval(() => {
        if (ws.readyState !== WebSocket.OPEN) return;
        ws.send('ping');
        pongTimer.current = setTimeout(() => {
          ws.close();
        }, PONG_TIMEOUT);
      }, PING_INTERVAL);
    };

    ws.onmessage = (event) => {
      if (!mountedRef.current) return;

      if (event.data === 'pong') {
        if (pongTimer.current) { clearTimeout(pongTimer.current); pongTimer.current = null; }
        return;
      }

      try {
        const data = JSON.parse(event.data) as SocialEvent;
        setLastEvent(data);

        switch (data.type) {
          case 'friends_online':
            setOnlineIds(new Set(data.userIds));
            break;

          case 'friend_online':
            setOnlineIds(prev => { const next = new Set(prev); next.add(data.user.id); return next; });
            break;

          case 'friend_offline':
            setOnlineIds(prev => { const next = new Set(prev); next.delete(data.user.id); return next; });
            break;

          case 'friend_removed':
            setOnlineIds(prev => { const next = new Set(prev); next.delete(data.userId); return next; });
            break;

          case 'friend_request_accepted':
            if (data.user.isActive)
              setOnlineIds(prev => { const next = new Set(prev); next.add(data.user.id); return next; });
            break;
        }
      } catch {}
    };

    ws.onclose = () => {
      if (!mountedRef.current) return;
      clearTimers();
      setConnected(false);
      wsRef.current = null;
      const delay = Math.min(RECONNECT_BASE * 2 ** retriesRef.current, RECONNECT_MAX);
      retriesRef.current++;
      reconnectTimer.current = setTimeout(() => { if (mountedRef.current) connect(); }, delay);
    };

    ws.onerror = () => { ws.close(); };

    wsRef.current = ws;
  }, [loggedIn, clearTimers]);

  useEffect(() => {
    mountedRef.current = true;
    const initTimer = setTimeout(() => { if (mountedRef.current) connect(); }, 100);

    return () => {
      mountedRef.current = false;
      clearTimeout(initTimer);
      clearTimers();
      if (wsRef.current) { wsRef.current.close(); wsRef.current = null; }
    };
  }, [connect, clearTimers]);

  const sendChatMessage = useCallback((to: number, content: string) => {
    if (wsRef.current && wsRef.current.readyState === WebSocket.OPEN)
      wsRef.current.send(JSON.stringify({ type: 'chat_send', to, content }));
  }, []);

  const requestChatHistory = useCallback((friendId: number) => {
    if (wsRef.current && wsRef.current.readyState === WebSocket.OPEN)
      wsRef.current.send(JSON.stringify({ type: 'chat_history', friendId }));
  }, []);

  return { onlineIds, lastEvent, connected, sendChatMessage, requestChatHistory };
}

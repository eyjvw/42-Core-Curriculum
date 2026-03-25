import { useEffect, useMemo, useRef, useState } from 'react';

interface Card {
  suit: string;
  rank: string;
  value: number;
}

interface PlayerHand {
  cards: Card[];
  total: number;
  isBusted: boolean;
}

interface GamePlayer {
  id: string;
  username: string;
  hand: PlayerHand;
  bet: number;
  balance: number;
  status: 'betting' | 'playing' | 'standing' | 'busted' | 'blackjack' | 'finished';
  result?: 'win' | 'lose' | 'push' | 'blackjack';
  winnings?: number;
}

interface GameState {
  gameId: string;
  dealerHand: {
    cards: Card[];
    total: number;
    isBusted: boolean;
    hidden: boolean;
  };
  players: GamePlayer[];
  currentPlayerId: string | null;
  currentPlayerIndex: number;
  status: 'betting' | 'dealing' | 'playing' | 'dealer_turn' | 'finished';
}

interface RoomPlayer {
  id: string;
  username: string;
  role: string;
  balance: number;
  bet: number;
  isConnected: boolean;
}

export interface Room {
  id: string;
  code: string;
  hostId: string;
  status: 'waiting' | 'betting' | 'playing' | 'finished';
  playerCount: number;
  maxPlayers: number;
  spectatorCount: number;
  players?: RoomPlayer[];
  spectators?: Array<{ id: string; username: string; role: string; isConnected: boolean }>;
  game?: GameState | null;
}

interface MultiplayerProps {
  onClose: () => void;
  onBalanceUpdate: (balance: number) => void;
  initialBalance: number;
  userId?: number;
  username?: string;
  initialRoom?: Room;
}

const SUIT_SYMBOLS: Record<string, string> = {
  hearts: '♥',
  diamonds: '♦',
  clubs: '♣',
  spades: '♠',
};

const SUIT_COLORS: Record<string, string> = {
  hearts: '#ff4757',
  diamonds: '#ff4757',
  clubs: '#1a1a2e',
  spades: '#1a1a2e',
};

function removePlayerFromRoomState(room: Room, playerId: string): Room {
  const nextPlayers = room.players?.filter((p) => p.id !== playerId) || [];
  const nextSpectators = room.spectators?.filter((p) => p.id !== playerId) || [];
  let nextHostId = room.hostId;
  if (nextHostId === playerId && nextPlayers.length > 0) nextHostId = nextPlayers[0]!.id;
  return { ...room, hostId: nextHostId, players: nextPlayers, spectators: nextSpectators, playerCount: nextPlayers.length, spectatorCount: nextSpectators.length };
}

function CardComponent({ card, hidden = false, order = 0 }: { card: Card; hidden?: boolean; order?: number }) {
  const isHidden = hidden || card.rank === '?';
  const symbol = SUIT_SYMBOLS[card.suit] || '?';
  const color = SUIT_COLORS[card.suit] || '#1a1a2e';
  return (
    <div className={`stake-card ${isHidden ? 'hidden' : ''}`} style={{ animationDelay: `${order * 80}ms` }}>
      {isHidden ? (
        <div className="stake-card-back">🎴</div>
      ) : (
        <>
          <div className="stake-card-corner top" style={{ color }}>
            <span className="rank">{card.rank}</span>
            <span className="suit">{symbol}</span>
          </div>
          <div className="stake-card-center" style={{ color }}>{symbol}</div>
          <div className="stake-card-corner bottom" style={{ color }}>
            <span className="rank">{card.rank}</span>
            <span className="suit">{symbol}</span>
          </div>
        </>
      )}
    </div>
  );
}

export default function MultiplayerBlackjack({ onClose, onBalanceUpdate, initialBalance, userId, initialRoom: initialRoomProp }: MultiplayerProps) {
  const [currentRoom, setCurrentRoom] = useState<Room | null>(initialRoomProp ?? null);
  const [gameState, setGameState] = useState<GameState | null>(initialRoomProp?.game ?? null);
  const [loading, setLoading] = useState(!initialRoomProp);
  const [error, setError] = useState<string | null>(null);
  const [bet, setBet] = useState(10);
  const [kicked, setKicked] = useState(false);
  const [showResult, setShowResult] = useState(false);
  const [winnings, setWinnings] = useState<number | null>(null);
  const [balance, setBalance] = useState(initialBalance);
  const [codeCopied, setCodeCopied] = useState(false);
  const wsRef = useRef<WebSocket | null>(null);

  const myUserId = String(userId);
  const isHost = currentRoom?.hostId === myUserId;
  const isPlaying = currentRoom?.status === 'playing';

  const myRoomPlayer = useMemo(
    () => currentRoom?.players?.find((p) => p.id === myUserId),
    [currentRoom, myUserId]
  );
  const myGamePlayer = useMemo(
    () => gameState?.players?.find((p) => p.id === myUserId),
    [gameState, myUserId]
  );
  const isMyTurn = gameState?.currentPlayerId === myUserId;

  useEffect(() => {
    const newBalance = myGamePlayer?.balance ?? myRoomPlayer?.balance;
    if (newBalance !== undefined && newBalance !== balance) {
      setBalance(newBalance);
      onBalanceUpdate(newBalance);
    }
  }, [myGamePlayer, myRoomPlayer]);

  useEffect(() => {
    if (currentRoom?.status === 'finished' && gameState) {
      setShowResult(true);
      setWinnings(gameState.players.find((p) => p.id === myUserId)?.winnings ?? null);
      const timer = setTimeout(() => setShowResult(false), 3000);
      return () => clearTimeout(timer);
    }
    setShowResult(false);
    return undefined;
  }, [currentRoom?.status, gameState, myUserId]);

  useEffect(() => {
    (async () => {
      if (!initialRoomProp) setLoading(true);
      try {
        const res = await fetch('/api/games/rooms/my-room', { credentials: 'include' });
        if (!res.ok)
        {
          if (!initialRoomProp) setError('No active room found');
          setLoading(false);
          return;
        }
        const data = await res.json();
        if (data.room) { setCurrentRoom(data.room); setGameState(data.room.game || null); }
        else if (!initialRoomProp) setError(data.error || 'No active room found');
      } catch { if (!initialRoomProp) setError('Failed to load room'); }
      setLoading(false);
    })();
  }, []);

  useEffect(() => {
    if (!currentRoom || kicked) return;
    let retries = 0;
    let reconnectTimer: ReturnType<typeof setTimeout> | null = null;
    let alive = true;
    let activeWs: WebSocket | null = null;

    const connectWs = () => {
      if (!alive) return;
      const protocol = window.location.protocol === 'https:' ? 'wss:' : 'ws:';
      const ws = new WebSocket(`${protocol}//${window.location.host}/api/games/rooms/${currentRoom.id}/ws`);
      activeWs = ws;

      ws.onopen = () => {
        if (!alive) { ws.close(); return; }
        retries = 0;
        wsRef.current = ws;
      };

      ws.onmessage = (event) => {
        if (!alive) return;
        try {
          const data = JSON.parse(event.data);
          if (data.type === 'room-update' && data.room) {
            setCurrentRoom(data.room);
            setGameState(data.room.game || null);
          } else if (data.type === 'game_state' && data.payload) {
            setGameState(data.payload);
          } else if (data.type === 'player_kicked' && data.payload?.kickedUserId === myUserId) {
            setKicked(true);
          } else if (data.type === 'player_kicked' && data.payload?.kickedUserId) {
            const id = String(data.payload.kickedUserId);
            setCurrentRoom((prev) => prev ? removePlayerFromRoomState(prev, id) : prev);
            setGameState((prev) => prev ? { ...prev, players: prev.players.filter((p) => p.id !== id) } : prev);
          } else if ((data.type === 'leave' || data.type === 'player_disconnected') && data.playerId) {
            const id = String(data.playerId);
            setCurrentRoom((prev) => prev ? removePlayerFromRoomState(prev, id) : prev);
            setGameState((prev) => prev ? { ...prev, players: prev.players.filter((p) => p.id !== id) } : prev);
          }
        } catch {}
      };

      ws.onclose = () => {
        if (wsRef.current === ws) wsRef.current = null;
        activeWs = null;
        if (!alive || kicked) return;
        const delay = Math.min(2000 * 2 ** retries, 30000);
        retries++;
        reconnectTimer = setTimeout(connectWs, delay);
      };

      ws.onerror = () => {};
    };

    connectWs();

    return () => {
      alive = false;
      if (reconnectTimer) clearTimeout(reconnectTimer);
      if (activeWs) {
        activeWs.onmessage = null;
        activeWs.onerror = null;
        if (activeWs.readyState === WebSocket.CONNECTING) {
          const pending = activeWs;
          pending.onopen = () => pending.close();
          pending.onclose = null;
        } else {
          activeWs.onclose = null;
          activeWs.close();
        }
      }
      wsRef.current = null;
    };
  }, [currentRoom?.id, kicked, myUserId]);

  const api = async (path: string, body: Record<string, unknown>) => {
    const res = await fetch(`/api/games/rooms/${path}`, {
      method: 'POST', credentials: 'include',
      headers: { 'Content-Type': 'application/json' },
      body: JSON.stringify(body),
    });
    return res.json();
  };

  const startGame = async () => {
    if (!currentRoom) return;
    setError(null);
    const data = await api('start', { roomId: currentRoom.id });
    if (data.error) setError(data.error);
    else if (data.room) { setCurrentRoom(data.room); setGameState(data.room.game || null); }
  };

  const placeBet = async () => {
    if (!currentRoom || bet < 1) return;
    setLoading(true); setError(null);
    const data = await api('bet', { roomId: currentRoom.id, bet });
    if (data.error) setError(data.error);
    setLoading(false);
  };

  const hit = async () => {
    if (!currentRoom) return;
    setLoading(true); setError(null);
    const data = await api('hit', { roomId: currentRoom.id });
    if (data.error) setError(data.error);
    if (data.game) setGameState(data.game);
    setLoading(false);
  };

  const stand = async () => {
    if (!currentRoom) return;
    setLoading(true); setError(null);
    const data = await api('stand', { roomId: currentRoom.id });
    if (data.error) setError(data.error);
    if (data.game) setGameState(data.game);
    setLoading(false);
  };

  const doubleDown = async () => {
    if (!currentRoom) return;
    setLoading(true); setError(null);
    const data = await api('double', { roomId: currentRoom.id });
    if (data.error) setError(data.error);
    if (data.game) setGameState(data.game);
    setLoading(false);
  };

  const kickPlayer = async (targetUserId: string) => {
    if (!currentRoom) return;
    const data = await api('kick', { roomId: currentRoom.id, targetUserId });
    if (data.error) setError(data.error);
    else if (data.room) { setCurrentRoom(data.room); if (data.room.game) setGameState(data.room.game); }
  };

  const newRound = async () => {
    if (!currentRoom) return;
    setLoading(true); setError(null);
    const data = await api('new-round', { roomId: currentRoom.id });
    if (data.error) setError(data.error);
    else { setGameState(null); setBet(10); }
    setLoading(false);
  };

  const leaveRoom = async () => {
    if (currentRoom) { try { await api('leave', { roomId: currentRoom.id }); } catch {} }
    onClose();
  };

  const addBot = async () => {
    if (!currentRoom) return;
    setError(null);
    try {
      const data = await api('add-bot', { roomId: currentRoom.id });
      if (data.error) setError(data.error);
      else if (data.room) setCurrentRoom(data.room);
    } catch {
      setError('Failed to add bot');
    }
  };

  const copyRoomCode = () => {
    if (!currentRoom) return;
    const text = currentRoom.code;
    const onSuccess = () => { setCodeCopied(true); setTimeout(() => setCodeCopied(false), 2000); };
    if (navigator.clipboard?.writeText) {
      navigator.clipboard.writeText(text).then(onSuccess).catch(() => {});
    } else {
      const ta = document.createElement('textarea');
      ta.value = text;
      ta.style.position = 'fixed';
      ta.style.opacity = '0';
      document.body.appendChild(ta);
      ta.select();
      try { document.execCommand('copy'); onSuccess(); } catch {}
      document.body.removeChild(ta);
    }
  };

  const multiplyBet = (multiplier: number) => {
    const max = myRoomPlayer?.balance ?? balance;
    setBet(Math.min(max, Math.max(1, Math.floor(bet * multiplier))));
  };

  const getResultInfo = () => {
    const mine = gameState?.players.find((p) => p.id === myUserId);
    if (!mine?.result) return null;
    switch (mine.result) {
      case 'blackjack': return { text: 'BLACKJACK!', color: '#ffd700' };
      case 'win':       return { text: 'YOU WIN!',   color: '#00d26a' };
      case 'lose':      return { text: 'YOU LOSE',   color: '#ff4757' };
      case 'push':      return { text: 'PUSH',        color: '#ffa502' };
      default: return null;
    }
  };

  const resultInfo = getResultInfo();
  const betIsLocked = (myRoomPlayer?.bet || 0) > 0;
  const currentBetMax = myRoomPlayer?.balance ?? balance;
  const waitingFor = gameState?.players.find((p) => p.id === gameState.currentPlayerId)?.username;

  if (loading && !currentRoom) {
    return (
      <div className="stake-bj-container" style={{ alignItems: 'center', justifyContent: 'center' }}>
        <div style={{ color: '#fff', fontSize: '18px' }}>Loading room...</div>
      </div>
    );
  }

  if (kicked) {
    return (
      <div className="stake-bj-container" style={{ alignItems: 'center', justifyContent: 'center' }}>
        <div className="stake-bj-sidebar" style={{ maxWidth: '420px', width: '100%' }}>
          <div className="stake-bj-header">
            <div className="stake-bj-title"><span className="stake-bj-icon">🃏</span><span>Blackjack</span></div>
            <button className="stake-bj-close" onClick={onClose}>✕</button>
          </div>
          <div className="stake-bj-bet-section">
            <div className="stake-bj-error">You have been kicked from this room.</div>
            <button className="stake-bj-deal-btn" onClick={onClose}>Back</button>
          </div>
        </div>
      </div>
    );
  }

  if (!currentRoom) {
    return (
      <div className="stake-bj-container" style={{ alignItems: 'center', justifyContent: 'center' }}>
        <div className="stake-bj-sidebar" style={{ maxWidth: '420px', width: '100%' }}>
          <div className="stake-bj-header">
            <div className="stake-bj-title"><span className="stake-bj-icon">🃏</span><span>Blackjack</span></div>
            <button className="stake-bj-close" onClick={onClose}>✕</button>
          </div>
          <div className="stake-bj-bet-section">
            <div className="stake-bj-error">{error || 'No active room found.'}</div>
            <button className="stake-bj-deal-btn" onClick={onClose}>Back</button>
          </div>
        </div>
      </div>
    );
  }

  if (currentRoom.status === 'waiting') {
    return (
      <div style={{ position: 'fixed', inset: 0, display: 'flex', alignItems: 'center', justifyContent: 'center', background: 'rgba(0,0,0,0.75)', zIndex: 9999 }}>
        <div style={{ background: '#1a2c38', borderRadius: '16px', padding: '32px', width: '100%', maxWidth: '480px', boxShadow: '0 24px 64px rgba(0,0,0,0.7)', border: '1px solid rgba(255,255,255,0.1)', color: '#fff' }}>

          <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'space-between', marginBottom: '24px' }}>
            <div style={{ display: 'flex', alignItems: 'center', gap: '10px' }}>
              <span style={{ fontSize: '24px' }}>🃏</span>
              <span style={{ fontSize: '20px', fontWeight: 700 }}>Room Lobby</span>
            </div>
            <button onClick={leaveRoom} style={{ background: 'rgba(255,255,255,0.1)', border: 'none', color: '#fff', width: '32px', height: '32px', borderRadius: '6px', cursor: 'pointer', fontSize: '16px', display: 'flex', alignItems: 'center', justifyContent: 'center' }}>✕</button>
          </div>

          <div style={{ textAlign: 'center', marginBottom: '24px', padding: '16px', background: 'rgba(0,0,0,0.35)', borderRadius: '10px', border: '1px solid rgba(255,255,255,0.1)' }}>
            <div style={{ fontSize: '11px', color: '#9ec2ff', marginBottom: '8px', letterSpacing: '1px', textTransform: 'uppercase' }}>Room Code</div>
            <div style={{ display: 'flex', alignItems: 'center', justifyContent: 'center', gap: '10px' }}>
              <span style={{ fontSize: '28px', fontWeight: 700, letterSpacing: '6px', color: '#ffd700', fontFamily: 'monospace' }}>{currentRoom.code}</span>
              <button onClick={copyRoomCode} title="Copy code" style={{ background: codeCopied ? 'rgba(0,215,106,0.2)' : 'rgba(255,255,255,0.1)', border: '1px solid rgba(255,255,255,0.2)', borderRadius: '4px', color: codeCopied ? '#00d26a' : '#fff', cursor: 'pointer', padding: '4px 8px', fontSize: '13px' }}>
                {codeCopied ? '✓ Copied' : '⧉ Copy'}
              </button>
            </div>
            <div style={{ fontSize: '11px', color: 'rgba(255,255,255,0.4)', marginTop: '8px' }}>{currentRoom.playerCount}/{currentRoom.maxPlayers} players</div>
          </div>

          <div style={{ display: 'flex', flexDirection: 'column', gap: '8px', marginBottom: '24px' }}>
            {(currentRoom.players ?? []).map((player) => (
              <div key={player.id} style={{ display: 'flex', alignItems: 'center', gap: '12px', background: player.id === myUserId ? 'rgba(158,194,255,0.08)' : 'rgba(0,0,0,0.3)', border: player.id === myUserId ? '1px solid rgba(158,194,255,0.25)' : '1px solid rgba(255,255,255,0.08)', borderRadius: '8px', padding: '10px 14px' }}>
                <div style={{ width: '30px', height: '30px', borderRadius: '50%', background: 'rgba(255,255,255,0.12)', display: 'flex', alignItems: 'center', justifyContent: 'center', fontSize: '13px', fontWeight: 700, flexShrink: 0 }}>
                  {player.username.slice(0, 1).toUpperCase()}
                </div>
                <span style={{ flex: 1, fontWeight: 600, fontSize: '14px' }}>{player.username}</span>
                {player.id === currentRoom.hostId && <span style={{ color: '#ffd700', fontSize: '12px' }}>★ Host</span>}
                {player.id === myUserId && <span style={{ color: '#9ec2ff', fontSize: '11px' }}>(you)</span>}
                {player.role === 'bot' && <span style={{ color: '#ffa502', fontSize: '11px' }}>🤖 Bot</span>}
                <span style={{ width: '7px', height: '7px', borderRadius: '50%', background: player.isConnected ? '#00d26a' : '#888', display: 'inline-block', flexShrink: 0 }} />
                {isHost && player.id !== myUserId && (
                  <button onClick={() => kickPlayer(player.id)} style={{ background: 'none', border: 'none', color: '#ff4757', cursor: 'pointer', fontSize: '13px', padding: '2px 4px' }}>✕</button>
                )}
              </div>
            ))}
            {Array.from({ length: currentRoom.maxPlayers - (currentRoom.players?.length ?? 0) }).map((_, i) => (
              <div key={`empty-${i}`} style={{ display: 'flex', alignItems: 'center', gap: '12px', border: '1px dashed rgba(255,255,255,0.12)', borderRadius: '8px', padding: '10px 14px', color: 'rgba(255,255,255,0.25)', fontSize: '13px' }}>
                <div style={{ width: '30px', height: '30px', borderRadius: '50%', background: 'rgba(255,255,255,0.05)', display: 'flex', alignItems: 'center', justifyContent: 'center', fontSize: '16px' }}>+</div>
                <span>Waiting for player…</span>
              </div>
            ))}
          </div>

          {error && <div className="stake-bj-error" style={{ marginBottom: '16px' }}>{error}</div>}

          {isHost && currentRoom.playerCount < currentRoom.maxPlayers && (
            <button
              onClick={addBot}
              disabled={loading}
              style={{ width: '100%', marginBottom: '10px', padding: '11px', background: 'rgba(255,165,0,0.12)', border: '1px solid rgba(255,165,0,0.35)', borderRadius: '8px', color: '#ffa502', cursor: 'pointer', fontSize: '14px', fontWeight: 500 }}
            >
              🤖 Add Bot Player
            </button>
          )}

          {isHost ? (
            <button className="stake-bj-deal-btn" onClick={startGame} disabled={loading || currentRoom.playerCount < 1}>
              {loading ? 'Starting…' : '▶ Start Game'}
            </button>
          ) : (
            <div style={{ textAlign: 'center', color: '#9ec2ff', fontSize: '14px', padding: '14px 0' }}>Waiting for host to start…</div>
          )}
          <button onClick={leaveRoom} style={{ width: '100%', marginTop: '12px', padding: '12px', background: 'rgba(255,255,255,0.06)', border: '1px solid rgba(255,255,255,0.15)', borderRadius: '8px', color: 'rgba(255,255,255,0.7)', cursor: 'pointer', fontSize: '14px', fontWeight: 500 }}>
            Leave Room
          </button>
        </div>
      </div>
    );
  }

  return (
    <div className="stake-bj-container">
      {error && (
        <div style={{ position: 'fixed', top: '10px', left: '50%', transform: 'translateX(-50%)', background: '#ff4757', color: 'white', padding: '12px 20px', borderRadius: '6px', zIndex: 9999, fontSize: '14px', maxWidth: '90%' }}>
          ❌ {error}
        </div>
      )}

      <div className="stake-bj-sidebar">
        <div className="stake-bj-header">
          <div className="stake-bj-title">
            <span className="stake-bj-icon">🃏</span>
            <span>Blackjack</span>
          </div>
          <button className="stake-bj-close" onClick={leaveRoom}>✕</button>
        </div>

        <div className="stake-bj-bet-section">
          <label className="stake-bj-label">Bet Amount</label>
          <div className="stake-bj-input-wrapper">
            <span className="stake-bj-currency">$</span>
            <input
              type="number"
              value={bet}
              onChange={(e) => setBet(Math.max(1, Math.min(currentBetMax, parseInt(e.target.value) || 1)))}
              disabled={isPlaying || betIsLocked}
              className="stake-bj-input"
            />
            <div className="stake-bj-input-btns">
              <button onClick={() => multiplyBet(0.5)} disabled={isPlaying || betIsLocked}>½</button>
              <button onClick={() => multiplyBet(2)}   disabled={isPlaying || betIsLocked}>2×</button>
            </div>
          </div>

          <div className="stake-bj-quick-bets">
            {[10, 50, 100, 500].map((amount) => (
              <button
                key={amount}
                onClick={() => setBet(Math.min(currentBetMax, amount))}
                disabled={isPlaying || betIsLocked}
                className={bet === amount ? 'active' : ''}
              >
                ${amount}
              </button>
            ))}
            <button
              onClick={() => setBet(currentBetMax)}
              disabled={isPlaying || betIsLocked}
              className={bet === currentBetMax ? 'active' : ''}
            >
              Max
            </button>
          </div>

          {error && <div className="stake-bj-error">{error}</div>}

          {!isPlaying ? (
            <>
              {currentRoom.status === 'betting' && !betIsLocked && currentBetMax > 0 && (
                <button
                  className="stake-bj-deal-btn"
                  onClick={placeBet}
                  disabled={loading || bet > currentBetMax || bet < 1}
                >
                  {loading ? 'Placing...' : 'Bet'}
                </button>
              )}
              {currentRoom.status === 'betting' && currentBetMax <= 0 && (
                <div style={{ textAlign: 'center', color: '#ff4757', fontSize: '13px', marginTop: '12px' }}>
                  You're broke! Spectating this round…
                </div>
              )}
              {currentRoom.status === 'betting' && betIsLocked && (
                <div style={{ textAlign: 'center', color: '#9ec2ff', fontSize: '13px', marginTop: '12px' }}>
                  ✓ Bet locked: ${myRoomPlayer?.bet} — waiting for others…
                  <div style={{ marginTop: '6px', fontSize: '11px', color: 'rgba(255,255,255,0.4)' }}>
                    {currentRoom.players?.filter((p) => p.bet > 0).length}/{currentRoom.players?.filter((p) => p.balance > 0).length} players ready
                  </div>
                </div>
              )}
              {currentRoom.status === 'finished' && isHost && (
                <button className="stake-bj-deal-btn" onClick={newRound} disabled={loading}>
                  {loading ? 'Starting...' : 'New Round'}
                </button>
              )}
              {currentRoom.status === 'finished' && !isHost && (
                <div style={{ textAlign: 'center', color: '#9ec2ff', fontSize: '13px', marginTop: '12px' }}>
                  Waiting for host to start a new round...
                </div>
              )}
            </>
          ) : (
            <div className="stake-bj-actions">
              <button className="stake-bj-action hit"    onClick={hit}        disabled={loading || !isMyTurn || myGamePlayer?.status !== 'playing'}>Hit</button>
              <button className="stake-bj-action stand"  onClick={stand}      disabled={loading || !isMyTurn || myGamePlayer?.status !== 'playing'}>Stand</button>
              <button className="stake-bj-action double" onClick={doubleDown} disabled={loading || !isMyTurn || myGamePlayer?.status !== 'playing' || (myGamePlayer?.hand.cards.length || 0) !== 2 || (myGamePlayer?.balance || 0) < (myGamePlayer?.bet || 0)}>
                Double
              </button>
            </div>
          )}

          {isPlaying && !isMyTurn && (
            <div style={{ textAlign: 'center', color: '#9ec2ff', fontSize: '13px', marginTop: '12px' }}>
              Waiting for {waitingFor || 'player'}...
            </div>
          )}

          {winnings !== null && winnings > 0 && (
            <div className="stake-bj-winnings">+${winnings.toLocaleString()}</div>
          )}
        </div>

        <div className="stake-bj-balance">
          <span>Balance</span>
          <span className="amount">${balance.toLocaleString()}</span>
        </div>
      </div>

      <div className="stake-bj-game">

        <div className="stake-bj-table">

          <div className="stake-bj-dealer">
            <div className="stake-bj-label-text">
              DEALER {gameState && !gameState.dealerHand.hidden ? `(${gameState.dealerHand.total})` : ''}
            </div>
            <div className="stake-bj-cards">
              {gameState?.dealerHand.cards.map((card, idx) => (
                <CardComponent
                  key={`dealer-${gameState.gameId}-${card.suit}-${card.rank}-${idx}`}
                  card={card}
                  hidden={gameState.dealerHand.hidden && idx === 1}
                  order={idx}
                />
              ))}
            </div>
          </div>

          {showResult && resultInfo && (
            <div className="stake-bj-result" style={{ color: resultInfo.color }}>
              {resultInfo.text}
              {winnings !== null && winnings > 0 && <div className="stake-bj-result-amount">+${winnings}</div>}
            </div>
          )}

          <div style={{ display: 'flex', gap: '32px', justifyContent: 'center', alignItems: 'flex-end', flexWrap: 'wrap', width: '100%', padding: '0 12px' }}>
            {myGamePlayer && (
              <div style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', gap: '6px', position: 'relative' }}>
                {myGamePlayer.id === gameState?.currentPlayerId && (
                  <div style={{ position: 'absolute', top: '-18px', fontSize: '10px', color: '#ffd700', fontWeight: 700, letterSpacing: '1px', textTransform: 'uppercase' }}>▼ YOUR TURN</div>
                )}
                <div className="stake-bj-cards">
                  {myGamePlayer.hand.cards.map((card, idx) => (
                    <CardComponent key={`me-${myGamePlayer.id}-${card.suit}-${card.rank}-${idx}`} card={card} order={idx} />
                  ))}
                </div>
                <div className="stake-bj-label-text" style={{ fontSize: '12px' }}>
                  YOU ({myGamePlayer.hand.total})
                  {myGamePlayer.hand.isBusted && <span style={{ color: '#ff4757', marginLeft: '4px' }}>BUST</span>}
                  {myGamePlayer.status === 'blackjack' && <span style={{ color: '#ffd700', marginLeft: '4px' }}>BJ!</span>}
                  {myGamePlayer.result === 'win' && <span style={{ color: '#00d26a', marginLeft: '4px' }}>WIN</span>}
                  {myGamePlayer.result === 'lose' && <span style={{ color: '#ff4757', marginLeft: '4px' }}>LOSE</span>}
                  {myGamePlayer.result === 'push' && <span style={{ color: '#ffa502', marginLeft: '4px' }}>PUSH</span>}
                </div>
                <div style={{ fontSize: '11px', color: '#ffd700' }}>${myGamePlayer.bet}</div>
              </div>
            )}

            {gameState?.players.filter((p) => p.id !== myUserId).map((player) => (
              <div key={player.id} style={{ display: 'flex', flexDirection: 'column', alignItems: 'center', gap: '6px', position: 'relative' }}>
                {player.id === gameState.currentPlayerId && (
                  <div style={{ position: 'absolute', top: '-18px', fontSize: '10px', color: '#ffd700', fontWeight: 700, letterSpacing: '1px', textTransform: 'uppercase' }}>▼ PLAYING</div>
                )}
                <div className="stake-bj-cards">
                  {player.hand.cards.map((card, idx) => (
                    <CardComponent key={`${player.id}-${card.suit}-${card.rank}-${idx}`} card={card} order={idx} />
                  ))}
                </div>
                <div style={{ fontSize: '12px', fontWeight: 700, color: 'rgba(255,255,255,0.7)', textTransform: 'uppercase', letterSpacing: '1px' }}>
                  {player.username} ({player.hand.total})
                  {player.hand.isBusted && <span style={{ color: '#ff4757', marginLeft: '4px' }}>BUST</span>}
                  {player.status === 'blackjack' && <span style={{ color: '#ffd700', marginLeft: '4px' }}>BJ!</span>}
                  {player.result === 'win' && <span style={{ color: '#00d26a', marginLeft: '4px' }}>WIN</span>}
                  {player.result === 'lose' && <span style={{ color: '#ff4757', marginLeft: '4px' }}>LOSE</span>}
                  {player.result === 'push' && <span style={{ color: '#ffa502', marginLeft: '4px' }}>PUSH</span>}
                </div>
                <div style={{ fontSize: '11px', color: '#ffd700' }}>${player.bet}</div>
              </div>
            ))}
          </div>

        </div>

        {!gameState && currentRoom.players && currentRoom.players.filter((p) => p.id !== myUserId).length > 0 && (
          <div style={{ display: 'flex', gap: '12px', flexWrap: 'wrap', justifyContent: 'center', marginTop: '16px', padding: '0 12px' }}>
            {currentRoom.players.filter((p) => p.id !== myUserId).map((player) => (
              <div key={player.id} style={{
                background: 'rgba(0,0,0,0.3)',
                border: '1px solid rgba(255,255,255,0.12)',
                borderRadius: '10px',
                padding: '8px 14px',
                fontSize: '13px',
                color: player.isConnected ? '#fff' : '#888',
                display: 'flex',
                alignItems: 'center',
                gap: '8px',
              }}>
                <span>{player.username}</span>
                {player.id === currentRoom.hostId && <span style={{ color: '#ffd700' }}>★</span>}
                {!player.isConnected && <span style={{ color: '#ff7b7b', fontSize: '11px' }}>offline</span>}
                {currentRoom.status === 'betting' && player.bet > 0 && <span style={{ color: '#00e701', fontSize: '11px' }}>✓ ${player.bet}</span>}
                {currentRoom.status === 'betting' && player.bet <= 0 && player.balance > 0 && <span style={{ color: '#ffa502', fontSize: '11px' }}>Betting…</span>}
                {currentRoom.status === 'betting' && player.balance <= 0 && <span style={{ color: '#888', fontSize: '11px' }}>Broke</span>}
                {currentRoom.status !== 'betting' && player.bet > 0 && <span style={{ color: '#00e701', fontSize: '11px' }}>${player.bet}</span>}
                {isHost && player.id !== myUserId && (
                  <button onClick={() => kickPlayer(player.id)} style={{ fontSize: '10px', color: '#ff4757', background: 'none', border: 'none', cursor: 'pointer' }}>✕</button>
                )}
              </div>
            ))}
          </div>
        )}

        <div style={{ position: 'absolute', top: '10px', right: '10px', fontSize: '11px', color: 'rgba(255,255,255,0.3)', letterSpacing: '1px' }}>
          {currentRoom.code}
        </div>
      </div>
    </div>
  );
}

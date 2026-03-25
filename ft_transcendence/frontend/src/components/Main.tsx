import { useState, useEffect, useCallback, useRef }	from 'react';
import { useTranslation }					from 'react-i18next';
import type { User }						from '../types/auth';
import FriendsList							from './FriendsList';
import ChatWindow							from './ChatWindow';
import Blackjack							from './Blackjack';
import MultiplayerBlackjack					from './MultiplayerBlackjack';
import type { Room }						from './MultiplayerBlackjack';
import { useSocialSocket }					from '../hooks/useSocialSocket';
import type { SocialEvent }					from '../hooks/useSocialSocket';
import type { Friend }						from '../services/types';
import blackjackImg							from '../assets/blackjack.jpg';

interface Game {
  id:			string;
  name:			string;
  image:		string;
  players:		number;
  background:	string;
}

interface MainProps {
  user: User;
  onOpenProfile: () => void;
  onUserUpdate?: (user: User) => void;
}

export default function Main({ user, onOpenProfile, onUserUpdate }: MainProps)
{
  const { t }							= useTranslation();
  const [selectedGame, setSelectedGame]	= useState<Game | null>(null);
  const [selectedMode, setSelectedMode]	= useState<'solo' | 'multiplayer' | null>(null);
  const [multiplayerAction, setMultiplayerAction] = useState<'create' | 'join' | null>(null);
  const [codeInput, setCodeInput]		= useState('');
  const [mpLoading, setMpLoading]		= useState(false);
  const [mpError, setMpError]			= useState<string | null>(null);
  const [mounted, setMounted]			= useState(false);
  const [friendsOpen, setFriendsOpen]	= useState(false);
  const [chatFriend, setChatFriend]		= useState<Friend | null>(null);
  const [activeGame, setActiveGame]		= useState<string | null>(null);
  const [mpRoom, setMpRoom]             = useState<Room | null>(null);
  const [userCoins, setUserCoins]		= useState(user.coins ?? 1000);
  const [hasActiveRoom, setHasActiveRoom] = useState(false);
  const { onlineIds, lastEvent, sendChatMessage, requestChatHistory } = useSocialSocket(true);

  const balanceChannelRef = useRef<BroadcastChannel | null>(null);
  const gameChannelRef = useRef<BroadcastChannel | null>(null);

  useEffect(() => {
    setMounted(true);
    const channel = new BroadcastChannel('wallet_sync');
    balanceChannelRef.current = channel;
    channel.onmessage = (event) => {
      if (event.data?.type === 'balance_update' && typeof event.data.balance === 'number') {
        setUserCoins(event.data.balance);
      }
    };
    const gameChannel = new BroadcastChannel('game_state');
    gameChannelRef.current = gameChannel;
    gameChannel.onmessage = (event) => {
      if (event.data?.type === 'game_active') {
        setHasActiveRoom(true);
      } else if (event.data?.type === 'game_inactive') {
        setHasActiveRoom(false);
      }
    };
    return () => { channel.close(); gameChannel.close(); };
  }, []);

  useEffect(() => {
    setUserCoins(user.coins ?? 1000);
  }, [user.coins]);

  useEffect(() => {
    if (onUserUpdate && userCoins !== (user.coins ?? 1000)) {
      onUserUpdate({ ...user, coins: userCoins });
    }
  }, [userCoins]);

  useEffect(() => {
    const checkActiveRoom = async () => {
      try {
        const response = await fetch('/api/games/rooms/my-room', {
          method: 'GET',
          credentials: 'include',
        });
        if (!response.ok)
        {
          setHasActiveRoom(false);
          return;
        }
        const data = await response.json();
        setHasActiveRoom(!!data.room);
      } catch { setHasActiveRoom(false); }
    };
    checkActiveRoom();
    try {
      if (activeGame)
        gameChannelRef.current?.postMessage({ type: 'game_active' });
      else
        gameChannelRef.current?.postMessage({ type: 'game_inactive' });
    } catch {}
  }, [activeGame]);

  const handleBalanceUpdate = useCallback((newBalance: number) => {
    setUserCoins(newBalance);
    try { balanceChannelRef.current?.postMessage({ type: 'balance_update', balance: newBalance }); } catch {}
  }, []);

  const games: Game[] = [
    {
      id: 'blackjack',
      name: 'Blackjack',
      image: blackjackImg,
      players: 2341,
      background: 'linear-gradient(135deg, #1a1a2e 0%, #16213e 100%)',
    },
  ];

  if (!mounted)
    return null;

  const openGameModal = (game: Game) => {
    setSelectedGame(game);
    setSelectedMode(null);
  };

  const closeGameModal = () => {
    setSelectedGame(null);
    setSelectedMode(null);
    setMultiplayerAction(null);
    setCodeInput('');
    setMpError(null);
    setMpLoading(false);
  };

  const launchGame = async () => {
	if (!selectedGame || !selectedMode) return;
    if (activeGame || hasActiveRoom) {
      setMpError('You already have an active game. Finish or leave it first.');
      return;
    }
    if (selectedGame.id === 'blackjack') {
      if (selectedMode === 'solo') {
        setActiveGame('blackjack-solo');
      } else if (selectedMode === 'multiplayer') {
        setActiveGame('blackjack-multi');
      }
    }
    closeGameModal();
  };

  const createRoom = async () => {
    if (activeGame) {
      setMpError('You already have an active game. Finish it first.');
      return;
    }
    setMpLoading(true);
    setMpError(null);
    try {
      const response = await fetch('/api/games/rooms/create', {
        method: 'POST',
        credentials: 'include',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({}),
      });
      if (!response.ok)
      {
        const text = await response.text();
        try
        {
          const errData = JSON.parse(text);
          setMpError(errData.error || 'Failed to create room');
        }
        catch { setMpError('Server error: ' + (text || response.statusText)); }
        setMpLoading(false);
        return;
      }
      const data = await response.json();
      if (data.code) {
        setMpRoom(data.room ?? null);
        closeGameModal();
        setActiveGame('blackjack-multi');
      } else {
        setMpError(data.error || 'Failed to create room');
      }
    } catch {
      setMpError('Failed to create room');
    }
    setMpLoading(false);
  };

  const joinRoom = async () => {
    if (activeGame) {
      setMpError('You already have an active game. Finish it first.');
      return;
    }
    if (!codeInput.trim()) {
      setMpError('Please enter a room code');
      return;
    }
    setMpLoading(true);
    setMpError(null);
    try
    {
      const response = await fetch('/api/games/rooms/join', {
        method: 'POST',
        credentials: 'include',
        headers: { 'Content-Type': 'application/json' },
        body: JSON.stringify({ code: codeInput.toUpperCase() }),
      });
      if (!response.ok)
      {
        const text = await response.text();
        try
        {
          const errData = JSON.parse(text);
          setMpError(errData.error || 'Failed to join room');
        }
        catch { setMpError('Server error: ' + (text || response.statusText));}
        setMpLoading(false);
        return;
      }
      const data = await response.json();
      if (data.room) {
        setMpRoom(data.room);
        closeGameModal();
        setActiveGame('blackjack-multi');
      } else {
        setMpError(data.error || 'Failed to join room');
      }
    } catch {
      setMpError('Failed to join room');
    }
    setMpLoading(false);
  };

  const rejoinRoom = async () => {
    setMpError(null);
    closeGameModal();
    setActiveGame('blackjack-multi');
  };

  const leaveActiveRoom = async () => {
    setMpLoading(true);
    setMpError(null);
    try {
      const res = await fetch('/api/games/rooms/my-room', {
        method: 'GET',
        credentials: 'include',
      });
      const data = await res.json();
      if (data.room) {
        await fetch('/api/games/rooms/leave', {
          method: 'POST',
          credentials: 'include',
          headers: { 'Content-Type': 'application/json' },
          body: JSON.stringify({ roomId: data.room.id }),
        });
      }
      setHasActiveRoom(false);
    } catch {
      setMpError('Failed to leave room');
    }
    setMpLoading(false);
  };

  return (
    <div className="stake-container">
      <div className="header-icons">
          <div className="coins-pill">$ {Number(userCoins).toLocaleString()}</div>
          <button className="social-btn" title={t('main.friends')} onClick={() => setFriendsOpen(!friendsOpen)}>
            👥
          </button>
          <button className="profile-btn" title={t('main.profile')} onClick={onOpenProfile}>
            <div className="avatar-container">
              {user.avatarUrl ? (
                <img className="profile-avatar" src={user.avatarUrl} alt={user.username} />
              ) : (
                <div className="profile-avatar placeholder">
                  {user.username.slice(0, 1).toUpperCase()}
                </div>
              )}
              {user.isActive && <span className="online-indicator" title="Online"></span>}
            </div>
          </button>
      </div>

      <div className="casino-deco" aria-hidden="true">
        <span className="deco" style={{ top: '12%', left: '6%', fontSize: '38px', animationDelay: '0s' }}>🪙</span>
        <span className="deco" style={{ top: '18%', right: '8%', fontSize: '32px', animationDelay: '1.2s' }}>♠️</span>
        <span className="deco" style={{ top: '55%', left: '4%', fontSize: '36px', animationDelay: '0.6s' }}>🎰</span>
        <span className="deco" style={{ top: '70%', right: '5%', fontSize: '34px', animationDelay: '1.8s' }}>💎</span>
        <span className="deco" style={{ top: '40%', left: '8%', fontSize: '28px', animationDelay: '2.4s' }}>♥️</span>
        <span className="deco" style={{ top: '80%', left: '12%', fontSize: '30px', animationDelay: '0.3s' }}>🎲</span>
        <span className="deco" style={{ top: '35%', right: '6%', fontSize: '36px', animationDelay: '1.5s' }}>🪙</span>
        <span className="deco" style={{ top: '60%', right: '12%', fontSize: '26px', animationDelay: '2.1s' }}>♦️</span>
        <span className="deco" style={{ top: '85%', right: '10%', fontSize: '32px', animationDelay: '0.9s' }}>🃏</span>
        <span className="deco" style={{ top: '25%', left: '14%', fontSize: '24px', animationDelay: '1.7s' }}>♣️</span>
        <span className="deco" style={{ top: '48%', right: '15%', fontSize: '30px', animationDelay: '2.6s' }}>💰</span>
        <span className="deco" style={{ top: '90%', left: '25%', fontSize: '28px', animationDelay: '0.4s' }}>🪙</span>
        <span className="deco" style={{ top: '8%', left: '25%', fontSize: '26px', animationDelay: '3.0s' }}>🎰</span>
        <span className="deco" style={{ top: '15%', right: '22%', fontSize: '30px', animationDelay: '0.8s' }}>🪙</span>
        <span className="deco" style={{ top: '30%', left: '2%', fontSize: '32px', animationDelay: '2.0s' }}>💰</span>
        <span className="deco" style={{ top: '45%', left: '18%', fontSize: '22px', animationDelay: '3.3s' }}>♠️</span>
        <span className="deco" style={{ top: '65%', left: '22%', fontSize: '34px', animationDelay: '1.1s' }}>🎲</span>
        <span className="deco" style={{ top: '75%', right: '20%', fontSize: '28px', animationDelay: '2.8s' }}>♥️</span>
        <span className="deco" style={{ top: '50%', right: '3%', fontSize: '30px', animationDelay: '0.5s' }}>🃏</span>
        <span className="deco" style={{ top: '92%', right: '25%', fontSize: '26px', animationDelay: '1.9s' }}>💎</span>
        <span className="deco" style={{ top: '5%', right: '35%', fontSize: '24px', animationDelay: '3.5s' }}>♦️</span>
        <span className="deco" style={{ top: '38%', right: '25%', fontSize: '28px', animationDelay: '0.7s' }}>🪙</span>
        <span className="deco" style={{ top: '68%', left: '35%', fontSize: '22px', animationDelay: '2.3s' }}>♣️</span>
        <span className="deco" style={{ top: '88%', left: '5%', fontSize: '34px', animationDelay: '1.4s' }}>🎰</span>
        <span className="deco" style={{ top: '22%', left: '30%', fontSize: '20px', animationDelay: '3.1s' }}>💰</span>
        <span className="deco" style={{ top: '78%', right: '30%', fontSize: '26px', animationDelay: '0.2s' }}>🎲</span>
        <span className="deco" style={{ top: '95%', left: '40%', fontSize: '30px', animationDelay: '2.5s' }}>🪙</span>
        <span className="deco" style={{ top: '42%', left: '28%', fontSize: '24px', animationDelay: '1.6s' }}>💎</span>
      </div>

      <h1 className="logo">ft_gambling</h1>

      <section className="games-section">
        <div className="games-carousel">
          {games.map(game => (
            <div key={game.id} className="game-item">
              <div
                className="game-card-stake"
                style={{ background: game.background }}
                onClick={() => openGameModal(game)}
              >
                <img src={game.image} alt={game.name} loading="lazy" />
                <div className="game-card-overlay">
                  <h3>{game.name}</h3>
                  <p>Beat the dealer by getting as close to 21 as possible without going over. Aces count as 1 or 11.</p>
                </div>
              </div>
              <p className="players-count">
                🟢 {game.players.toLocaleString()} {t('main.players')}
              </p>
            </div>
          ))}
        </div>
      </section>

      {selectedGame && (
        <div className="modal-overlay" onClick={closeGameModal}>
          <div className="modal-stake" onClick={(e) => e.stopPropagation()}>
            <button className="close-btn" onClick={closeGameModal}>×</button>
            <div className="modal-info">
              <h2>{selectedGame.name}</h2>
              <p className="modal-players">
                {selectedGame.players.toLocaleString()} {t('main.playersOnline')}
              </p>
              
              {selectedMode === null ? (
                <>
                  <div className="mode-selector">
                    <button
                      className={`mode-btn ${selectedMode === 'solo' ? 'active' : ''}`}
                      onClick={() => setSelectedMode('solo')}
                    >
                      {t('main.modeSolo')}
                    </button>
                    <button
                      className={`mode-btn ${selectedMode === 'multiplayer' ? 'active' : ''}`}
                      onClick={() => setSelectedMode('multiplayer')}
                    >
                      Multiplayer
                    </button>
                  </div>
                </>
              ) : selectedMode === 'solo' ? (
                <div>
                  <button className="play-now-btn" onClick={launchGame}>
                    {t('main.launch')}
                  </button>
                  {mpError && (
                    <div style={{ 
                      background: 'rgba(255, 71, 87, 0.2)', 
                      border: '1px solid rgba(255, 71, 87, 0.4)',
                      color: '#ff4757',
                      padding: '12px',
                      borderRadius: '6px',
                      marginTop: '12px',
                      fontSize: '13px'
                    }}>
                      {mpError}
                    </div>
                  )}
                </div>
              ) : multiplayerAction === null ? (
                <div className="multiplayer-options">
                  {hasActiveRoom && (
                    <div style={{
                      background: 'rgba(255, 215, 0, 0.1)',
                      border: '1px solid rgba(255, 215, 0, 0.3)',
                      borderRadius: '8px',
                      padding: '14px',
                      marginBottom: '16px',
                    }}>
                      <div style={{ color: '#ffd700', fontSize: '13px', fontWeight: 600, marginBottom: '10px' }}>
                        ⚠️ You have an active room
                      </div>
                      <div style={{ display: 'flex', gap: '8px' }}>
                        <button
                          className="play-now-btn"
                          onClick={rejoinRoom}
                          disabled={mpLoading}
                          style={{ flex: 1, fontSize: '13px', padding: '10px' }}
                        >
                          {mpLoading ? 'Loading...' : '↩ Rejoin Room'}
                        </button>
                        <button
                          className="mode-btn"
                          onClick={leaveActiveRoom}
                          disabled={mpLoading}
                          style={{ flex: 1, fontSize: '13px', padding: '10px', color: '#ff4757', borderColor: 'rgba(255, 71, 87, 0.4)' }}
                        >
                          {mpLoading ? 'Leaving...' : '✕ Leave Room'}
                        </button>
                      </div>
                      {mpError && (
                        <div style={{ color: '#ff4757', fontSize: '12px', marginTop: '8px' }}>{mpError}</div>
                      )}
                    </div>
                  )}
                  <button 
                    className="play-now-btn"
                    onClick={() => setMultiplayerAction('create')}
                    disabled={hasActiveRoom}
                    style={{ marginBottom: '12px', opacity: hasActiveRoom ? 0.5 : 1 }}
                  >
                    + Create Room
                  </button>
                  <button 
                    className="play-now-btn"
                    onClick={() => setMultiplayerAction('join')}
                    disabled={hasActiveRoom}
                    style={{ opacity: hasActiveRoom ? 0.5 : 1 }}
                  >
                    🔗 Join Room
                  </button>
                </div>
              ) : multiplayerAction === 'create' ? (
                <div className="multiplayer-create">
                  <button 
                    className="play-now-btn"
                    onClick={createRoom}
                    disabled={mpLoading}
                    style={{ width: '100%', marginBottom: '12px' }}
                  >
                    {mpLoading ? 'Creating...' : 'Create Room'}
                  </button>
                  <button 
                    className="mode-btn"
                    onClick={() => setMultiplayerAction(null)}
                    style={{ width: '100%' }}
                  >
                    ← Back
                  </button>
                  {mpError && (
                    <div style={{ 
                      background: 'rgba(255, 71, 87, 0.2)', 
                      border: '1px solid rgba(255, 71, 87, 0.4)',
                      color: '#ff4757',
                      padding: '12px',
                      borderRadius: '6px',
                      marginTop: '12px',
                      fontSize: '13px'
                    }}>
                      {mpError}
                    </div>
                  )}
                </div>
              ) : (
                <div className="multiplayer-join">
                  <div style={{ marginBottom: '16px' }}>
                    <label style={{ display: 'block', fontSize: '14px', fontWeight: '600', marginBottom: '8px' }}>
                      Room Code
                    </label>
                    <input 
                      type="text"
                      placeholder="e.g., ABC123"
                      value={codeInput}
                      onChange={(e) => setCodeInput(e.target.value.toUpperCase())}
                      disabled={mpLoading}
                      maxLength={6}
                      onKeyPress={(e) => e.key === 'Enter' && joinRoom()}
                      style={{
                        width: '100%',
                        padding: '12px 16px',
                        fontSize: '16px',
                        fontWeight: '600',
                        textTransform: 'uppercase',
                        letterSpacing: '2px',
                        textAlign: 'center',
                        fontFamily: 'monospace',
                        borderRadius: '6px',
                        border: '2px solid rgba(255, 255, 255, 0.2)',
                        background: 'rgba(255, 255, 255, 0.05)',
                        color: '#fff'
                      }}
                    />
                  </div>
                  <button 
                    className="play-now-btn"
                    onClick={joinRoom}
                    disabled={mpLoading || !codeInput.trim()}
                    style={{ width: '100%', marginBottom: '12px' }}
                  >
                    {mpLoading ? 'Joining...' : 'Join Room'}
                  </button>
                  <button 
                    className="mode-btn"
                    onClick={() => setMultiplayerAction(null)}
                    style={{ width: '100%' }}
                  >
                    ← Back
                  </button>
                  {mpError && (
                    <div style={{ 
                      background: 'rgba(255, 71, 87, 0.2)', 
                      border: '1px solid rgba(255, 71, 87, 0.4)',
                      color: '#ff4757',
                      padding: '12px',
                      borderRadius: '6px',
                      marginTop: '12px',
                      fontSize: '13px'
                    }}>
                      {mpError}
                    </div>
                  )}
                </div>
              )}
            </div>
          </div>
        </div>
      )}

      <FriendsList
        open={friendsOpen}
        onClose={() => setFriendsOpen(false)}
        onlineIds={onlineIds}
        lastEvent={lastEvent}
        onOpenChat={(f: Friend) => { setChatFriend(f); setFriendsOpen(false); }}
      />

      {chatFriend && (
        <ChatWindow
          friendId={chatFriend.id}
          friendUsername={chatFriend.username}
          friendAvatarUrl={chatFriend.avatarUrl}
          currentUserId={user.id}
          lastEvent={lastEvent}
          onClose={() => setChatFriend(null)}
          sendChatMessage={sendChatMessage}
          requestChatHistory={requestChatHistory}
        />
      )}

      {activeGame === 'blackjack-solo' && (
        <Blackjack
          onClose={() => setActiveGame(null)}
          onBalanceUpdate={handleBalanceUpdate}
          initialBalance={userCoins}
        />
      )}

      {activeGame === 'blackjack-multi' && (
        <MultiplayerBlackjack
          onClose={() => {
            setActiveGame(null);
            setMpRoom(null);
            setSelectedMode(null);
            setMultiplayerAction(null);
          }}
          onBalanceUpdate={handleBalanceUpdate}
          initialBalance={userCoins}
          userId={user.id}
          username={user.username}
          initialRoom={mpRoom ?? undefined}
        />
      )}

      <style>{`
        * {
          box-sizing: border-box;
        }

        .stake-container {
          flex: 1;
          background-color: #0b1622;
          background-image:
            radial-gradient(circle at 15% 25%, rgba(64, 147, 238, 0.12), transparent 35%),
            radial-gradient(circle at 80% 20%, rgba(78, 196, 255, 0.08), transparent 40%),
            radial-gradient(circle at 20% 80%, rgba(120, 115, 245, 0.08), transparent 35%),
            radial-gradient(circle at 80% 80%, rgba(50, 200, 180, 0.08), transparent 35%);
          color: #fff;
          padding: 0;
          display: flex;
          flex-direction: column;
          position: relative;
          overflow: hidden;
        }

        .casino-deco {
          position: absolute;
          inset: 0;
          pointer-events: none;
          z-index: 0;
        }

        .deco {
          position: absolute;
          opacity: 0.25;
          animation: decoFloat 6s ease-in-out infinite;
          filter: grayscale(0);
          user-select: none;
          text-shadow: 0 0 12px rgba(255, 215, 0, 0.3);
        }

        @keyframes decoFloat {
          0%, 100% { transform: translateY(0) rotate(0deg); }
          50% { transform: translateY(-18px) rotate(8deg); }
        }

        .header-icons {
          position: fixed;
          top: 16px;
          right: 20px;
          display: flex;
          align-items: center;
          gap: 12px;
          z-index: 100;
          background: rgba(18, 29, 42, 0.75);
          backdrop-filter: blur(16px);
          -webkit-backdrop-filter: blur(16px);
          border: 1px solid rgba(255, 255, 255, 0.1);
          border-radius: 50px;
          padding: 6px 16px;
          box-shadow: 0 4px 20px rgba(0, 0, 0, 0.3);
        }

        .header-left {
          display: flex;
          align-items: center;
          gap: 20px;
        }

        .header-right {
          display: flex;
          align-items: center;
          gap: 16px;
        }

        .social-btn {
          background: rgba(255, 255, 255, 0.05);
          border: 1px solid rgba(255, 255, 255, 0.1);
          color: #fff;
          width: 40px;
          height: 40px;
          border-radius: 8px;
          display: flex;
          align-items: center;
          justify-content: center;
          cursor: pointer;
          font-size: 18px;
          transition: all 0.2s ease;
        }

        .social-btn:hover {
          background: rgba(255, 255, 255, 0.1);
          transform: translateY(-2px);
        }

        .header-left {
          display: flex;
          align-items: center;
          gap: 28px;
        }

        .logo {
          font-size: 52px;
          font-weight: 900;
          margin: 40px 0 0 0;
          text-align: center;
          letter-spacing: -0.5px;
          background: linear-gradient(
            120deg, 
            #ffffff 0%, 
            #66a9ff 25%, 
            #1a73e8 50%, 
            #66a9ff 75%, 
            #ffffff 100%
          );
          background-size: 200% auto;
          -webkit-background-clip: text;
          -webkit-text-fill-color: transparent;
          background-clip: text;
          line-height: 1.2;
          animation: shine 4s linear infinite;
        }

        @keyframes shine {
          to {
            background-position: 200% center;
          }
        }

        .header-right {
          display: flex;
          align-items: center;
          gap: 12px;
        }

        .coins-pill {
          padding: 6px 10px;
          background: rgba(255, 255, 255, 0.06);
          border: 1px solid rgba(255, 255, 255, 0.12);
          border-radius: 999px;
          font-size: 12px;
          font-weight: 700;
          color: #e7eef7;
        }

        .profile-btn {
          background: none;
          border: none;
          cursor: pointer;
          padding: 0;
          transition: all 0.3s ease;
        }

        .profile-btn:hover .profile-avatar {
          transform: scale(1.08);
          border-color: #66a9ff;
        }

        .avatar-container {
          position: relative;
          display: flex;
          align-items: center;
          justify-content: center;
        }

        .online-indicator {
          position: absolute;
          bottom: 2px;
          right: 2px;
          width: 12px;
          height: 12px;
          background-color: #44b700;
          border: 2px solid #121d2a;
          border-radius: 50%;
          box-shadow: 0 0 8px rgba(68, 183, 0, 0.4);
        }

        .profile-avatar {
          width: 44px;
          height: 44px;
          border-radius: 50%;
          object-fit: cover;
          border: 2px solid rgba(255, 255, 255, 0.2);
          transition: all 0.3s ease;
        }

        .profile-avatar.placeholder {
          background: #3a4452;
          color: #ffffff;
          display: flex;
          align-items: center;
          justify-content: center;
          font-weight: bold;
          font-size: 18px;
        }

        .games-section {
          padding: 40px 24px 20px 24px;
        }

        .games-carousel {
          display: flex;
          gap: 16px;
          padding: 0;
          max-width: 1400px;
          margin: 0 auto;
          flex-wrap: wrap;
          justify-content: center;
        }

        .game-item {
          width: 280px;
          display: flex;
          flex-direction: column;
          align-items: center;
          gap: 8px;
          flex-shrink: 0;
        }

        .game-card-stake {
          position: relative;
          border-radius: 12px;
          overflow: hidden;
          cursor: pointer;
          transition: all 0.3s cubic-bezier(0.4, 0, 0.2, 1);
          width: 280px;
          height: 380px;
          transform: translateY(0);
          border: 1px solid rgba(255, 255, 255, 0.08);
          box-shadow: 0 12px 30px rgba(0, 0, 0, 0.25);
        }

        .game-card-stake img {
          width: 100%;
          height: 100%;
          object-fit: cover;
          object-position: center;
          display: block;
          transition: transform 0.35s ease;
        }

        .game-card-stake:hover {
          box-shadow: 0 16px 36px rgba(0, 0, 0, 0.45);
          transform: translateY(-6px);
        }

        .game-card-stake:hover img {
          transform: scale(1.01);
        }

        .game-card-overlay {
          position: absolute;
          inset: 0;
          background: rgba(10, 15, 26, 0.88);
          display: flex;
          flex-direction: column;
          align-items: center;
          justify-content: center;
          padding: 24px;
          opacity: 0;
          transition: opacity 0.3s ease;
          text-align: center;
        }

        .game-card-stake:hover .game-card-overlay {
          opacity: 1;
        }

        .game-card-overlay h3 {
          margin: 0 0 12px 0;
          font-size: 22px;
          font-weight: 800;
          background: linear-gradient(120deg, #fff, #66a9ff);
          -webkit-background-clip: text;
          -webkit-text-fill-color: transparent;
        }

        .game-card-overlay p {
          margin: 0;
          font-size: 14px;
          line-height: 1.5;
          color: rgba(255, 255, 255, 0.8);
        }

        .players-count {
          font-size: 12px;
          color: rgba(231, 238, 247, 0.7);
          margin: 0;
          font-weight: 700;
          letter-spacing: 0.3px;
          text-align: center;
        }

        .activity-section {
          padding: 0 24px 24px 24px;
        }

        .activity-card {
          max-width: 1400px;
          margin: 0 auto;
          background: rgba(18, 29, 42, 0.85);
          border: 1px solid rgba(255, 255, 255, 0.08);
          border-radius: 12px;
          overflow: hidden;
          box-shadow: 0 12px 30px rgba(0, 0, 0, 0.25);
          backdrop-filter: blur(14px);
        }

        .activity-header {
          display: flex;
          align-items: center;
          justify-content: space-between;
          padding: 16px 20px;
          background: rgba(0, 0, 0, 0.25);
          border-bottom: 1px solid rgba(255, 255, 255, 0.08);
        }

        .activity-header h2 {
          margin: 0;
          font-size: 16px;
          text-transform: uppercase;
          letter-spacing: 1px;
        }

        .activity-subtitle {
          color: rgba(231, 238, 247, 0.7);
          font-size: 12px;
          font-weight: 600;
        }

        .activity-table {
          display: flex;
          flex-direction: column;
        }

        .activity-row {
          display: grid;
          grid-template-columns: 2fr 1.5fr 1fr 1.4fr 1.2fr 1.4fr;
          gap: 12px;
          align-items: center;
          padding: 14px 20px;
          border-bottom: 1px solid rgba(255, 255, 255, 0.06);
          font-size: 13px;
        }

        .activity-row:last-child {
          border-bottom: none;
        }

        .activity-head {
          font-size: 12px;
          text-transform: uppercase;
          letter-spacing: 0.8px;
          color: rgba(231, 238, 247, 0.6);
          background: rgba(0, 0, 0, 0.25);
        }

        .activity-cell {
          white-space: nowrap;
          overflow: hidden;
          text-overflow: ellipsis;
        }

        .activity-muted {
          color: rgba(231, 238, 247, 0.6);
        }

        .activity-win {
          color: #3be089;
          font-weight: 700;
        }

        .activity-loss {
          color: #ff8a8a;
          font-weight: 700;
        }

        .activity-empty {
          padding: 20px;
          text-align: center;
          color: rgba(231, 238, 247, 0.6);
          font-size: 13px;
        }

        .modal-overlay {
          position: fixed;
          top: 0;
          left: 0;
          right: 0;
          bottom: 0;
          background: rgba(0, 0, 0, 0.85);
          display: flex;
          align-items: center;
          justify-content: center;
          z-index: 1000;
          padding: 20px;
        }

        .modal-stake {
          background: rgba(18, 29, 42, 0.95);
          border-radius: 16px;
          overflow: hidden;
          max-width: 420px;
          width: 100%;
          position: relative;
          border: 1px solid rgba(255, 255, 255, 0.08);
          box-shadow: 0 20px 45px rgba(0, 0, 0, 0.45);
        }

        .modal-info {
          padding: 28px;
          text-align: center;
        }

        .modal-info h2 {
          font-size: 32px;
          margin: 0 0 12px 0;
          font-weight: 700;
          text-transform: uppercase;
          letter-spacing: 1px;
        }

        .modal-players {
          color: rgba(231, 238, 247, 0.7);
          margin: 0 0 24px 0;
          font-size: 14px;
        }

        .play-now-btn {
          width: 100%;
          padding: 14px;
          background: #1a73e8;
          color: #ffffff;
          border: none;
          border-radius: 8px;
          font-size: 16px;
          font-weight: 700;
          cursor: pointer;
          transition: all 0.3s ease;
          text-transform: uppercase;
          letter-spacing: 1px;
        }

        .play-now-btn:disabled {
          opacity: 0.55;
          cursor: not-allowed;
          transform: none;
          box-shadow: none;
        }

        .play-now-btn:hover {
          transform: scale(1.02);
          box-shadow: 0 12px 32px rgba(26, 115, 232, 0.35);
        }

        .mode-selector {
          display: grid;
          gap: 12px;
          margin: 20px 0 24px 0;
        }

        .mode-btn {
          width: 100%;
          padding: 12px 14px;
          border-radius: 10px;
          border: 1px solid rgba(255, 255, 255, 0.12);
          background: rgba(255, 255, 255, 0.04);
          color: #e7eef7;
          font-weight: 700;
          font-size: 14px;
          text-transform: uppercase;
          letter-spacing: 0.8px;
          cursor: pointer;
          transition: all 0.25s ease;
        }

        .mode-btn:hover {
          border-color: rgba(26, 115, 232, 0.6);
          box-shadow: 0 10px 24px rgba(26, 115, 232, 0.2);
          transform: translateY(-2px);
        }

        .mode-btn.active {
          background: rgba(26, 115, 232, 0.2);
          border-color: rgba(26, 115, 232, 0.8);
          color: #ffffff;
        }

        .close-btn {
          position: absolute;
          top: 16px;
          right: 16px;
          background: rgba(0, 0, 0, 0.5);
          border: none;
          color: #fff;
          font-size: 32px;
          cursor: pointer;
          width: 36px;
          height: 36px;
          border-radius: 999px;
          transition: all 0.3s ease;
          z-index: 10;
          display: flex;
          align-items: center;
          justify-content: center;
        }

        .close-btn:hover {
          background: rgba(26, 115, 232, 0.3);
          color: #8cc2ff;
        }

        @media (max-width: 768px) {
          .games-section {
            padding-left: 16px;
            padding-right: 16px;
          }

          .logo {
            font-size: 36px;
          }

          .game-item {
            width: 200px;
          }

          .game-card-stake {
            width: 200px;
            height: 270px;
          }
        }
      `}</style>
    </div>
  );
}

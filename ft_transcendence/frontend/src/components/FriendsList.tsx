import { useState, useEffect, useRef }        from 'react';
import { useTranslation }                     from 'react-i18next';
import { api }                                from '../services/api';
import type { Friend, FriendRequest }         from '../services/types';
import type { SocialEvent }                   from '../hooks/useSocialSocket';
import FriendProfile                          from './FriendProfile';

interface FriendsListProps {
  open:       boolean;
  onClose:    () => void;
  onlineIds:  Set<number>;
  lastEvent:  SocialEvent | null;
  onOpenChat: (friend: Friend) => void;
}

type Tab = 'friends' | 'requests' | 'add';

export default function FriendsList({ open, onClose, onlineIds, lastEvent, onOpenChat }: FriendsListProps) {
  const { t }                                       = useTranslation();
  const [tab, setTab]                                = useState<Tab>('friends');
  const [friends, setFriends]                        = useState<Friend[]>([]);
  const [received, setReceived]                      = useState<FriendRequest[]>([]);
  const [sent, setSent]                              = useState<FriendRequest[]>([]);
  const [addUsername, setAddUsername]                 = useState('');
  const [loading, setLoading]                        = useState(false);
  const [error, setError]                            = useState('');
  const [success, setSuccess]                        = useState('');
  const [selectedFriendId, setSelectedFriendId]       = useState<number | null>(null);
  const prevEventRef                                 = useRef<SocialEvent | null>(null);

  const refresh = async () => {
    const [friendsRes, reqRes] = await Promise.all([
      api.getFriends(),
      api.getFriendRequests(),
    ]);
    if (friendsRes.friends) setFriends(friendsRes.friends);
    if (reqRes.received)    setReceived(reqRes.received);
    if (reqRes.sent)        setSent(reqRes.sent);
  };

  useEffect(() => {
    if (open) refresh();
  }, [open]);

  useEffect(() => {
    if (!lastEvent || lastEvent === prevEventRef.current) return;
    prevEventRef.current = lastEvent;

    switch (lastEvent.type) {
      case 'friend_request_received':
        setReceived(prev => {
          if (prev.some(r => r.id === lastEvent.user.id)) return prev;
          return [...prev, { id: lastEvent.user.id, username: lastEvent.user.username, avatarUrl: lastEvent.user.avatarUrl }];
        });
        break;

      case 'friend_request_accepted':
        setFriends(prev => {
          if (prev.some(f => f.id === lastEvent.user.id)) return prev;
          return [...prev, {
            id:        lastEvent.user.id,
            username:  lastEvent.user.username,
            avatarUrl: lastEvent.user.avatarUrl,
            isActive:  lastEvent.user.isActive,
          }];
        });
        setSent(prev => prev.filter(s => s.id !== lastEvent.user.id));
        setReceived(prev => prev.filter(r => r.id !== lastEvent.user.id));
        break;

      case 'friend_request_cancelled':
        setReceived(prev => prev.filter(r => r.id !== lastEvent.userId));
        break;

      case 'friend_removed':
        setFriends(prev => prev.filter(f => f.id !== lastEvent.userId));
        break;
    }
  }, [lastEvent]);

  const handleSendRequest = async () => {
    if (!addUsername.trim()) return;
    setLoading(true);
    setError('');
    setSuccess('');

    const res = await api.sendFriendRequest(addUsername.trim());
    if (res.error) setError(res.error);
    else {
      setSuccess(t('friends.requestSent'));
      setAddUsername('');
      await refresh();
    }
    setLoading(false);
  };

  const handleAccept = async (senderId: number) => {
    await api.acceptFriendRequest(senderId);
    await refresh();
  };

  const handleRefuse = async (senderId: number) => {
    await api.refuseFriendRequest(senderId);
    await refresh();
  };

  const handleCancel = async (receiverId: number) => {
    await api.cancelFriendRequest(receiverId);
    await refresh();
  };

  const handleRemove = async (friendId: number) => {
    await api.removeFriend(friendId);
    await refresh();
  };

  const friendsWithLiveStatus = friends.map(f => ({
    ...f,
    isActive: onlineIds.has(f.id),
  }));
  const sortedFriends = [...friendsWithLiveStatus].sort((a, b) => (a.isActive === b.isActive ? 0 : a.isActive ? -1 : 1));

  return (
    <>
      {open && <div className="friends-overlay" onClick={onClose} />}
      <aside className={`friends-panel ${open ? 'friends-panel--open' : ''}`}>
        <div className="friends-panel-header">
          <h2>{t('friends.title')}</h2>
          <button className="friends-close-btn" onClick={onClose}>×</button>
        </div>

        <div className="friends-tabs">
          <button
            className={`friends-tab ${tab === 'friends' ? 'active' : ''}`}
            onClick={() => { setTab('friends'); setError(''); setSuccess(''); }}
          >
            {t('friends.myFriends')} {friends.length > 0 && <span className="friends-badge">{friends.length}</span>}
          </button>
          <button
            className={`friends-tab ${tab === 'requests' ? 'active' : ''}`}
            onClick={() => { setTab('requests'); setError(''); setSuccess(''); }}
          >
            {t('friends.requests')} {received.length > 0 && <span className="friends-badge friends-badge--alert">{received.length}</span>}
          </button>
          <button
            className={`friends-tab ${tab === 'add' ? 'active' : ''}`}
            onClick={() => { setTab('add'); setError(''); setSuccess(''); }}
          >
            {t('friends.add')}
          </button>
        </div>

        <div className="friends-panel-body">
          {tab === 'friends' && (
            <div className="friends-list">
              {sortedFriends.length === 0 ? (
                <p className="friends-empty">{t('friends.noFriends')}</p>
              ) : (
                sortedFriends.map(f => (
                  <div key={f.id} className="friend-row">
                    <div className="friend-info friend-info--clickable" onClick={() => setSelectedFriendId(f.id)}>
                      <div className="friend-avatar-wrap">
                        {f.avatarUrl ? (
                          <img className="friend-avatar" src={f.avatarUrl} alt={f.username} />
                        ) : (
                          <div className="friend-avatar friend-avatar--placeholder">
                            {f.username.slice(0, 1).toUpperCase()}
                          </div>
                        )}
                        <span className={`friend-status ${f.isActive ? 'online' : 'offline'}`} />
                      </div>
                      <div>
                        <p className="friend-name">{f.username}</p>
                        <p className="friend-status-text">
                          {f.isActive ? t('friends.online') : t('friends.offline')}
                        </p>
                      </div>
                    </div>
                    <div className="friend-actions">
                      <button
                        className="friend-chat-btn"
                        onClick={() => onOpenChat(f)}
                        title={t('chat.open', 'Chat')}
                      >
                        💬
                      </button>
                      <button className="friend-remove-btn" onClick={() => handleRemove(f.id)} title={t('friends.remove')}>
                        ✕
                      </button>
                    </div>
                  </div>
                ))
              )}
            </div>
          )}

          {tab === 'requests' && (
            <div className="friends-list">
              {received.length > 0 && (
                <>
                  <h3 className="friends-subtitle">{t('friends.received')}</h3>
                  {received.map(r => (
                    <div key={r.id} className="friend-row">
                      <div className="friend-info">
                        <div className="friend-avatar-wrap">
                          {r.avatarUrl ? (
                            <img className="friend-avatar" src={r.avatarUrl} alt={r.username} />
                          ) : (
                            <div className="friend-avatar friend-avatar--placeholder">
                              {r.username.slice(0, 1).toUpperCase()}
                            </div>
                          )}
                        </div>
                        <p className="friend-name">{r.username}</p>
                      </div>
                      <div className="friend-actions">
                        <button className="friend-accept-btn" onClick={() => handleAccept(r.id)}>✓</button>
                        <button className="friend-refuse-btn" onClick={() => handleRefuse(r.id)}>✕</button>
                      </div>
                    </div>
                  ))}
                </>
              )}

              {sent.length > 0 && (
                <>
                  <h3 className="friends-subtitle">{t('friends.sent')}</h3>
                  {sent.map(s => (
                    <div key={s.id} className="friend-row">
                      <div className="friend-info">
                        <div className="friend-avatar-wrap">
                          {s.avatarUrl ? (
                            <img className="friend-avatar" src={s.avatarUrl} alt={s.username} />
                          ) : (
                            <div className="friend-avatar friend-avatar--placeholder">
                              {s.username.slice(0, 1).toUpperCase()}
                            </div>
                          )}
                        </div>
                        <p className="friend-name">{s.username}</p>
                      </div>
                      <button className="friend-cancel-btn" onClick={() => handleCancel(s.id)}>
                        {t('friends.cancel')}
                      </button>
                    </div>
                  ))}
                </>
              )}

              {received.length === 0 && sent.length === 0 && (
                <p className="friends-empty">{t('friends.noRequests')}</p>
              )}
            </div>
          )}

          {tab === 'add' && (
            <div className="friends-add">
              {error && <div className="error-message">{error}</div>}
              {success && <div className="info-message">{success}</div>}
              <div className="friends-add-form">
                <input
                  type="text"
                  className="friends-add-input"
                  placeholder={t('friends.usernamePlaceholder')}
                  value={addUsername}
                  onChange={(e) => setAddUsername(e.target.value)}
                  onKeyDown={(e) => { if (e.key === 'Enter') handleSendRequest(); }}
                  maxLength={15}
                />
                <button
                  className="friends-add-btn"
                  onClick={handleSendRequest}
                  disabled={loading || !addUsername.trim()}
                >
                  {loading ? '...' : t('friends.sendRequest')}
                </button>
              </div>
            </div>
          )}
        </div>
      </aside>

      {selectedFriendId !== null && (
        <FriendProfile
          userId={selectedFriendId}
          isOnline={onlineIds.has(selectedFriendId)}
          onClose={() => setSelectedFriendId(null)}
        />
      )}
    </>
  );
}

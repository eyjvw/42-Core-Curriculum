import { useState, useEffect }     from 'react';
import { useTranslation }          from 'react-i18next';
import { api }                     from '../services/api';
import type { UserProfile }        from '../services/types';

interface FriendProfileProps {
  userId:    number;
  isOnline:  boolean;
  onClose:   () => void;
}

export default function FriendProfile({ userId, isOnline, onClose }: FriendProfileProps) {
  const { t }                          = useTranslation();
  const [profile, setProfile]          = useState<UserProfile | null>(null);
  const [loading, setLoading]          = useState(true);
  const [error, setError]              = useState('');

  useEffect(() => {
    setLoading(true);
    setError('');
    api.getUserProfile(userId).then(res => {
      if (res.error)       setError(res.error);
      else if (res.profile) setProfile(res.profile);
      setLoading(false);
    });
  }, [userId]);

  const online = profile ? isOnline : false;

  const memberSince = profile?.createdAt
    ? new Date(profile.createdAt).toLocaleDateString(undefined, { year: 'numeric', month: 'long', day: 'numeric' })
    : '—';

  const winRate = profile?.stats && profile.stats.gamesPlayed > 0
    ? Math.round((profile.stats.gamesWon / profile.stats.gamesPlayed) * 100)
    : 0;

  return (
    <div className="fp-overlay" onClick={onClose}>
      <div className="fp-modal" onClick={e => e.stopPropagation()}>
        <button className="fp-close" onClick={onClose}>×</button>

        {loading && <div className="fp-loading">{t('common.loading')}</div>}
        {error   && <div className="fp-error">{error}</div>}

        {profile && !loading && (
          <>
            <div className="fp-header">
              <div className="fp-avatar-wrap">
                {profile.avatarUrl ? (
                  <img className="fp-avatar" src={profile.avatarUrl} alt={profile.username} />
                ) : (
                  <div className="fp-avatar fp-avatar--placeholder">
                    {profile.username.slice(0, 1).toUpperCase()}
                  </div>
                )}
                <span className={`fp-status-dot ${online ? 'online' : 'offline'}`} />
              </div>
              <div className="fp-identity">
                <h2 className="fp-username">{profile.username}</h2>
                <span className={`fp-status-label ${online ? 'online' : 'offline'}`}>
                  {online ? t('friends.online') : t('friends.offline')}
                </span>
              </div>
            </div>

            {profile.bio && (
              <p className="fp-bio">{profile.bio}</p>
            )}

            <div className="fp-info-grid">
              <div className="fp-info-card">
                <span className="fp-info-label">{t('friendProfile.coins')}</span>
                <span className="fp-info-value">$ {Number(profile.coins).toLocaleString()}</span>
              </div>
              <div className="fp-info-card">
                <span className="fp-info-label">{t('friendProfile.memberSince')}</span>
                <span className="fp-info-value">{memberSince}</span>
              </div>
            </div>

            {profile.stats && (
              <div className="fp-stats-section">
                <h3 className="fp-section-title">{t('friendProfile.stats')}</h3>

                <div className="fp-winrate-bar">
                  <div className="fp-winrate-fill" style={{ width: `${winRate}%` }} />
                  <span className="fp-winrate-text">{winRate}% {t('friendProfile.winRate')}</span>
                </div>

                <div className="fp-stats-grid">
                  <div className="fp-stat">
                    <span className="fp-stat-value">{profile.stats.gamesPlayed}</span>
                    <span className="fp-stat-label">{t('friendProfile.played')}</span>
                  </div>
                  <div className="fp-stat fp-stat--win">
                    <span className="fp-stat-value">{profile.stats.gamesWon}</span>
                    <span className="fp-stat-label">{t('friendProfile.won')}</span>
                  </div>
                  <div className="fp-stat fp-stat--loss">
                    <span className="fp-stat-value">{profile.stats.gamesLost}</span>
                    <span className="fp-stat-label">{t('friendProfile.lost')}</span>
                  </div>
                </div>

                <div className="fp-game-stats">
                  <div className="fp-game-row">
                    <span className="fp-game-name">🃏 Blackjack</span>
                    <span className="fp-game-wins">{profile.stats.blackjacksWon}W</span>
                    <span className="fp-game-losses">{profile.stats.blackjackLosses}L</span>
                  </div>
                  <div className="fp-game-row">
                    <span className="fp-game-name">🎰 Roulette</span>
                    <span className="fp-game-wins">{profile.stats.rouletteWins}W</span>
                    <span className="fp-game-losses">{profile.stats.rouletteLosses}L</span>
                  </div>
                </div>
              </div>
            )}

            <div className="fp-footer">
              {profile.isFriend && (
                <span className="fp-badge fp-badge--friend">✓ {t('friendProfile.isFriend')}</span>
              )}
              {!profile.isFriend && profile.hasPending && (
                <span className="fp-badge fp-badge--pending">⏳ {t('friendProfile.pendingRequest')}</span>
              )}
            </div>
          </>
        )}
      </div>
    </div>
  );
}

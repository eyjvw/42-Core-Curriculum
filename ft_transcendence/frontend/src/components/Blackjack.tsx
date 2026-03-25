import { useState, useEffect }	from 'react';
import { api }					from '../services/api';
import type { GameState, Card }	from '../types/game';

interface BlackjackProps
{
  onClose:			() => void;
  onBalanceUpdate:	(balance: number) => void;
  initialBalance:	number;
}

const SUIT_SYMBOLS: Record<string, string> = {
  hearts:	'♥',
  diamonds:	'♦',
  clubs:	'♣',
  spades:	'♠'
};

const SUIT_COLORS: Record<string, string> = {
  hearts:	'#ff4757',
  diamonds:	'#ff4757',
  clubs:	'#1a1a2e',
  spades:	'#1a1a2e'
};

function CardComponent({ card, hidden = false, order = 0 }: { card: Card; hidden?: boolean; order?: number }) {
  const isHidden = hidden || card.rank === '?';
  const symbol = SUIT_SYMBOLS[card.suit] || '?';
  const color = SUIT_COLORS[card.suit] || '#1a1a2e';

  return (
    <div
      className={`stake-card ${isHidden ? 'hidden' : ''}`}
      style={{ animationDelay: `${order * 80}ms` }}
    >
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

export default function Blackjack({ onClose, onBalanceUpdate, initialBalance }: BlackjackProps) {
  const [game, setGame] = useState<GameState | null>(null);
  const [balance, setBalance] = useState(initialBalance);
  const [bet, setBet] = useState(10);
  const [loading, setLoading] = useState(false);
  const [error, setError] = useState<string | null>(null);
  const [winnings, setWinnings] = useState<number | null>(null);
  const [showResult, setShowResult] = useState(false);

  useEffect(() => {
    loadGame();
  }, []);

  useEffect(() => {
    if (game?.status === 'finished') {
      setShowResult(true);
      const timer = setTimeout(() => setShowResult(false), 3000);
      return () => clearTimeout(timer);
    }
  }, [game?.status, game?.result]);

  const loadGame = async () => {
    const result = await api.blackjackGet();
    if (result.game) setGame(result.game);
    if (result.balance !== undefined) {
      setBalance(result.balance);
      onBalanceUpdate(result.balance);
    }
  };

  const startNewGame = async () => {
    if (bet < 1 || bet > balance) {
      setError('Invalid bet amount');
      return;
    }
    setLoading(true);
    setError(null);
    setWinnings(null);
    setShowResult(false);

    const result = await api.blackjackNew(bet);
    
    if (result.error) {
      setError(result.error);
    } else if (result.game) {
      setGame(result.game);
      if (result.balance !== undefined) {
        setBalance(result.balance);
        onBalanceUpdate(result.balance);
      }
    } else {
      setError('Failed to create game');
    }
    setLoading(false);
  };

  const hit = async () => {
    setLoading(true);
    setError(null);
    const result = await api.blackjackHit();
    if (result.error) setError(result.error);
    else if (result.game) {
      setGame(result.game);
      if (result.balance !== undefined) {
        setBalance(result.balance);
        onBalanceUpdate(result.balance);
      }
    }
    setLoading(false);
  };

  const stand = async () => {
    setLoading(true);
    setError(null);
    const result = await api.blackjackStand();
    if (result.error) setError(result.error);
    else if (result.game) {
      setGame(result.game);
      if (result.balance !== undefined) {
        setBalance(result.balance);
        onBalanceUpdate(result.balance);
      }
      if (result.winnings !== undefined) setWinnings(result.winnings);
    }
    setLoading(false);
  };

  const doubleDown = async () => {
    setLoading(true);
    setError(null);
    const result = await api.blackjackDouble();
    if (result.error) setError(result.error);
    else if (result.game) {
      setGame(result.game);
      if (result.balance !== undefined) {
        setBalance(result.balance);
        onBalanceUpdate(result.balance);
      }
      if (result.winnings !== undefined) setWinnings(result.winnings);
    }
    setLoading(false);
  };

  const multiplyBet = (multiplier: number) => {
    setBet(Math.min(balance, Math.max(1, Math.floor(bet * multiplier))));
  };

  const getResultInfo = () => {
    if (!game || game.status !== 'finished') return null;
    switch (game.result) {
      case 'blackjack': return { text: 'BLACKJACK!', color: '#ffd700', isWin: true };
      case 'player_win': return { text: 'YOU WIN!', color: '#00d26a', isWin: true };
      case 'dealer_win': return { text: 'DEALER WINS', color: '#ff4757', isWin: false };
      case 'push': return { text: 'PUSH', color: '#ffa502', isWin: null };
      default: return null;
    }
  };

  const resultInfo = getResultInfo();
  const isPlaying = game && game.status === 'playing';

  return (
    <div className="stake-bj-container">
      {error && (
        <div style={{
          position: 'fixed',
          top: '10px',
          left: '50%',
          transform: 'translateX(-50%)',
          background: '#ff4757',
          color: 'white',
          padding: '12px 20px',
          borderRadius: '6px',
          zIndex: 9999,
          fontSize: '14px',
          maxWidth: '90%'
        }}>
          ❌ {error}
        </div>
      )}

      <div className="stake-bj-sidebar">
        <div className="stake-bj-header">
          <div className="stake-bj-title">
            <span className="stake-bj-icon">🃏</span>
            <span>Blackjack</span>
          </div>
          <button className="stake-bj-close" onClick={onClose}>✕</button>
        </div>

        <div className="stake-bj-bet-section">
          <label className="stake-bj-label">Bet Amount</label>
          <div className="stake-bj-input-wrapper">
            <span className="stake-bj-currency">$</span>
            <input
              type="number"
              value={bet}
              onChange={(e) => setBet(Math.max(1, Math.min(balance, parseInt(e.target.value) || 1)))}
              disabled={!!isPlaying}
              className="stake-bj-input"
            />
            <div className="stake-bj-input-btns">
              <button onClick={() => multiplyBet(0.5)} disabled={!!isPlaying}>½</button>
              <button onClick={() => multiplyBet(2)} disabled={!!isPlaying}>2×</button>
            </div>
          </div>

          <div className="stake-bj-quick-bets">
            {[10, 50, 100, 500].map((amount) => (
              <button
                key={amount}
                onClick={() => setBet(Math.min(balance, amount))}
                disabled={!!isPlaying}
                className={bet === amount ? 'active' : ''}
              >
                ${amount}
              </button>
            ))}
            <button
              onClick={() => setBet(balance)}
              disabled={!!isPlaying}
              className={bet === balance ? 'active' : ''}
            >
              Max
            </button>
          </div>

          {error && <div className="stake-bj-error">{error}</div>}

          {!isPlaying ? (
            <button 
              className="stake-bj-deal-btn"
              onClick={startNewGame}
              disabled={loading || bet > balance || bet < 1}
            >
              {loading ? 'Dealing...' : 'Bet'}
            </button>
          ) : (
            <div className="stake-bj-actions">
              <button className="stake-bj-action hit" onClick={hit} disabled={loading}>
                Hit
              </button>
              <button className="stake-bj-action stand" onClick={stand} disabled={loading}>
                Stand
              </button>
              <button 
                className="stake-bj-action double" 
                onClick={doubleDown} 
                disabled={loading || game.playerHand.cards.length !== 2 || balance < game.bet}
              >
                Double
              </button>
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
              DEALER {game && !game.dealerHand.hidden ? `(${game.dealerHand.total})` : ''}
            </div>
            <div style={{ fontSize: '11px', color: '#888', minHeight: '16px' }}>
              {game ? `${game.dealerHand.cards.length} cards${game.dealerHand.hidden ? ' (1 hidden)' : ''}` : ''}
            </div>
            <div className="stake-bj-cards">
              {game?.dealerHand.cards.map((card, idx) => (
                <CardComponent 
                  key={`dealer-${game.gameId}-${card.suit}-${card.rank}-${idx}`}
                  card={card} 
                  hidden={game.dealerHand.hidden && idx === 1}
                  order={idx}
                />
              ))}
            </div>
          </div>

          {showResult && resultInfo && (
            <div className="stake-bj-result" style={{ color: resultInfo.color }}>
              {resultInfo.text}
              {winnings !== null && winnings > 0 && (
                <div className="stake-bj-result-amount">+${winnings}</div>
              )}
            </div>
          )}

          <div className="stake-bj-player">
            <div className="stake-bj-cards">
              {game?.playerHand.cards.map((card, idx) => (
                <CardComponent
                  key={`player-${game.gameId}-${card.suit}-${card.rank}-${idx}`}
                  card={card}
                  order={idx}
                />
              ))}
            </div>
            <div style={{ fontSize: '11px', color: '#888', minHeight: '16px' }}>
              {game ? `${game.playerHand.cards.length} cards` : ''}
            </div>
            <div className="stake-bj-label-text">
              YOU {game ? `(${game.playerHand.total})` : ''}
            </div>
          </div>

          {game && (
            <div className="stake-bj-bet-display">
              <div className="stake-bj-chips">
                {Array.from({ length: Math.min(5, Math.ceil(game.bet / 100)) }).map((_, i) => (
                  <div key={i} className="stake-chip" style={{ bottom: `${i * 4}px` }} />
                ))}
              </div>
              <span className="stake-bj-bet-amount">${game.bet}</span>
            </div>
          )}
        </div>
      </div>
    </div>
  );
}

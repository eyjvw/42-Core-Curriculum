import { useState, useEffect, useRef }    from 'react';
import { useTranslation }                 from 'react-i18next';
import type { ChatMessage, SocialEvent }  from '../hooks/useSocialSocket';

interface ChatWindowProps {
  friendId:            number;
  friendUsername:      string;
  friendAvatarUrl:     string | null;
  currentUserId:       number;
  lastEvent:           SocialEvent | null;
  onClose:             () => void;
  sendChatMessage:     (to: number, content: string) => void;
  requestChatHistory:  (friendId: number) => void;
}

export default function ChatWindow({
  friendId,
  friendUsername,
  friendAvatarUrl,
  currentUserId,
  lastEvent,
  onClose,
  sendChatMessage,
  requestChatHistory,
}: ChatWindowProps) {
  const { t }                                = useTranslation();
  const [messages, setMessages]              = useState<ChatMessage[]>([]);
  const [input, setInput]                    = useState('');
  const bottomRef                            = useRef<HTMLDivElement>(null);
  const prevEventRef                         = useRef<SocialEvent | null>(null);
  const historyLoaded                        = useRef(false);

  useEffect(() => {
    historyLoaded.current = false;
    setMessages([]);
    requestChatHistory(friendId);
  }, [friendId, requestChatHistory]);

  useEffect(() => {
    if (!lastEvent || lastEvent === prevEventRef.current) return;
    prevEventRef.current = lastEvent;

    if (lastEvent.type === 'chat_history' && lastEvent.friendId === friendId) {
      setMessages(lastEvent.messages);
      historyLoaded.current = true;
    }

    if (lastEvent.type === 'chat_message') {
      const msg = lastEvent as ChatMessage & { type: string };
      if ((msg.from === friendId && msg.to === currentUserId) ||
          (msg.from === currentUserId && msg.to === friendId)) {
        setMessages(prev => {
          if (prev.some(m => m.id === msg.id)) return prev;
          return [...prev, { id: msg.id, from: msg.from, to: msg.to, content: msg.content, createdAt: msg.createdAt, username: msg.username }];
        });
      }
    }
  }, [lastEvent, friendId, currentUserId]);

  useEffect(() => {
    bottomRef.current?.scrollIntoView({ behavior: 'smooth' });
  }, [messages]);

  const handleSend = () => {
    const text = input.trim();
    if (!text) return;
    sendChatMessage(friendId, text);
    setInput('');
  };

  const handleKeyDown = (e: React.KeyboardEvent) => {
    if (e.key === 'Enter' && !e.shiftKey) {
      e.preventDefault();
      handleSend();
    }
  };

  return (
    <div className="chat-window">
      <div className="chat-header">
        <div className="chat-header-info">
          {friendAvatarUrl ? (
            <img className="chat-avatar" src={friendAvatarUrl} alt={friendUsername} />
          ) : (
            <div className="chat-avatar chat-avatar--placeholder">
              {friendUsername.slice(0, 1).toUpperCase()}
            </div>
          )}
          <span className="chat-header-name">{friendUsername}</span>
        </div>
        <button className="chat-close-btn" onClick={onClose}>×</button>
      </div>

      <div className="chat-messages">
        {messages.length === 0 && historyLoaded.current && (
          <p className="chat-empty">{t('chat.noMessages', 'No messages yet. Say hi! 👋')}</p>
        )}
        {messages.map(msg => (
          <div
            key={msg.id}
            className={`chat-bubble ${msg.from === currentUserId ? 'chat-bubble--mine' : 'chat-bubble--theirs'}`}
          >
            <p className="chat-bubble-text">{msg.content}</p>
            <span className="chat-bubble-time">
              {msg.createdAt ? new Date(msg.createdAt + 'Z').toLocaleTimeString([], { hour: '2-digit', minute: '2-digit' }) : ''}
            </span>
          </div>
        ))}
        <div ref={bottomRef} />
      </div>

      <div className="chat-input-bar">
        <input
          className="chat-input"
          type="text"
          value={input}
          onChange={e => setInput(e.target.value)}
          onKeyDown={handleKeyDown}
          placeholder={t('chat.placeholder', 'Type a message…')}
          maxLength={2000}
          autoFocus
        />
        <button className="chat-send-btn" onClick={handleSend} disabled={!input.trim()}>
          ➤
        </button>
      </div>
    </div>
  );
}

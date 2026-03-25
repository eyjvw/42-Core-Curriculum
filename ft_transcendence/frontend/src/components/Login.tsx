import { useState }				from 'react';
import { useTranslation }		from 'react-i18next';
import { api }					from '../services/api';
import type { LoginData }		from '../types/auth';

interface LoginProps {
  onSuccess:			() => void;
  onSwitchToRegister:	() => void;
}

export default function Login({ onSuccess, onSwitchToRegister }: LoginProps) {
  const { t }					= useTranslation();
  const [formData, setFormData]	= useState<LoginData>({
    email:		'',
    password:	'',
  });
  const [a2fCode, setA2fCode]			= useState('');
  const [requires2FA, setRequires2FA]	= useState(false);
  const [error, setError]				= useState<string>('');
  const [loading, setLoading]			= useState(false);

  const handleSubmit = async (e: React.SyntheticEvent<HTMLFormElement>) => {
    e.preventDefault();
    setError('');
    setLoading(true);

    const loginData	= requires2FA ? { ...formData, a2f_code: a2fCode } : formData;
    const result	= await api.login(loginData);

    if (result.error) {
      if (result.error === '2FA code required') {
        setRequires2FA(true);
        setLoading(false);
        return;
      }
      setError(result.error);
      setLoading(false);
    }
	else if (result.success)
      onSuccess();
	else
	{
      setError(t('login.failed'));
      setLoading(false);
    }
  };

  return (
    <div className="auth-container">
      <div className="auth-card">
        <h1>{t('login.title')}</h1>
        <p className="auth-subtitle">{t('login.subtitle')}</p>

        <form onSubmit={handleSubmit}>
          <div className="form-group">
            <label className="sr-only" htmlFor="email">Email</label>
            <input
              id="email"
              type="text"
              placeholder={t('login.emailPlaceholder')}
              value={formData.email}
              onChange={(e) => setFormData({ ...formData, email: e.target.value })}
              required
              disabled={loading}
            />
          </div>

          <div className="form-group">
            <label className="sr-only" htmlFor="password">Password</label>
            <input
              id="password"
              type="password"
              placeholder={t('common.password')}
              value={formData.password}
              onChange={(e) => setFormData({ ...formData, password: e.target.value })}
              required
              disabled={loading}
              minLength={6}
            />
          </div>

          {requires2FA && (
            <div className="form-group">
              <label className="sr-only" htmlFor="a2f-code">2FA Code</label>
              <input
                id="a2f-code"
                type="text"
                placeholder={t('login.a2fPlaceholder')}
                value={a2fCode}
                onChange={(e) => setA2fCode(e.target.value)}
                required
                disabled={loading}
                maxLength={6}
                autoFocus
              />
            </div>
          )}

          {error && <div className="error-message">{error}</div>}

          <button type="submit" className="submit-btn" disabled={loading}>
            {loading ? t('login.submitting') : t('login.submit')}
          </button>
        </form>

        <p className="switch-auth">
          {t('login.switch')}{' '}
          <button onClick={onSwitchToRegister} className="link-btn">
            {t('login.switchCta')}
          </button>
        </p>
      </div>
    </div>
  );
}

import { useState }			from 'react';
import { useTranslation }	from 'react-i18next';
import { api }				from '../services/api';

interface TwoFactorSettingsProps {
  isEnabled:	boolean;
  onUpdate:		() => void;
}

export default function TwoFactorSettings({ isEnabled, onUpdate }: TwoFactorSettingsProps) {
  const { t }						= useTranslation();
  const [loading, setLoading]		= useState(false);
  const [error, setError]			= useState('');
  const [setupData, setSetupData]	= useState<{ secret: string; uri: string } | null>(null);
  const [verifyCode, setVerifyCode]	= useState('');

  const handleEnable = async () => {
    setLoading(true);
    setError('');
    const result = await api.enable2FA();
    
	if (result.error)
		setError(result.error);
	else if (result.secret && result.uri)
		setSetupData({ secret: result.secret, uri: result.uri });
	setLoading(false);
  };

  const handleVerify = async (e: React.FormEvent) => {
    e.preventDefault();
    setLoading(true);
    setError('');
    
    const result = await api.verify2FA(verifyCode);
    
	if (result.error)
		setError(result.error);
	else if (result.success)
	{
		setSetupData(null);
		setVerifyCode('');
		onUpdate();
	}
	setLoading(false);
  };

  const handleDisable = async () => {
    setLoading(true);
    setError('');
    
    const result = await api.disable2FA();
    
    if (result.error)
		setError(result.error);
    else if (result.success)
		onUpdate();
    setLoading(false);
  };

  if (setupData) {
    return (
      <div className="two-factor-setup">
        <h3>{t('twoFactor.setupTitle')}</h3>
        <p>{t('twoFactor.setupInstructions')}</p>
        
        <div className="qr-section">
          <img 
            src={`https://api.qrserver.com/v1/create-qr-code/?size=200x200&data=${encodeURIComponent(setupData.uri)}`} 
            alt="2FA QR Code"
          />
          <p className="secret-code">
            {t('twoFactor.manualCode')}: <code>{setupData.secret}</code>
          </p>
        </div>

        <form onSubmit={handleVerify}>
          <div className="form-group">
            <input
              type="text"
              placeholder={t('twoFactor.enterCode')}
              value={verifyCode}
              onChange={(e) => setVerifyCode(e.target.value)}
              maxLength={6}
              required
              disabled={loading}
            />
          </div>
          {error && <div className="error-message">{error}</div>}
          <button type="submit" className="profile-primary" disabled={loading}>
            {loading ? t('common.loading') : t('twoFactor.verify')}
          </button>
          <button 
            type="button" 
            className="profile-secondary" 
            onClick={() => setSetupData(null)}
            disabled={loading}
          >
            {t('twoFactor.cancel')}
          </button>
        </form>
      </div>
    );
  }

  return (
    <div className="two-factor-settings">
      <h3>{t('twoFactor.title')}</h3>
      <p className="two-factor-status">
        {t('twoFactor.status')}: {isEnabled ? t('twoFactor.enabled') : t('twoFactor.disabled')}
      </p>
      
      {error && <div className="error-message">{error}</div>}
      
      {isEnabled ? (
        <button 
          className="profile-danger" 
          onClick={handleDisable} 
          disabled={loading}
        >
          {loading ? t('common.loading') : t('twoFactor.disable')}
        </button>
      ) : (
        <button 
          className="profile-primary" 
          onClick={handleEnable} 
          disabled={loading}
        >
          {loading ? t('common.loading') : t('twoFactor.enable')}
        </button>
      )}
    </div>
  );
}

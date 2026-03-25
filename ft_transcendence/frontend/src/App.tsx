import										'./App.css';
import { useState, useEffect, useCallback, type JSX }	from 'react';
import { useTranslation }					from 'react-i18next';
import Login								from './components/Login';
import Register								from './components/Register';
import Main									from './components/Main';
import Profile								from './components/Profile';
import TermsOfService						from './components/TermsOfService';
import PrivacyPolicy						from './components/PrivacyPolicy';
import { api }								from './services/api';
import type { User }						from './types/auth';

type View = 'loading' | 'login' | 'register' | 'authenticated' | 'profile' | 'terms' | 'privacy';

function App() {
  const [view, setView] = useState<View>('loading');
  const [user, setUser] = useState<User | null>(null);
  const year = new Date().getFullYear();
  const { t, i18n } = useTranslation();

  const navigateTo = useCallback((newView: View, replace = false) => {
    if (replace)
      window.history.replaceState({ view: newView }, '', '');
    else
      window.history.pushState({ view: newView }, '', '');
    setView(newView);
  }, []);

  const checkAuth = async () => {
    const result = await api.me();
    if (result.user)
	  {
      setUser(result.user);
      navigateTo('authenticated', true);
    }
	else
      navigateTo('login', true);
  };

  useEffect(() => {
    checkAuth();
  }, []);

  useEffect(() => {
    const onPopState = (e: PopStateEvent) => {
      const v = e.state?.view as View | undefined;
      if (v) setView(v);
    };
    window.addEventListener('popstate', onPopState);
    return () => window.removeEventListener('popstate', onPopState);
  }, []);

  useEffect(() => {
    const lang = user?.language ?? 'en';
    i18n.changeLanguage(lang);
    document.documentElement.lang = lang;
    document.documentElement.dir = lang === 'ar' ? 'rtl' : 'ltr';
  }, [user, i18n]);

  const handleAuthSuccess = () => { checkAuth(); };

  let content: JSX.Element;

  if (view === 'loading') {
    content = (
      <div className="auth-container">
        <div className="auth-card">
          <h1>{t('common.loading')}</h1>
        </div>
      </div>
    );
  }
  else if (view === 'authenticated' && user)
    content = <Main user={user} onOpenProfile={() => navigateTo('profile')} onUserUpdate={(updatedUser) => setUser(updatedUser)} />;
  else if (view === 'profile' && user) {
    content = (
      <Profile
        user={user}
        onBack={() => window.history.back()}
        onUserUpdate={(updatedUser) => {
          setUser(updatedUser);
        }}
        onLogout={async () => {
          await api.logout();
          setUser(null);
          navigateTo('login', true);
        }}
        currentLanguage={user.language ?? 'en'}
      />
    );
  }
  else if (view === 'register') {
    content = (
      <Register
        onSuccess={handleAuthSuccess}
        onSwitchToLogin={() => navigateTo('login')}
      />
    );
  }
  else if (view === 'terms') {
    content = <TermsOfService onBack={() => window.history.back()} />;
  }
  else if (view === 'privacy') {
    content = <PrivacyPolicy onBack={() => window.history.back()} />;
  }
  else {
    content = (
      <Login
        onSuccess={handleAuthSuccess}
        onSwitchToRegister={() => navigateTo('register')}
      />
    );
  }

  return (
    <div className="app-shell">
      <div className="app-content">{content}</div>
      <footer className={`app-footer${view === 'terms' || view === 'privacy' ? ' legal-footer' : ''}`}>
        <div className="footer-links">
          <button onClick={() => navigateTo('terms')} className="footer-link">{t('footer.terms')}</button>
          <span className="footer-separator">•</span>
          <button onClick={() => navigateTo('privacy')} className="footer-link">{t('footer.privacy')}</button>
        </div>
        <div className="footer-credits">
          {t('footer.createdBy', { names: 'Samuel, Hoel, Derhen, Marc, Zibrian', year })}
        </div>
      </footer>
    </div>
  );
}

export default App;

import { useTranslation } from 'react-i18next';

interface PrivacyPolicyProps {
  onBack: () => void;
}

export default function PrivacyPolicy({ onBack }: PrivacyPolicyProps) {
  const { t } = useTranslation();

  return (
    <div className="legal-page">
      <div className="legal-container">
        <button className="legal-back" onClick={onBack}>← {t('common.back', 'Back')}</button>

        <h1 className="legal-title">{t('footer.privacy')}</h1>
        <p className="legal-updated">Last updated: March 8, 2026</p>

        <section className="legal-section">
          <h2>1. Introduction</h2>
          <p>
            This Privacy Policy explains how ft_gambling ("the Platform"), an educational project developed
            as part of the 42 school curriculum, collects, uses, and protects your personal information.
          </p>
        </section>

        <section className="legal-section">
          <h2>2. Information We Collect</h2>

          <h3>2.1 Account Information</h3>
          <p>When you create an account, we collect:</p>
          <ul>
            <li><strong>Email address</strong> — used for account identification and login.</li>
            <li><strong>Username</strong> — publicly displayed on the Platform.</li>
            <li><strong>Password</strong> — stored securely using bcrypt hashing. We never store or have access to your plain-text password.</li>
          </ul>

          <h3>2.2 Game Data</h3>
          <ul>
            <li>Virtual currency balance and transaction history.</li>
            <li>Game results and statistics.</li>
            <li>Chat messages exchanged with friends on the Platform.</li>
          </ul>

          <h3>2.3 Technical Data</h3>
          <ul>
            <li>IP address (used for rate limiting and security).</li>
            <li>Browser user agent (for compatibility purposes).</li>
          </ul>
        </section>

        <section className="legal-section">
          <h2>3. How We Use Your Information</h2>
          <p>We use your information to:</p>
          <ul>
            <li>Authenticate and manage your account.</li>
            <li>Provide the gaming and social features of the Platform.</li>
            <li>Protect against abuse, cheating, and unauthorized access.</li>
            <li>Enforce rate limits and prevent denial-of-service attacks.</li>
          </ul>
          <p>
            <strong>We do not sell, rent, or share your personal data with third parties.</strong>
          </p>
        </section>

        <section className="legal-section">
          <h2>4. Data Storage & Security</h2>
          <ul>
            <li>All data is stored in a local SQLite database on the server.</li>
            <li>Passwords are hashed using bcrypt with a salt factor of 10.</li>
            <li>Authentication tokens are signed using JWT (JSON Web Tokens).</li>
            <li>2FA secrets are stored encrypted in the database.</li>
            <li>Communication between your browser and the server is encrypted via HTTPS (terminated at the reverse proxy).</li>
          </ul>
        </section>

        <section className="legal-section">
          <h2>5. Cookies</h2>
          <p>The Platform uses a single essential cookie:</p>
          <ul>
            <li>
              <strong>token</strong> — An HttpOnly, SameSite=Lax authentication cookie containing your
              JWT session token. This cookie is required for the Platform to function and cannot be disabled.
            </li>
          </ul>
          <p>We do not use any tracking cookies, analytics cookies, or third-party cookies.</p>
        </section>

        <section className="legal-section">
          <h2>6. Third-Party Services</h2>
          <p>The Platform integrates with the following third-party services:</p>
          <ul>
            <li>
              <strong>QR Server API</strong> — Used to generate QR codes for 2FA setup. Only the 2FA URI
              is sent; no personal data is transmitted.
            </li>
          </ul>
        </section>

        <section className="legal-section">
          <h2>7. Data Retention</h2>
          <p>
            Your data is retained as long as your account is active. Since this is an educational project,
            all data may be deleted when the project concludes or the server is decommissioned.
          </p>
        </section>

        <section className="legal-section">
          <h2>8. Your Rights</h2>
          <p>You have the right to:</p>
          <ul>
            <li>Access your personal data through your profile page.</li>
            <li>Update your username, email, avatar, and language preferences.</li>
            <li>Enable or disable two-factor authentication.</li>
            <li>Request deletion of your account and associated data.</li>
          </ul>
        </section>

        <section className="legal-section">
          <h2>9. Children's Privacy</h2>
          <p>
            The Platform is not intended for users under 18 years of age.
            We do not knowingly collect personal information from children.
          </p>
        </section>

        <section className="legal-section">
          <h2>10. Changes to This Policy</h2>
          <p>
            We may update this Privacy Policy from time to time. The "Last updated" date at the top
            of this page indicates when the policy was last revised.
          </p>
        </section>

        <section className="legal-section">
          <h2>11. Contact</h2>
          <p>
            For privacy-related questions, please contact the development team through the 42 school channels.
          </p>
        </section>
      </div>
    </div>
  );
}

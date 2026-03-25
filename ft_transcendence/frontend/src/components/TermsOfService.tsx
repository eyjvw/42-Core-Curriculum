import { useTranslation } from 'react-i18next';

interface TermsOfServiceProps {
  onBack: () => void;
}

export default function TermsOfService({ onBack }: TermsOfServiceProps) {
  const { t } = useTranslation();

  return (
    <div className="legal-page">
      <div className="legal-container">
        <button className="legal-back" onClick={onBack}>← {t('common.back', 'Back')}</button>

        <h1 className="legal-title">{t('footer.terms')}</h1>
        <p className="legal-updated">Last updated: March 8, 2026</p>

        <section className="legal-section">
          <h2>1. Acceptance of Terms</h2>
          <p>
            By accessing and using ft_gambling ("the Platform"), you agree to be bound by these Terms of Service.
            If you do not agree with any part of these terms, you must not use the Platform.
          </p>
        </section>

        <section className="legal-section">
          <h2>2. Description of Service</h2>
          <p>
            ft_gambling is an educational project developed as part of the 42 school curriculum (ft_transcendence).
            The Platform provides simulated casino-style games using virtual currency only.
            <strong> No real money is involved at any point.</strong> The virtual coins have no monetary value
            and cannot be exchanged, withdrawn, or converted into real currency.
          </p>
        </section>

        <section className="legal-section">
          <h2>3. User Accounts</h2>
          <p>
            You may create an account using an email/password combination.
            You are responsible for maintaining the confidentiality of your credentials.
            You agree to provide accurate information and to keep your account details up to date.
          </p>
          <ul>
            <li>You must be at least 18 years old to use the Platform.</li>
            <li>One account per person is allowed.</li>
            <li>You are responsible for all activity under your account.</li>
            <li>We reserve the right to suspend or terminate accounts that violate these terms.</li>
          </ul>
        </section>

        <section className="legal-section">
          <h2>4. Virtual Currency</h2>
          <p>
            All coins on the Platform are virtual and provided for entertainment purposes only.
          </p>
          <ul>
            <li>Virtual coins have no real-world value.</li>
            <li>Virtual coins cannot be purchased, sold, or transferred outside the Platform.</li>
            <li>We may adjust, reset, or modify virtual balances at any time.</li>
          </ul>
        </section>

        <section className="legal-section">
          <h2>5. Prohibited Conduct</h2>
          <p>You agree not to:</p>
          <ul>
            <li>Use automated scripts, bots, or exploits to gain an unfair advantage.</li>
            <li>Attempt to hack, reverse-engineer, or compromise the Platform's security.</li>
            <li>Harass, abuse, or threaten other users.</li>
            <li>Impersonate other users or misrepresent your identity.</li>
            <li>Use the Platform for any illegal purpose.</li>
          </ul>
        </section>

        <section className="legal-section">
          <h2>6. Intellectual Property</h2>
          <p>
            The Platform, including its design, code, and content, is an educational project.
            All rights are reserved by the developers (Samuel, Hoel, Derhen, Marc, Zibrian).
            You may not copy, modify, or distribute any part of the Platform without permission.
          </p>
        </section>

        <section className="legal-section">
          <h2>7. Disclaimer of Warranties</h2>
          <p>
            The Platform is provided "as is" and "as available" without warranties of any kind.
            We do not guarantee that the Platform will be uninterrupted, error-free, or secure.
            This is an educational project and should be treated as such.
          </p>
        </section>

        <section className="legal-section">
          <h2>8. Limitation of Liability</h2>
          <p>
            To the fullest extent permitted by law, the developers shall not be liable for any
            indirect, incidental, or consequential damages arising from your use of the Platform.
          </p>
        </section>

        <section className="legal-section">
          <h2>9. Two-Factor Authentication</h2>
          <p>
            The Platform offers optional two-factor authentication (2FA) for enhanced security.
            If you enable 2FA, you are responsible for maintaining access to your authenticator device.
            We cannot recover accounts if you lose access to your 2FA method.
          </p>
        </section>

        <section className="legal-section">
          <h2>10. Changes to Terms</h2>
          <p>
            We reserve the right to modify these Terms of Service at any time.
            Continued use of the Platform after changes constitutes acceptance of the new terms.
          </p>
        </section>

        <section className="legal-section">
          <h2>11. Contact</h2>
          <p>
            For questions about these Terms, please contact the development team through the 42 school channels.
          </p>
        </section>
      </div>
    </div>
  );
}

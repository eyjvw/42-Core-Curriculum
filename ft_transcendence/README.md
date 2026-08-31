# ft_transcendence — ft_gambling

*This project has been created as part of the 42 curriculum by sbonneau, hkeromne, marcheva, dedavid, zcadinot.*

A full-stack, single-page web application built as the final project of the 42 common core. **ft_gambling** is an online casino-style platform featuring Blackjack (solo & multiplayer), a real-time social system with friends and chat, user authentication with optional two-factor authentication, and a fully containerised microservice architecture behind an Nginx reverse proxy.

> **Disclaimer:** All currency on the platform is **100 % virtual**. No real money is involved at any point.

---

## Table of Contents

1. [Team Information](#team-information)
2. [Description](#description)
3. [Features List](#features-list)
4. [Technical Stack](#technical-stack)
5. [Database Schema](#database-schema)
6. [Architecture Overview](#architecture-overview)
7. [Modules](#modules)
8. [Instructions](#instructions)
9. [Individual Contributions](#individual-contributions)
10. [Project Management](#project-management)
11. [Resources](#resources)

---

## Team Information

| Member    | Role(s)                          | Responsibilities |
|-----------|----------------------------------|------------------|
| **Samuel** | Project Owner, Developer        | Defined project vision, priorities and acceptance criteria. Developed backend services and frontend components. |
| **Hoel**   | Project Owner, Developer        | Co-defined product scope and requirements. Worked on authentication, game logic and social features. |
| **Marc**   | Project Manager, Developer      | Coordinated sprints, tracked progress and deadlines. Developed features across frontend and backend. |
| **Derhen** | Technical Lead, Developer       | Drove architecture decisions (microservices, gateway, WAF). Implemented core infrastructure and DevOps. |
| **Zibrian**| Technical Lead, Developer       | Co-led technical choices (database, Docker, Nginx). Developed game engine and multiplayer systems. |

---

## Description

**ft_gambling** is a single-page application (SPA) that recreates a casino experience using only virtual currency. The project demonstrates modern web development practices including:

- **Microservice backend** — independent services for authentication, social features, and games, orchestrated through a central API gateway.
- **Real-time communication** — WebSocket-based live updates for multiplayer games, friend presence, and instant messaging.
- **Security-first design** — a WAF (Web Application Firewall) with SQL injection detection, rate limiting, CORS management, and HTTPS termination via Nginx.
- **Internationalisation** — full i18n support in English, French, and Arabic.

### Key Features

- 🃏 **Blackjack** — Solo play against the dealer with hit, stand, and double-down actions.
- 🎲 **Multiplayer Blackjack** — Create or join rooms with a code, play with friends and bots in real time.
- 👥 **Social System** — Friend requests, online presence indicators, and private real-time chat.
- 🔐 **Authentication** — Email/password registration, JWT session management, and optional TOTP-based 2FA.
- 🛡️ **Gateway & WAF** — Centralised reverse proxy with rate limiting, SQL injection detection, and CORS handling.
- 🌐 **Internationalisation** — UI available in English, French, and Arabic.
- 🪙 **Virtual Economy** — 1 000 starting coins, bet system, balance tracking across games.

---

## Features List

| Feature | Description | Contributors |
|---------|-------------|--------------|
| User Registration & Login | Email/password auth with input validation (Zod) | Samuel, Hoel |
| JWT Session Management | HttpOnly cookie-based JWT tokens | Samuel, Hoel |
| Two-Factor Authentication (2FA) | TOTP-based 2FA with QR code setup (OTPAuth) | Samuel, Hoel |
| User Profile | View/edit username, email, avatar, bio, language | Samuel, Marc |
| Friend System | Send/accept/decline/remove friend requests | Hoel, Marc |
| Online Presence | Real-time friend online/offline status via WebSocket | Hoel, Marc |
| Real-time Chat | Private messaging between friends with history | Hoel, Marc |
| Solo Blackjack | Full Blackjack engine (hit, stand, double, bust, blackjack) | Derhen, Zibrian |
| Multiplayer Blackjack | Room creation/joining, turn-based play, spectators | Derhen, Zibrian |
| Bot Players | AI-controlled players for multiplayer rooms | Derhen, Zibrian |
| Virtual Currency | 1 000 starting coins, betting, balance updates | All |
| API Gateway | Central proxy routing to microservices | Derhen |
| WAF — Rate Limiting | Token-bucket rate limiter on API routes | Derhen |
| WAF — SQL Injection Detection | Pattern-based SQL injection blocking | Derhen |
| HTTPS / Nginx Reverse Proxy | SSL termination, WebSocket proxying | Derhen, Zibrian |
| Internationalisation (i18n) | English, French, Arabic translations | Marc |
| Privacy Policy & Terms of Service | Legal pages accessible from footer | Samuel |
| Responsive UI | Mobile-friendly casino-themed design | All |

---

## Technical Stack

### Frontend
| Technology | Purpose | Justification |
|------------|---------|---------------|
| **React 19** | UI framework | Component-based, strong ecosystem, team familiarity |
| **TypeScript** | Type safety | Catches errors at compile time, better DX |
| **Vite 7** | Build tool & dev server | Extremely fast HMR, native ESM support |
| **i18next** | Internationalisation | Mature i18n library with React bindings |
| **React Three Fiber** | 3D rendering | Visual effects and animations |

### Backend
| Technology | Purpose | Justification |
|------------|---------|---------------|
| **Bun** | JavaScript runtime | Fastest JS runtime, native TypeScript, built-in HTTP server and WebSocket support |
| **TypeScript** | Type safety | Consistent with frontend, strong typing |
| **Drizzle ORM** | Database access | Type-safe, lightweight, excellent SQLite support |
| **Jose** | JWT handling | Standards-compliant, lightweight JWT library |
| **Bcrypt** | Password hashing | Industry standard for secure password storage |
| **Zod** | Input validation | Runtime type checking with TypeScript inference |
| **OTPAuth** | 2FA TOTP | Lightweight TOTP library for 2FA implementation |

### Infrastructure
| Technology | Purpose | Justification |
|------------|---------|---------------|
| **Docker & Docker Compose** | Containerisation | Reproducible builds, isolated services |
| **Nginx** | Reverse proxy & SSL termination | Industry-standard, efficient TLS handling, WebSocket support |
| **SQLite** | Database | Lightweight, zero-config, perfect for single-server deployment, no external DB service needed |
| **OpenSSL** | Certificate generation | Self-signed certs for development HTTPS |

### Why SQLite?
SQLite was chosen because the project runs on a single server and doesn't require the overhead of a client-server database like PostgreSQL. It offers:
- Zero configuration and zero maintenance.
- A single file for the entire database, easily backed up.
- Excellent performance for the expected workload with WAL mode.
- Native support in Bun via `bun:sqlite`.

---

## Database Schema

### Visual Representation

```
┌──────────────────────┐       ┌──────────────────────┐
│        users         │       │        stats          │
├──────────────────────┤       ├──────────────────────┤
│ id          INTEGER PK│◄─────│ user_id     INTEGER FK│
│ username    TEXT UQ   │       │ id          INTEGER PK│
│ email       TEXT UQ   │       │ points      INTEGER   │
│ password_hash TEXT    │       │ games_played INTEGER  │
│ avatar_url  TEXT      │       │ games_won   INTEGER   │
│ is_active   INTEGER   │       │ games_lost  INTEGER   │
│ a2f_secret  TEXT      │       │ blackjacks_won INTEGER│
│ a2f_active  INTEGER   │       │ blackjack_losses INT  │
│ coins       INTEGER   │       │ created_at  TEXT      │
│ bio         TEXT      │       │ updated_at  TEXT      │
│ language    TEXT      │       └──────────┬───────────┘
│ created_at  TEXT      │                  │
│ updated_at  TEXT      │       ┌──────────▼───────────┐
└───┬───────────┬──────┘       │   points_history     │
    │           │              ├──────────────────────┤
    │           │              │ id        INTEGER PK  │
    │           │              │ stat_id   INTEGER FK   │
    │           │              │ change    INTEGER      │
    │           │              │ reason    TEXT          │
    │           │              │ game_type TEXT          │
    │           │              │ created_at TEXT         │
    │           │              └────────────────────────┘
    │           │
┌───▼───────────▼──────┐       ┌──────────────────────┐
│      friends         │       │   friend_requests    │
├──────────────────────┤       ├──────────────────────┤
│ user_id   INTEGER FK │       │ sender_id   INT FK   │
│ friend_id INTEGER FK │       │ receiver_id INT FK   │
│ PK(user_id,friend_id)│       │ PK(sender,receiver)  │
└──────────────────────┘       └──────────────────────┘

┌──────────────────────┐
│      messages        │
├──────────────────────┤
│ id         INTEGER PK│
│ sender_id  INTEGER FK│──► users.id
│ receiver_id INTEGER FK│──► users.id
│ content    TEXT       │
│ created_at TEXT       │
└──────────────────────┘
```

### Tables & Relationships

| Table | Description | Key Relationships |
|-------|-------------|-------------------|
| `users` | User accounts with auth, profile, and settings | Referenced by all other tables |
| `stats` | Per-user game statistics | `user_id → users.id` |
| `points_history` | Ledger of coin changes | `stat_id → stats.id` |
| `friends` | Bidirectional friend links | `user_id, friend_id → users.id` |
| `friend_requests` | Pending friend requests | `sender_id, receiver_id → users.id` |
| `messages` | Private chat messages | `sender_id, receiver_id → users.id` |

---

## Architecture Overview

```
                  ┌────────────┐
   Client ───────►│   Nginx    │ (HTTPS :8443 / HTTP :8080)
                  │  SSL Term  │
                  └─────┬──────┘
                        │ HTTP
                  ┌─────▼──────┐
                  │  Gateway   │ :8000
                  │  WAF/Proxy │
                  └──┬──┬──┬──┬┘
                     │  │  │  │
           ┌─────────┘  │  │  └─────────┐
           ▼            ▼  ▼            ▼
      ┌────────┐  ┌────────┐  ┌────────┐  ┌──────────┐
      │  Auth  │  │ Social │  │  Game  │  │ Frontend │
      │ :4000  │  │ :4001  │  │ :4002  │  │  :3000   │
      └────────┘  └────────┘  └────────┘  └──────────┘
           │           │           │
           └───────────┴───────────┘
                       │
                ┌──────▼──────┐
                │   SQLite    │
                │  (shared)   │
                └─────────────┘
```

---

## Modules

### Module Summary

| # | Module | Type | Points | Contributors |
|---|--------|------|--------|--------------|
| 1 | Framework as Backend (Bun) | Major | 2 | All |
| 2 | Standard User Management | Major | 2 | Samuel, Hoel |
| 3 | Remote Authentication (JWT) | Major | 2 | Samuel, Hoel |
| 4 | Two-Factor Authentication (2FA) | Major | 2 | Samuel, Hoel |
| 5 | Remote Players (Multiplayer) | Major | 2 | Derhen, Zibrian |
| 6 | Live Chat | Major | 2 | Hoel, Marc |
| 7 | AI Opponent (Bot Player) | Major | 2 | Derhen, Zibrian |
| 8 | Game Customisation Options | Minor | 1 | Derhen, Zibrian |
| 9 | Database Integration (SQLite + Drizzle ORM) | Minor | 1 | All |
| 10 | WAF/ModSecurity (Gateway + SQL Injection Detection) | Major | 2 | Derhen |
| 11 | Multiple Language Support (i18n) | Minor | 1 | Marc |
| 12 | Server-Side Rendering / Frontend Framework (React + Vite) | Minor | 1 | All |
| 13 | Replacing Pong with Another Game (Blackjack) | Major | 2 | All |

**Total: 8 Major × 2 + 5 Minor × 1 = 21 points**

### Module Details

#### 1. Framework as Backend — Bun (Major)
The entire backend runs on **Bun**, a modern JavaScript runtime with built-in HTTP server, WebSocket support, native TypeScript execution, and SQLite bindings. Each microservice (auth, social, game, gateway) uses `Bun.serve()` for HTTP and WebSocket handling without any external framework like Express.

#### 2. Standard User Management (Major)
Full user account lifecycle: registration with email/password, login, logout, profile editing (username, email, avatar, bio, language), and session management via JWT tokens stored in HttpOnly cookies.

#### 3. Remote Authentication — JWT (Major)
Stateless authentication using JSON Web Tokens signed with HMAC-SHA256 via the **Jose** library. Tokens are issued on login and verified on every protected API request. Passwords are hashed with **bcrypt** (salt factor 10).

#### 4. Two-Factor Authentication (Major)
Optional TOTP-based 2FA using the **OTPAuth** library. Users scan a QR code with an authenticator app. The TOTP secret is stored in the database and verified on each login when 2FA is enabled.

#### 5. Remote Players — Multiplayer (Major)
Real-time multiplayer Blackjack via WebSocket. Players can create rooms (assigned a unique code), invite others, and play turn-based Blackjack. Room state is broadcast to all connected players and spectators in real time.

#### 6. Live Chat (Major)
Real-time private messaging between friends via WebSocket. Messages are persisted in the `messages` table. Chat history is retrievable. Online presence is tracked and broadcast to friends.

#### 7. AI Opponent — Bot Player (Major)
Room owners can add AI-controlled bot players to multiplayer Blackjack rooms. Bots follow a configurable strategy (e.g., hit below 17, stand at 17+) and act automatically during their turn.

#### 8. Game Customisation Options (Minor)
Players can choose between solo and multiplayer modes, set bet amounts, and create private rooms with unique codes.

#### 9. Database Integration — SQLite + Drizzle ORM (Minor)
Type-safe database access with **Drizzle ORM** over **SQLite** in WAL mode. The schema is defined in TypeScript with automatic migrations. Shared database volume across services.

#### 10. WAF / ModSecurity — Gateway (Major)
The API gateway implements a Web Application Firewall with:
- **Rate limiting** — Token-bucket algorithm, 1 000 requests/minute per client on API routes.
- **SQL injection detection** — Pattern-based detection on query strings.
- **CORS management** — Dynamic origin validation.
- **HTTPS termination** via Nginx reverse proxy.

#### 11. Multiple Language Support — i18n (Minor)
Full internationalisation with **i18next** and **react-i18next**. The UI is available in English, French, and Arabic. User language preference is stored in the database and applied on login.

#### 12. Frontend Framework — React + Vite (Minor)
The frontend is a React 19 SPA bundled with Vite 7. Uses React Compiler (babel-plugin-react-compiler) for automatic optimisations. TypeScript throughout.

#### 13. Replacing Pong with Another Game — Blackjack (Major)
Instead of the traditional Pong game, the project implements a full **Blackjack** game engine with proper rules (hit, stand, double down, bust, blackjack, dealer logic), supporting both solo and multiplayer modes.

---

## Instructions

### Prerequisites

| Software | Version | Purpose |
|----------|---------|---------|
| **Docker** | ≥ 24.0 | Container runtime |
| **Docker Compose** | ≥ 2.20 | Service orchestration |
| **Make** | any | Build automation |
| **OpenSSL** | any | TLS certificate generation |

### Environment Variables

Create the following `.env` files before running the project:

**`gateway/.env`**
```env
PORT=8000
AUTH_ROUTE=http://auth:4000
SOCIAL_ROUTE=http://social:4001
GAMES_ROUTE=http://game:4002
WS_ROUTE=http://game:4002
FRONTEND_ROUTE=http://frontend:3000
FRONTEND_PORT=3000
EXTERNAL_PORT=8443
```

**`backend/auth/.env`**
```env
PORT=4000
JWT_SECRET=your_jwt_secret_here
```

**`backend/social/.env`**
```env
PORT=4001
JWT_SECRET=your_jwt_secret_here
```

**`backend/game/.env`**
```env
PORT=4002
JWT_SECRET=your_jwt_secret_here
```

**`frontend/.env`**
```env
VITE_API_URL=
```

> ⚠️ The `JWT_SECRET` must be the **same** across all backend services.

### Step-by-step

```bash
# 1. Clone the repository
git clone <repository-url>
cd ft_transcendence

# 2. Create the .env files as described above

# 3. Build and run (generates TLS certs automatically)
make all

# 4. Access the application
# Open https://localhost:8443 in your browser
# (Accept the self-signed certificate warning)
```

### Available Make Commands

| Command | Description |
|---------|-------------|
| `make all` | Generate certs, build, and start all services |
| `make up` | Start services (generates certs if missing) |
| `make down` | Stop all services |
| `make restart` | Stop and restart all services |
| `make rebuild` | Rebuild from scratch and start |
| `make logs` | Follow logs from all services |
| `make ps` | Show service status |
| `make clean` | Remove all containers, images, and volumes |
| `make fclean` | Full clean + Docker system prune |
| `make re` | Full clean + rebuild |

---

## Individual Contributions

### Samuel
- **Authentication system** — Designed and implemented registration, login, logout, and JWT token management.
- **2FA** — Implemented TOTP-based two-factor authentication with QR code generation.
- **User profile** — Profile viewing and editing (username, email, avatar, bio).
- **Legal pages** — Created Privacy Policy and Terms of Service pages.
- **Frontend components** — Login, Register, Profile, and TwoFactorSettings components.

### Hoel
- **Authentication** — Co-developed the auth service, input validation with Zod, and session management.
- **2FA** — Co-implemented two-factor authentication flow.
- **Social system** — Built the friend request system (send, accept, decline, remove).
- **Real-time chat** — Implemented WebSocket-based private messaging with message persistence.
- **Online presence** — Real-time friend online/offline status tracking and broadcasting.

### Marc
- **Project management** — Coordinated tasks, tracked progress, and ensured deadlines were met.
- **Friend system UI** — Built the FriendsList and ChatWindow frontend components.
- **Internationalisation** — Set up i18next with English, French, and Arabic translations.
- **UI/UX** — Contributed to responsive design and casino-themed visual elements.
- **Social features** — Contributed to social WebSocket integration and friend management.

### Derhen
- **Gateway & WAF** — Designed and built the API gateway with rate limiting, SQL injection detection, and CORS handling.
- **Infrastructure** — Set up Docker Compose, Nginx reverse proxy, and SSL termination.
- **Architecture** — Drove the microservice architecture decisions and service communication patterns.
- **Multiplayer system** — Co-developed the room-based multiplayer WebSocket infrastructure.
- **Game engine** — Co-developed the Blackjack game engine and game state management.

### Zibrian
- **Blackjack engine** — Co-developed the core Blackjack game logic (hit, stand, double, dealer AI).
- **Multiplayer rooms** — Co-built room creation, joining, spectating, and real-time state synchronisation.
- **Bot players** — Implemented AI-controlled bot players with configurable strategies.
- **Infrastructure** — Co-led Docker and Nginx configuration, database schema design.
- **WebSocket management** — Built the WebSocket manager for game room real-time communication.

---

## Project Management

### Work Organisation
- **Sprints** — The team worked in weekly sprints with defined goals.
- **Task distribution** — Tasks were assigned based on roles and expertise. The two POs defined priorities, the PM tracked progress, and the Tech Leads made architecture decisions.
- **Code review** — All code was reviewed by at least one other team member before merging.

### Tools Used
| Tool | Purpose |
|------|---------|
| **GitHub** | Version control, pull requests, code review |
| **GitHub Issues** | Task tracking and bug reporting |
| **Discord** | Primary communication channel for daily standups and discussions |

### Communication
- **Daily standups** on Discord to sync progress and blockers.
- **Weekly planning sessions** to define sprint goals and assign tasks.
- **Code review discussions** via GitHub pull request comments.

---

## Resources

### Documentation & References
- [Bun Documentation](https://bun.sh/docs) — Runtime, HTTP server, WebSocket, SQLite bindings.
- [React Documentation](https://react.dev) — Component model, hooks, state management.
- [Vite Documentation](https://vitejs.dev) — Build tool configuration and dev server.
- [Drizzle ORM Documentation](https://orm.drizzle.team) — Type-safe database queries.
- [SQLite Documentation](https://www.sqlite.org/docs.html) — Database engine reference.
- [Nginx Documentation](https://nginx.org/en/docs/) — Reverse proxy and SSL configuration.
- [Docker Documentation](https://docs.docker.com) — Containerisation and Compose.
- [JWT Introduction (jwt.io)](https://jwt.io/introduction) — JSON Web Token standard.
- [OWASP SQL Injection Prevention](https://cheatsheetseries.owasp.org/cheatsheets/SQL_Injection_Prevention_Cheat_Sheet.html) — Security best practices.
- [i18next Documentation](https://www.i18next.com) — Internationalisation framework.
- [RFC 6238 — TOTP](https://datatracker.ietf.org/doc/html/rfc6238) — Time-based One-Time Password algorithm.

### AI Usage
AI tools (GitHub Copilot with Claude) were used as a development assistant for the following tasks:

| Task | AI Usage | Scope |
|------|----------|-------|
| **Code scaffolding** | Generating boilerplate code for repetitive patterns (API route handlers, type definitions) | Backend services |
| **CSS styling** | Generating and iterating on casino-themed CSS styles and animations | Frontend components |
| **Nginx configuration** | Generating and debugging the Nginx reverse proxy configuration | Infrastructure |
| **Bug fixing** | Diagnosing issues (MIME types, CORS, WebSocket proxying) | Cross-cutting |
| **Documentation** | Generating this README.md based on project requirements | Documentation |

AI was **not** used for:
- Core game logic design and algorithms.
- Database schema design.
- Architecture decisions.
- Security design (WAF rules, JWT strategy).

All AI-generated code was reviewed, tested, and adapted by team members before integration.

---

## License

This project is an educational project developed as part of the **42 school curriculum**. All rights are reserved by the developers (Samuel, Hoel, Marc, Derhen, Zibrian).

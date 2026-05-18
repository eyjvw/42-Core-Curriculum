# 42 Core Curriculum

A comprehensive 6-month (148 days) programming journey from C fundamentals to full-stack web development.

## Projects Overview

### Foundation (C Fundamentals)

| Project | Language | Time | Description |
|---------|----------|------|-------------|
| [libft](./libft/README.md) | C | 20-30h | Custom C standard library (51 functions) |
| [ft_printf](./ft_printf/README.md) | C | 15-25h | Printf implementation with format specifiers |
| [get_next_line](./get_next_line/README.md) | C | 15-25h | Line-by-line file reading with state persistence |

### Object-Oriented Programming (C++)

| Project | Language | Time | Description |
|---------|----------|------|-------------|
| [C++ 00-02](./C++/00/README.md) | C++98 | 15-20h | OOP fundamentals, classes, references vs pointers |
| [C++ 03-09](./C++/01/README.md) | C++98 | 50-70h | Inheritance, templates, exceptions, STL |

### Systems Programming

| Project | Language | Time | Description |
|---------|----------|------|-------------|
| [pipex](./pipex/README.md) | C | 20-30h | Shell piping with fork/exec |
| [push_swap](./push_swap/README.md) | C | 30-40h | Stack sorting with optimized algorithms |
| [philosophers](./philosophers/README.md) | C | 30-40h | Multithreading, mutexes, semaphores (bonus) |

### Graphics & Games

| Project | Language | Time | Description |
|---------|----------|------|-------------|
| [so_long](./so_long/README.md) | C | 40-50h | 2D game engine with MiniLibX |
| [cub3D](./cub3d/README.md) | C | 50-70h | 3D raycasting engine (Wolfenstein 3D style) |

### Networking

| Project | Language | Time | Description |
|---------|----------|------|-------------|
| [ft_irc](./ft_irc/README.md) | C++98 | 60-80h | Non-blocking IRC server with poll() |
| [minishell](./minishell/README.md) | C | 50-60h | Shell with AST parser, pipes, builtins |

### DevOps & Full-Stack

| Project | Tech Stack | Time | Description |
|---------|-----------|------|-------------|
| [Inception](./Inception/README.md) | Docker, Nginx, MariaDB, WordPress | 30-40h | Containerized infrastructure with TLS/SSL |
| [ft_transcendence](./ft_transcendence/README.md) | React, TypeScript, Bun, Vite, SQLite, Docker | 200+ h | Full-stack casino platform with real-time multiplayer |

---

## Key Technologies

### Languages
- **C** — Low-level systems programming, memory management, algorithms
- **C++ (98/11/14/17)** — Object-oriented design, templates, STL
- **TypeScript** — Web development (frontend & backend)

### Core Libraries & Tools
- **MiniLibX** — Graphics rendering (2D/3D)
- **POSIX APIs** — System calls, threading, sockets, processes
- **GNU readline** — Command-line interface

### Full-Stack Stack (ft_transcendence)
- **Frontend:** React 19, Vite, TypeScript, Zod, i18next
- **Backend:** Bun, TypeScript, Drizzle ORM, Jose (JWT), Bcrypt
- **Database:** SQLite (single-file, zero-config)
- **Infrastructure:** Docker, docker-compose, Nginx, OpenSSL

### System Administration (Inception)
- **Docker & docker-compose** — Orchestration
- **Nginx** — Reverse proxy, TLS/SSL termination
- **MariaDB** — Database
- **WordPress** — Content management

---

## Learning Progression

```
Week 1-2:   Foundations (libft, ft_printf, get_next_line)
Week 3-4:   C++ Basics (OOP, classes, pointers)
Week 5-6:   Systems (pipex, push_swap, advanced C++)
Week 7-8:   Graphics (so_long, philosophers threading)
Week 9-10:  Advanced Graphics (cub3D raycasting)
Week 11-12: Networking (ft_irc, minishell)
Week 13-14: Infrastructure (Inception - Docker)
Week 15-21: Full-Stack Capstone (ft_transcendence)
```

---

## Quick Start

### Build Any Project

```bash
cd <project>
make                  # Build
./binary arg1 arg2   # Run
make clean           # Clean objects
make fclean          # Clean all
make re              # Rebuild
```

### Recommended Learning Path

**For C mastery:**
1. libft → ft_printf → get_next_line → pipex

**For OOP & design patterns:**
1. C++ 00-02 → C++ 03-09 → ft_irc

**For performance & algorithms:**
1. push_swap → cub3D → ft_transcendence

**For full-stack development:**
1. Inception → ft_transcendence

---

## Statistics

| Metric | Value |
|--------|-------|
| **Total Projects** | 13 |
| **Total Lines of Code** | ~31,000+ |
| **Languages** | 6 (C, C++, JavaScript, TypeScript, Docker, YAML) |
| **Estimated Time** | ~700 hours |
| **Difficulty Progression** | Beginner → Intermediate → Advanced → Expert |

---

## Getting Started

1. **Read a project's README** — Each project folder has detailed documentation
2. **Build and test** — Run `make` and verify it compiles
3. **Explore the code** — Study the architecture in `includes/` and `src/`
4. **Understand the concepts** — Check the README for key learnings

---

## Project Status

✅ All projects complete and compiling  
✅ Makefiles standardized with `mk/` fragments  
✅ Error handling and memory management verified  
✅ Each project has comprehensive README  

---

## Notes

- All code follows **42 Norminette** standards
- **Manual memory management** — No external memory libraries
- **Modular design** — Clear separation of concerns in each project
- **Build system** — Consistent Makefile patterns across all projects

---

<div align="center">

**Created by:** sbonneau  
**School:** 42 Le Havre  
**Status:** ✅ Complete

Each project README contains detailed specifications, build instructions, and key concepts.  
Start with any project that interests you!

</div>

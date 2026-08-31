# ft_irc

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

**ft_irc** (executable `ircserv`) is a minimal IRC server written in C++98. It implements
non-blocking TCP connection handling, password authentication (`PASS`), user management
(`NICK` / `USER`), basic channel features (`JOIN` / `INVITE` / `KICK` / `TOPIC` / `MODE`)
and message delivery (`PRIVMSG`).

The server uses `poll()` for I/O multiplexing and processes commands and replies through the
`MSG`, `CMD` and `RPL` modules.

## Build

```bash
make
```

The Makefile compiles in C++98 with the flags `-Werror -Wall -Wextra -std=c++98 -g3`.

## Usage

```bash
./ircserv <PASSWORD> <PORT>
# Example:
./ircserv mySecretPass 6667
```

- `<PASSWORD>`: password required for `PASS` authentication
- `<PORT>`: TCP port (1-65535)

The server handles `SIGINT` to trigger a clean shutdown.

## Makefile rules

- `make` / `make all`: build the `ircserv` binary
- `make clean`: remove object files (`obj/`)
- `make fclean`: remove the binary and artifacts
- `make re`: full rebuild

## Project Structure

```
ft_irc/
├── Makefile                     - build rules
├── README.md                    - this file
├── headers/                     - headers (.hpp/.h)
├── srcs/                        - C++ sources
│   ├── main.cpp                 - entry point, argument checking
│   ├── Server.cpp               - main loop, accept, poll, auth
│   ├── Client.cpp               - client management
│   ├── Channel.cpp              - channel management
│   ├── MSG.cpp                  - message parsing/formatting
│   ├── RPL.cpp                  - reply generation (RPL/ERR)
│   ├── Package.cpp              - temporary command structure
│   ├── Ft.cpp                   - utilities (time, parsing, etc.)
│   ├── Errors.cpp               - error codes and constants
│   └── cmds/                    - IRC command implementations
│       ├── CMD.cpp
│       ├── Mode.cpp
│       ├── Join.cpp
│       ├── Invite.cpp
│       ├── Kick.cpp
│       ├── Topic.cpp
│       ├── Priv.cpp
│       ├── Nick.cpp
│       └── User.cpp
```

## Supported Commands

- `PASS`, `NICK`, `USER`: authentication and identification
- `JOIN`, `PART` (via `Join`), `MODE`: channel creation and management
- `INVITE`: invite a user to a channel
- `KICK`: eject a user from a channel
- `TOPIC`: read/write a channel topic
- `PRIVMSG` / `NOTICE` (via `Priv`): private or channel messages

> Note: the list above matches the implementations present in `srcs/cmds/`.

## Key Behavior

- The server expects `PASS` first, then `NICK`/`USER` to authenticate a client.
- Incoming data is buffered per client and processed line by line, using CRLF as separator.
- Idle or disconnected clients are cleaned up properly and their descriptors closed.

## Requirements

- C++98-compatible compiler (`g++` / `clang++`)
- POSIX system (Linux recommended)

## Testing & Debugging

- Build with `make`, then run `./ircserv <PASSWORD> <PORT>`.
- Connect with an IRC client (`irssi`, `weechat`) or with `telnet` / `nc` to test commands manually.

## Resources

- RFC 1459 — Internet Relay Chat Protocol: https://datatracker.ietf.org/doc/html/rfc1459
- man pages: `socket(2)`, `bind(2)`, `listen(2)`, `accept(2)`, `poll(2)`, `fcntl(2)`

## AI Usage

AI assistance was used to standardize README style across the repository.

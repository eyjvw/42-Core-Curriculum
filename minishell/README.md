# minishell

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

**minishell** is a minimal shell implementation in C that replicates the behavior of `bash`. It features an AST-based parser, built-in command execution, environment variable expansion, and signal handling.

The shell supports:
- **Command execution** with PATH resolution
- **Pipes** (`|`) and redirections (`>`, `>>`, `<`, `<<`)
- **Logical operators** (`&&`, `||`)
- **Subshells** with grouping
- **Built-in commands:** `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`
- **Variable expansion** (`$VAR`, `$?`)
- **Wildcards** and quote handling
- **Signal handling** (Ctrl+C, Ctrl+D)

## Build

### Compilation

```bash
make
```

This generates the `minishell` executable.

### Makefile Rules

- `make` / `make all` - Compile the shell
- `make clean` - Remove object files
- `make fclean` - Remove binary and objects
- `make re` - Full rebuild

## Usage

```bash
./minishell
```

The shell will then display a prompt and accept commands just like `bash`.

## Project Structure

```
minishell/
├── Makefile                 - Build configuration
├── main.c                   - Entry point
├── includes/                - Headers
├── sources/
│   ├── ast/                 - AST parsing (pipes, redirections, operators)
│   ├── built-in/            - Built-in command implementations
│   ├── exec/                - Command execution engine
│   ├── expand/              - Variable and wildcard expansion
│   ├── tokenizer/           - Lexical analysis
│   ├── utils/               - Utility functions
│   └── signals/             - Signal handlers
├── mk/                      - Shared Makefile fragments
└── valgrind.supp            - Valgrind suppression file
```

## Key Features

### Parser (AST-based)
- Tokenizes input into meaningful units
- Parses into Abstract Syntax Tree
- Handles operator precedence (`&&` > `||` > `|`)
- Supports nested groups and pipes

### Execution
- Forks child processes for commands
- Manages pipes with proper FD redirection
- Implements built-in commands without forking
- Handles HERE-DOC (`<<LIMITER`)

### Expansion
- Variable expansion with `$VAR` syntax
- Special variables: `$?` (exit status), `$0` (program name)
- Wildcard patterns (`*`, `?`)
- Quote handling (single, double, escape)

### Signals
- `Ctrl+C` (SIGINT) - Interrupt current command
- `Ctrl+D` (EOF) - Exit shell
- `Ctrl+\` (SIGQUIT) - Quit current command

## Notes

- The shell follows 42 Norminette coding standards
- Manual memory management with leak checking
- Uses GNU readline for line editing (if available)
- Supports command history via readline

## AI Usage

AI assistance (GitHub Copilot) was used for:
- Code review and refactoring
- Build system optimization
- Documentation generation

Core shell logic and parsing were implemented manually.

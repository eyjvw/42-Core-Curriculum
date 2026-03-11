# pipex

*This project has been created as part of the 42 curriculum by sbonneau.*

## Description

**pipex** is a C program that replicates the behavior of shell piping. It takes an input file, two or more commands, and an output file, and chains the commands together like a shell pipe — connecting each command's stdout to the next command's stdin.

```sh
# Equivalent shell behavior:
< infile cmd1 | cmd2 | ... > outfile

# here_doc mode:
cmd1 | cmd2 << LIMITER >> outfile
```

## Usage

### Compilation

```bash
make
```

### Running

```bash
./pipex infile "cmd1" "cmd2" outfile
# Example:
./pipex input.txt "grep hello" "wc -l" output.txt

# With multiple pipes:
./pipex infile "cmd1" "cmd2" "cmd3" outfile

# here_doc mode (reads from stdin until LIMITER):
./pipex here_doc LIMITER "cmd1" "cmd2" outfile
```

### Makefile Rules

| Rule | Effect |
|------|--------|
| `make` / `make all` | Compile the binary |
| `make clean` | Remove object files |
| `make fclean` | Remove object files and binary |
| `make re` | Full recompile from scratch |

## File Structure

```
pipex/
├── main.c                      - Entry point, pipex loop, child process
├── includes/
│   ├── pipex.h                 - Main header (includes all sub-headers)
│   ├── structs.h               - t_pipex structure definition
│   ├── defines.h               - Constants (BUFFER_SIZE, error messages)
│   └── functions.h             - All function prototypes
├── sources/
│   ├── ft_init.c               - Initialize t_pipex struct
│   ├── ft_open.c               - Open infile / outfile with error handling
│   ├── ft_exec.c               - Command resolution (PATH + absolute) and execve
│   ├── ft_close.c              - Safe fd closing
│   ├── ft_here_doc.c           - here_doc mode via pipe + fork
│   ├── ft_split.c              - Split string by delimiter
│   ├── ft_strcmp.c / ft_strncmp.c - String comparison utilities
│   ├── ft_putstr_fd.c          - Write string to file descriptor
│   ├── get_next_line.c         - Read one line from fd
│   └── get_next_line_utils.c   - GNL string utilities
└── mk/
    ├── variables.mk            - Compiler, sources, flags
    ├── colors.mk               - Terminal color codes
    └── rules.mk                - Make rules
```

## Data Structure: t_pipex

```c
typedef struct s_pipex
{
    int     pipe_fd[2];   // Current pipe (read/write ends)
    int     infile;       // Input file descriptor (-1 if unset)
    int     outfile;      // Output file descriptor (-1 if unset)
    int     prev_fd;      // Read end of previous pipe
    int     here_doc;     // 1 if here_doc mode
    int     cmds_count;   // Number of commands
    char    *limiter;     // here_doc stop word
    int     ac;           // argc
    char    **av;         // argv
    char    **env;        // environment variables
}   t_pipex;
```

## How It Works

### Standard mode

For each command, a `pipe()` + `fork()` is created:
- **Child**: redirects stdin/stdout to the appropriate pipe ends, resolves the command path, calls `execve`
- **Parent**: closes its copy of the write end, keeps the read end as `prev_fd` for the next iteration

The last command's stdout is redirected to `outfile` instead of a pipe.

### Command resolution (`ft_exec`)

1. If the command is an absolute or relative path (`/usr/bin/ls`, `./script.sh`), it's used directly after an `access()` check
2. Otherwise, `PATH` is searched: each directory in `PATH` is tried as `dir/cmd` until one passes `access(X_OK)`
3. Returns exit code `127` if command is not found (matches shell behavior)

### here_doc mode

A dedicated `fork()` reads stdin line by line using `get_next_line`, writing each line into a pipe until the `LIMITER` word is encountered. The read end of this pipe becomes `infile` for the main pipeline. Output is appended (`>>`) instead of truncated.

## Resources

- [man 2 pipe](https://man7.org/linux/man-pages/man2/pipe.2.html)
- [man 2 fork](https://man7.org/linux/man-pages/man2/fork.2.html)
- [man 2 execve](https://man7.org/linux/man-pages/man2/execve.2.html)
- [man 2 dup2](https://man7.org/linux/man-pages/man2/dup2.2.html)
- [42 Norminette](https://github.com/42School/norminette)

## AI Usage

AI assistance (GitHub Copilot) was used for the following tasks:

1. **Code Review**: Identifying fd leak on error paths, uninitialized fields, missing `exit` after command-not-found
2. **Refactoring**: Extracting absolute-path handling, restructuring Makefile into mk/ sub-files
3. **Documentation**: Generating the README structure

Core algorithm design, process/pipe logic, and implementation were done manually.

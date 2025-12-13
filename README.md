# Minishell

A small UNIX shell implemented as part of the 42 curriculum.
It provides a Bash-like interactive prompt with support for pipelines, I/O redirections, heredocs, environment variables, and a subset of built-in commands.

## Features

- **Interactive prompt**
  - Custom prompt: `Minishell >> `
  - Keeps running until `exit` is called or end-of-file (Ctrl-D) is received.

- **Command execution**
  - Run external programs using the `PATH` environment variable.
  - Execute commands using absolute or relative paths.
  - Multiple commands connected with pipelines: `cmd1 | cmd2 | cmd3`.

- **Redirections**
  - Input redirection: `< file`
  - Output redirection (truncate): `> file`
  - Output redirection (append): `>> file`
  - Heredoc: `<< LIMITER` with environment expansion in the here-document body.

- **Environment handling**
  - Internal copy of the parent environment.
  - Variable expansion for `$VAR` and `$?` in command lines.
  - Export / unset variables via built-in commands.

- **Built-ins**
  - `echo` with `-n` option.
  - `cd` with `HOME` and `OLDPWD` support.
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit` with numeric status handling.

- **Signals**
  - `Ctrl-C` (`SIGINT`) clears the current line, prints a new prompt and sets the exit status to `130`.
  - `SIGQUIT` is ignored in the main shell loop.

## Dependencies

- A Unix-like environment with:
  - `gcc`
  - `make`
  - The **readline** library (headers and development library)
- The project already includes:
  - `Libft-42/` (custom libc-like utilities)
  - `ft_printf/` (printf implementation)
  - `get_next_line/` (line reader used for heredocs)

Make sure the `READLINE` path in the root `Makefile` matches your system.
By default it is configured for Homebrew on macOS:

```make
READLINE = -I/Users/$(USER)/homebrew/opt/readline/include \
           -L/Users/$(USER)/homebrew/opt/readline/lib
```

Adapt this variable if your readline installation is located elsewhere.

## Build

From the project root:

```bash
make
```

This will:

- Compile all Minishell sources.
- Build `Libft-42` and `ft_printf`.
- Link everything into the `minishell` executable.

Cleanup targets:

```bash
make clean   # remove object files (including in Libft-42 and ft_printf)
make fclean  # clean + remove the minishell binary and library archives
make re      # full rebuild
```

## Run

After building:

```bash
./minishell
```

You will see the prompt:

```text
Minishell >> 
```

Type commands as you would in a simple Bash-like shell.

- End-of-file (Ctrl-D) exits the shell.
- `exit [status]` exits with the given status (0–255).
- `$?` reflects the exit status of the last executed pipeline or built-in.

## Usage examples

```bash
# basic commands
ls -la
echo "Hello, world"

# echo with -n
echo -n "no trailing newline"

# change directory
cd /tmp
pwd

# environment
export FOO=bar
echo $FOO
unset FOO
env

# redirections
echo "hello" > out.txt
cat < out.txt
echo "append" >> out.txt

# pipelines
cat /etc/passwd | grep bash | wc -l

# heredoc
cat << EOF
line 1
value: $HOME
EOF
```

## Project structure

- `main.c`  
  Main loop: initialization, signal setup, readline prompt, parsing and execution.

- `parsing.c`, `parsing_quotes.c`, `cleaning_quotes.c`  
  Syntax checks for pipes/redirections, quote validation and quote removal.

- `replace_env_vars.c`, `get_env.c`, `shellvl.c`  
  Environment duplication, `$VAR` / `$?` expansion, and `SHLVL` management.

- `tokenize_cmds.c`, `mini_split.c`  
  Split the input line into commands (separated by `|`) and words, respecting quotes.

- `setting_redirections.c`, `check_redirections.c`  
  Detect and extract redirections (`<`, `>`, `>>`, `<<`) and their target files.

- `execute_red.c`, `execute_herdoc.c`, `expand_herdoc.c`  
  Apply I/O redirections and implement heredoc behavior.

- `execution_cmd_pipes.c`, `execution_cmd_pipes_utils.c`  
  Execute pipelines with `fork`, `dup2`, and `execve`, and track child exit statuses.

- `builtins.c`, `builtins_utils.c`, `echo.c`, `export.c`, `unset.c`  
  Implementation of all shell built-ins.

- `Libft-42/`, `ft_printf/`, `get_next_line/`  
  Supporting libraries.

## Notes

This Minishell is designed to satisfy the 42 school project requirements and to emulate a subset of Bash behavior.
It focuses on the features described above and does not aim to be feature-complete compared to Bash.

## Authors

- suibrahi
- ahibrahi

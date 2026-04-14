readme_en_content = """# 🐚 Minishell - A Simple Command-Line Interpreter

> This project is a minimalist shell implementation. It provides a deep dive into process management, file descriptors, and signal handling in C.

---

## 📖 Table of Contents
1. [Introduction](#-introduction)
2. [Project Architecture](#-project-architecture)
3. [Features](#-features)
4. [Installation and Usage](#-installation-and-usage)

---

## 🚀 Introduction
The goal of **Minishell** is to recreate a simplified version of `bash`. The program displays a prompt, reads user input, parses it, and executes the requested commands while managing pipes, redirections, and environment variables.

---

## 📂 Project Architecture

Here is the directory structure as shown in the repository:

```text
MINISHELL/
├── includes/
│   ├── libft/                 # Extended C library (custom functions)
│   └── minishell.h            # Main project header
├── srcs/
│   ├── builtins/              # Internal commands (e.g., cd, echo, exit)
│   │   ├── cd_utils.c
│   │   ├── cd.c
│   │   ├── echo.c
│   │   ├── env.c
│   │   ├── exit.c
│   │   ├── export_utils.c
│   │   ├── export.c
│   │   ├── lists_utils.c
│   │   ├── pwd.c
│   │   └── unset.c
│   ├── exec/                  # Execution logic and signal handling
│   │   ├── child_process_utils.c
│   │   ├── child_process.c
│   │   ├── execute.c
│   │   ├── heredoc.c
│   │   ├── init_signal.c
│   │   ├── redirection.c
│   │   └── signal.c
│   └── parsing/               # Lexical and syntax analysis
│       ├── check_token.c
│       ├── cmd_other_type.c
│       ├── copy_env_utils.c
│       ├── copy_env.c
│       ├── create_cmd_args.c
│       ├── create_cmd.c
│       ├── create_token.c
│       ├── expand_quote.c
│       ├── expand_token_utils.c
│       ├── expand_token.c
│       ├── free.c
│       ├── ft_count_token.c
│       ├── ft_split_mod.c
│       ├── handle_quotes_utils.c
│       ├── handle_quotes.c
│       ├── input_to_token.c
│       ├── is_builtins.c
│       ├── lexer.c
│       ├── minishell.c        # Main entry point
│       ├── parsing.c
│       ├── path_finder.c
│       ├── quote_array.c
│       ├── readline_utils.c
│       ├── readline.c
│       ├── token_pipe.c
│       ├── token_redir_in.c
│       └── token_redir_out.c
├── .gitignore
└── Makefile                   # Compilation script
```
---
## ✨ Features

### 1. Command Management
* **Executables**: Finds and executes programs via the `PATH` variable or absolute/relative paths.
* **Builtins**: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.

### 2. Parsing & Lexing
* Management of **Single Quotes** `'` (literal) and **Double Quotes** `"` (variable expansion).
* **Expansion** of environment variables (e.g., `$USER`, `$HOME`).
* Exit status management of the last command using `$?`.

### 3. Control Operators
* **Pipes (`|`)**: Redirects the output of one command to the input of the next.
* **Redirections**:
    * `<`: Redirect standard input.
    * `>`: Redirect standard output (overwrite).
    * `>>`: Redirect standard output (append).
    * `<<`: Here-document (reads input until a delimiter).

### 4. Signals
* `Ctrl-C`: Displays a new prompt on a clear line.
* `Ctrl-D`: Exits the shell.
* `Ctrl-\ `: Does nothing.

---

## 🛠 Installation and Usage

### Compilation
Use the provided `Makefile` to compile the project:
```bash
make
```

Use the provided `minishell` to compile the project:
```bash
./minishell
```

To track all crashes and memory leaks in the program, you can run `Valgrind` with the following command:<br>
(Make sure to use the suppression file to ignore leaks from `readline`.)
```bash
valgrind --suppressions=readline.supp --leak-check=full --show-leak-kinds=all --track-fds=yes --track-origins=yes --trace-children=yes ./minishell
```

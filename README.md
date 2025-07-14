# Minishell (A Bash Clone) 42 Vienna Coding School Project
A Bash-like shell written in C by my colleague Abel Szabo and me.

## Overview  
Minishell is a custom-built Unix shell created to deepen understanding of low-level system programming. It replicates core features of Bash, including:

- Command parsing and execution  
- Pipes and redirections (`|`, `<`, `>`, `>>`)  
- Environment variable handling (`$`, `$?`)  
- Built-in commands: `cd`, `echo`, `pwd`, `export`, `unset`, `env`, `exit`  
- Signal handling (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`)  
- Command history with termcap navigation

## Technologies  
- C (C89/C90)  
- Unix system calls (`fork`, `execve`, `pipe`, etc.)  
- Termcap for input handling  
- Custom Libft library  

## Build & Run  
```bash
make
./minishell

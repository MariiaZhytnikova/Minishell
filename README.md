# Minishell

**Minishell** is a team project from the Hive Helsinki curriculum, where we developed a simplified Unix shell in C. The objective was to understand and implement core functionalities of a shell, including command parsing, execution, and environment management.

## 🚀 Project Overview

The goal of Minishell is to replicate the behavior of a basic shell, handling:

- Execution of commands with absolute or relative paths
- Command parsing with support for quotes and environment variables
- Input/output redirections and pipelines
- Built-in shell commands
- Signal handling for interactive use

This project provided hands-on experience with process control, file descriptors, and inter-process communication.

## 📁 Project Structure

- `src/`: Contains the source code for the shell's functionalities.
- `inc/`: Header files defining structures and function prototypes.
- `libft/`: Custom implementation of standard C library functions.
- `Makefile`: Automates the build process.

## 🔧 Compilation & Usage

To compile the project, run:

`make`

`./minishell`

## 🛠️ Features

- Command Execution: Supports execution of commands using absolute or relative paths.
- Built-in Commands: Implements echo, cd, pwd, export, unset, env, and exit.
- Pipelines: Allows chaining of commands using the pipe (|) operator.
- Redirections:
  - Input redirection (<)
  - Output redirection (>)
  - Append output redirection (>>)
  - Here-document (<<)
- Quoting:
  - Single quotes (') preserve the literal value of characters.
  - Double quotes (") preserve the literal value of all characters except $.
- Environment Variables: Expands variables prefixed with $.
- Signal Handling: Handles Ctrl+C, Ctrl+\, and Ctrl+D appropriately.

## 🧠 What We Learned

- Managing processes and file descriptors in Unix
- Parsing and interpreting shell commands
- Implementing a command-line interface with interactive features
- Handling signals and ensuring proper resource management
- Collaborating effectively in a team environment


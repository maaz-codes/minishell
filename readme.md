# Minishell

Minishell is a simple Unix shell built in C, mimicking basic functionalities of `bash`. It provides an interactive command-line interface, allowing users to execute common shell commands and manage processes. The project explores concepts like process creation, signal handling, file redirection, and pipe management, offering an in-depth understanding of how a shell operates behind the scenes.

## Key Features
- Displaying a custom prompt.
- Execution of commands using both relative and absolute paths.
- Handling of pipes (`|`) and redirections (`<`, `>`, `<<`, `>>`).
- Basic signal handling (e.g., `Ctrl-C`, `Ctrl-D`).
- Support for shell built-in commands:
  - `echo` with `-n` option
  - `cd`
  - `pwd`
  - `export`
  - `unset`
  - `env`
  - `exit`
- Environment variable expansion (e.g., `$PATH`, `$?`).

## Project Overview
This project is part of the curriculum at 42 Abu Dhabi, focusing on:
- Process management
- File descriptors
- Command parsing and execution

By completing this project, students gain deeper insights into how Unix-based shells function at their core.

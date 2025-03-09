# Minishell

Minishell is a minimalistic shell implementation for Unix-like systems, developed as part of the 42 curriculum. It mimics the behavior of Bash while reinforcing understanding of process management, system calls, and input parsing.

## Features
- Displays a prompt and waits for user input.
- Parses and executes simple commands.
- Supports environment variables.
- Implements built-in commands: `echo`, `cd`, `pwd`, `export`, `unset`, `env`, `exit`.
- Handles redirections (`>`, `>>`, `<`).
- Supports pipes (`|`) to chain commands.
- Manages processes and signals (`Ctrl+C`, `Ctrl+D`, `Ctrl+\`).
- Implements basic error handling.

## Installation
```sh
# Clone the repository
git clone https://github.com/maaz-codes/minishell.git
cd minishell

# Compile the shell
make
```

## Usage
```sh
# Run Minishell
./minishell

# Example commands
minishell$ echo "Hello, world!"
minishell$ ls -l | grep minishell
minishell$ export VAR=test && echo $VAR
```

## Built-in Commands
| Command   | Description |
|-----------|-------------|
| `echo`    | Prints arguments to the terminal |
| `cd`      | Changes the current directory |
| `pwd`     | Prints the current working directory |
| `export`  | Sets environment variables |
| `unset`   | Unsets environment variables |
| `env`     | Displays environment variables |
| `exit`    | Exits the shell |

## Signals
- `Ctrl+C` (SIGINT) - Interrupts the current command.
- `Ctrl+D` (EOF) - Exits the shell.
- `Ctrl+\` (SIGQUIT) - Terminates the running process.

## Credits
Developed by Maaz Khan & Raphael Creer as part of the 42 Abu Dhabi curriculum.

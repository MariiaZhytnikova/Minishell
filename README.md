# Minishell
The objective of this project is for you to create a simple shell. 

## Core Features (The Main Components):

Input Parsing:  
   - Handle user input and parse commands.
   - Tokenize the input (split into commands, arguments, and operators).
   - Handle spaces and special characters like quotes, redirections, etc.

Execution:
   - Execute the command by forking processes.
   - Handle built-in commands like echo, cd, pwd, exit.
   - Handle external commands by searching for executables in directories listed in $PATH.

Redirection:
   - Implement input and output redirections (<, >, >>).
   - Handle file descriptors (STDOUT, STDIN, STDERR).
   - Handle append mode with >>.

Pipes:
   - Implement piping (|) between commands (e.g., command1 | command2).
   - Handle multiple pipes in a single command (e.g., command1 | command2 | command3).

Built-in Commands:
   - Implement built-in commands like cd, exit, echo, pwd.
   - Handle their functionalities and edge cases.

Signals:
   - Handle signals like SIGINT (Ctrl+C) and SIGQUIT (Ctrl+).
   - Implement custom signal handling for foreground and background processes.

Environment Variables:
   - Implement access to environment variables (like $HOME, $PATH).
   -  Handle export, unset, and env commands.

Error Handling:
   - Implement error messages for invalid commands and arguments.
   - Handle memory allocation errors or process failures.

Bonus Features (if applicable for 42 project):

    Job Control:
        Implement background jobs with &.
        Implement fg, bg, and jobs built-in commands.
    History:
        Implement a history mechanism for recalling previous commands.
    Tab Completion:
        Implement basic tab completion for commands or file paths.

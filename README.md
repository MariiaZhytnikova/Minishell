# Minishell

The objective of this project is for you to create a simple shell.   

### Usefull resources:  
https://harm-smits.github.io/42docs/projects/minishell  
https://m4nnb3ll.medium.com/minishell-building-a-mini-bash-a-42-project-b55a10598218

### Shell should:
Run simple commands with absolute, relative path (e.g. /bin/ls, ../bin/ls)  
Run simple commands without a path (e.g. ls, cat, grep, etc…)  
Have a working history (you can navigate through commands with up/down arrows)  
Implement pipes (|)  
Implement redirections (<, >, >>)  
Implement the here-doc (<<)  
Handle double quotes ("") and single quotes (''), which should escape special characters, beside $ for double quotes.  
Handle environment variables ($ followed by a sequence of characters).  
Handle signals like in bash (ctrl + C, ctrl + \, ctrl + D).  
Implement the following built-ins:  
- echo (option -n only)
- exit
- env (with no options or arguments)
- export (with no options)
- unset (with no options)
- cd
- pwd

And for the bonus part (optional, but i did it, because it’s cool!) 
- handle && and || with the parenthesis () for priority.
- handle * wildcards for the current working directory.

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

## Git Workflow for the Project

### Branching Strategy:

   You can follow a simple Git branching model to ensure smooth collaboration between two people.

   - Main branch (main): This is the stable version of your project. Only merge into main when everything works and is tested.

   - Feature branches: For each new task, create a separate branch. This allows you to work on different features simultaneously without interfering with each other’s code.  
        Example: feature/input-parsing, feature/redirection, feature/pipes, feature/builtins.

   - Merge requests: When one of you finishes a task on a feature branch, create a Pull Request (PR) to merge into the main branch. The other team member should review the code and test it.

### Task Distribution Using Git:

   - Create a new branch for each task: Start a branch when you begin working on a task. Each task corresponds to a Git branch (e.g., feature/input-parsing or feature/redirection).

   - Commit frequently: Make small, frequent commits with meaningful commit messages, such as:
        Implemented input parsing for basic commands
        Fixed bug in redirection for stdin

   - Pull regularly: Pull the latest changes from the main branch to keep your local branch up to date.

### Example Git Workflow:

   - Create the repository and initialize the main branch.
   - Create feature branches for different tasks.
   - Commit your work frequently with clear commit messages.
   - Push changes to the remote repository.
   - Open pull requests (PR) and have the other teammate review the changes before merging into the main branch.
   - Merge and test the code in the main branch when both features are working.

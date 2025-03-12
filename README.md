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

### Allowed functions:

   - # readline # -  readline will read a line from the terminal and return it, using  prompt as a prompt.  If prompt is NULL or the empty string, no prompt is issued.  The line returned is allocated with malloc(3); the caller must                            free it when finished.  The line returned has the final newline removed, so only the text of the line remains.
   - rl_clear_history - The rl_clear_line() function clears the history list by deleting all of the entries. The rl_clear_line() function frees data that the readline library saves in the histroy list.
   - rl_on_new_line - Tell the update routines that we have moved onto a new (empty) line, usually after ouputting a newline. 
   - rl_replace_line - Replace the contents of rl_line_buffer with text. 
   - rl_redisplay - The rl_redisplay() change what's displayed on the screen to reflect the current contents of rl_line_buffer.
   - add_history -  Saves the line passed as parameter in the history so it can be retrieved later in the terminal (like pressing the up arrow in bash).
   - wait3, wait4 - These functions are obsolete; use waitpid(2) in new programs. 
   - signal - signal is obsolete; use sigaction.
   - sigaction - The sigaction() system call is used to change the action taken by a process on receipt of a specific signal.
   - sigemptyset -  Initialises the signal set pointed to by set, such that all signals defined in this document are excluded.  Return 0 on success and -1 on error. 
   - sigaddset - Adds the individual signal specified by the signo to the signal set pointed to by set. Applications must call sigemptyset() at least once for each object of type sigset_t prior to any other use of that object.
   - getcwd - Place an absolute pathname of the current working directory in the array pointed to by buf, and return buf. The pathname copied to the array shall contain no components that are symbolic links.
   - chdir - Changes the current working directory of the calling process to the directory specified in path.
   - stat, stat, fstat - These functions return information about a file, in the buffer pointed to by statbuf.  No permissions are required on the file itself, but—in the case of stat(), fstatat(), and lstat()—execute (search)                               permission is required on all of the directories in pathname that lead to the file. stat() retrieve information about the file pointed to by pathname; lstat() is identical to stat(), except that if pathname is a                         symbolic link, then it returns information about the link itself, not the file that the link refers to. fstat() is identical to stat(), except that the file about which information is to be retrieved is specified                        by the file descriptor fd.
   - unlink - Deletes a name from the filesystem.  If that name was the last link to a file and no processes have the file open, the file is deleted and the space it was using is made available for reuse.
   - opendir -  The opendir() function opens a directory stream corresponding to the directory name, and returns a pointer to the directory stream. The stream is positioned at the first entry in the directory.
   - readdir - returns a pointer to a dirent structure representing the next directory entry in the directory stream pointed to by dirp.  It returns NULL on reaching the end of the directory stream or if an error occurred.
   - closedir - closes the directory stream associated with dirp.  A successful call to closedir() also closes the underlying file descriptor associated with dirp. The directory stream descriptor dirp is not available after this call.
   - isatty - Tests whether fd is an open file descriptor referring to a terminal.
   - ttyname -  The function ttyname() returns a pointer to the null-terminated pathname of the terminal device that is open on the file descriptor fd, or NULL on error (for example, if fd is not connected to a terminal)
   - ttyslot - finds the slot of the current user's terminal in some file
   - ioctl - Ioctl in Linux stands for Input Output Control. It is a system call used to talk to device drivers. Most Linux drivers support the ioctl system. Ioctl is used in cases where the kernel does not support a system call for                         the driver or does not have a default system call to communicate with the driver.
   - tcsetattr - Shall set the parameters associated with the terminal referred to by the open file descriptor fildes from the termios structure referenced by termios_p
   - tcgetattr - The tcgetattr() function shall get the parameters associated with with the terminal reffered to by fildes and store them in the termios structure referenced by termios_p.
   - tgetent - Loads the entry for name. It returns 1 on success, 0 if there is no such entry, and -1 if the terminfo database could not be found. The emulation ignores the buffer pointer bp. 
   - tgetflag-  Gets the boolean entry for id, or zero if it is not available. 
   - tgetnum - Gets the numeric entry for id, or -1 if it is not available. 
   - tgetstr - Returns the string entry for id, or zero if it is not available. 
   - tgoto - Instantiates the parameters into the given capability. The output from this routine is to be passed to tputs. 
   - tputs - applies padding information to the string str and outputs it.

   - printf, malloc, free, write, access, open, read, close, fork, wait, waitpid, exit, kill, dup, dup2, pipe, execve, perror, strerror, getenv

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:09:19 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/12 16:29:02 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minishell.h"

# ifndef LEN_PATH
# define LEN_PATH 4096
#endif

// Text Colors
# define RESET		"\033[0m"
# define BLACK		"\033[30m"
# define RED		"\033[31m"
# define GREEN		"\033[32m"
# define YELLOW		"\033[33m"
# define BLUE		"\033[34m"
# define MAGENTA	"\033[35m"
# define CYAN		"\033[36m"
# define WHITE		"\033[37m"
# define BOLD		"\033[1m"

// Keys
# define DEL	127
# define UP		"\e[A"
# define DOWN	"\e[B"
# define LEFT	"\e[C"
# define RIGHT	"\e[D"

// Structures

// [char *delimiter] Indicates what is separating this cmd table from the next
// ** - delimiter = "\0" (last command table)
// ** - delimiter = ";" (consecutive execution of the next cmd table)
// ** - delimiter = "||" (execution of the next cmd table only if the previous has
// ** - delimiter = "&&"" (execution of the next cmd table only if the previous has
// ** a truthy exit_status)
// ** - ">"  - redirect stdout (for files: also overwrite file's content)
// ** - ">>" - redirect stdout (for files: also append to file's content)
// ** - "<"  - redirect stdin
// ** - "<<" - here doc

typedef enum
{
	REDIRECT_OUTPUT,
	REDIRECT_INPUT,
	REDIRECT_OUTPUT_APPEND,
	HEREDOC,
}	redirect;

typedef enum
{
	PIPE,
	AND,		// "&&" (execution of the next cmd table only if the previous has a truthy exit_status)
	OR,			// "||" (execution of the next cmd table only if the previous has
	// BACKGROUND, // "&" at the end of a command, it causes the command to run in the background
	// // execute as fork() -> child, In parent process, do not wait for the child
	NONE, // or use end
	END // ??
}	delimiter;

typedef enum
{
	COMMAND,
	ARGUMENT,
	WILDCARD,	// Expand with value
	// O_PARENT,	// Should be closed // # Error: Missing closing parenthesis
	// C_PARENT,
	// // Square brackets [] are used for conditional tests (in the same way as the test command). They 
	// 	//evaluate an expression and return a success or failure status based on the condition inside the brackets.
	// // [ -z ] // # Error: Missing argument to -z
	// // {}, () run only with one arg, it need ";" for more args, check if closed
}	arguments;


typedef struct s_list
{
	char	*value;
	t_list	*next;
}	t_list;

typedef	struct s_command
{
	int			id;					// ID for the command (used to identify commands)
	char		*command;			// The actual command (e.g., "ls", "grep")
	char		*delimiter;			// Delimiter between commands
	char		*args;				// Arguments for the command (e.g., ["-al"], ["foo"])
	char		*input_redirect;	// Input redirection (if any)
	char		*output_redirect;	// Output redirection (if any, e.g., "> output.txt")
	char		*error_redirect;	// redirect error file?
	int			nbr_cmds;
	int			status;
	//int		background;			// Flag for background execution (if any)
} t_command;

typedef struct	s_history
{
	char		*cmd_line;	// Stores the actual command entered by the user.
	t_history	*prev;		// Pointer to the previous command in the history (linked list).
	t_history	*next;		// Pointer to the next command in the history (linked list).
}	t_history;

typedef struct	s_session
{
	char		*input; // ?? do we need after tokenization
	size_t		len_input;
	size_t		prompt_len; // ?? do we need after tokenization 
	bool		is_history;
	t_history	*history;
	char		**env_dup;
	t_command	**command_tree;
	int			status_last;
	// terminating things
}	t_session;

#endif

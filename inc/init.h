/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:09:19 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/31 17:53:23 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minishell.h"

# ifndef LEN_PATH
# define LEN_PATH 4096
# define MAX_PROMT 131072
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

#define PROMPT	"\001" GREEN BOLD "\002minishell$ \001" RESET "\002"

// Keys
# define DEL	127
# define UP		"\e[A"
# define DOWN	"\e[B"
# define LEFT	"\e[C"
# define RIGHT	"\e[D"

// Structures

// [char *delimiter] Indicates what is separating this cmd table from the next

typedef enum
{
	NONE,
	PIPE,
	AND,							// "&&" (execution of the next cmd table only if the previous has a truthy exit_status)
	OR,								// "||" (execution of the next cmd table only if the previous has
}	delimiter;

// typedef enum
// {
// 	REDIRECT_INPUT,					// "<"  - redirect stdin
// 	REDIRECT_OUTPUT, 				// ">"  - redirect stdout (for files: also overwrite file's content)
// 	REDIRECT_OUTPUT_APPEND, 		// ">>" - redirect stdout (for files: also append to file's content)
// 	HEREDOC,						//"<<" - here doc
// }	redirect;

typedef	struct s_count
{
	int			cmd_nb;
	int			*args_nb;
	int			delimiter_nb;
	int			*red_in_nb;
	int			*red_out_nb;
	int			*red_app_nb;
	int			*red_h_doc_nb;
	int			here_doc;
}	t_count;

typedef struct	s_command
{
	int			pid;
	char		*command;
	char		**args;		// need NULL teminate
	char		**in;		// need NULL teminate
	char		**out;		// need NULL teminate
	char		**out_app;	// need NULL teminate
	char		**h_doc;	// need NULL teminate
	delimiter	type;
	int			status;
}	t_command;

typedef struct	s_history
{
	char				*cmd_line;	// Stores the actual command entered by the user.
	struct	s_history	*prev;		// Pointer to the previous command in the history (linked list).
	struct	s_history	*next;		// Pointer to the next command in the history (linked list).
}	t_history;

typedef struct	s_session
{
	char		*input; 			// ?? do we need after tokenization
	size_t		len_input;
	size_t		prompt_len;			// ?? do we need after tokenization 
	bool		is_history;
	t_history	*history;
	t_command	**cmds;
	int			status_last;
	t_list		*env_var;
	t_count		*count;
									// terminating things
}	t_session;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:09:19 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/02 12:53:10 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minishell.h"

# define LEN_PATH 4096
# define MAX_PROMT 131072

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



typedef enum
{
	PIPE,
	AND,							// "&&" (execution of the next cmd table only if the previous has a truthy exit_status)
	OR,								// "||" (execution of the next cmd table only if the previous has a false exit_status)
}	delimiter;

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
	char		**args;
	char		**in;
	char		**out;
	char		**out_app;
	char		**h_doc;
	delimiter	type;
	int			status;
}	t_command;

typedef struct	s_session
{
	char		*input; 			// ?? do we need after tokenization
	size_t		len_input;
	size_t		prompt_len;			// ?? do we need after tokenization 
	bool		is_history;
	t_command	**cmds;
	int			status_last;
	t_list		*env_var;
	t_count		*count;
									// terminating things
}	t_session;

#endif

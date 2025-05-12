/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 10:09:19 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/12 14:56:01 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INIT_H
# define INIT_H

# include "minishell.h"

# define LEN_PATH 4096
# define MAX_PR 231072

# define RESET		"\033[0m"
# define CYAN		"\033[36m"
# define BOLD		"\033[1m"
# define PROMPT		"\001\033[32m\033[1m\002minishell$ \001\033[0m\002"

typedef enum e_redir_type
{
	STD,
	IN_FILE,
	HERE_DOC,
	OUT_FILE,
	OUT_APPEND,
}	t_redir_type;

typedef enum e_del_type
{
	NONE,
	PIPE,
	AND,
	OR,
}	t_del_type;

typedef struct s_temp
{
	char	*temp;
	int		i;
	int		j;
	size_t	cap;
}	t_temp;

typedef struct s_file
{
	int				fd;
	char			*name;
	t_redir_type	type;
}	t_file;

typedef struct s_count
{
	int			cmd_nb;
	int			*args_nb;
	int			delimiter_nb;
	int			*red_in_nb;
	int			*red_out_nb;
	int			*red_app_nb;
	int			here_doc;
}	t_count;

typedef struct s_command
{
	int			pid;
	char		**args;
	t_file		**files;
	t_file		*last_in;
	t_file		*last_out;
	t_del_type	type;
	int			status;
}	t_command;

typedef struct s_session
{
	char		*input;
	char		*history_pipe;
	t_command	**cmds;
	int			status_last;
	t_list		*env_var;
	t_count		*count;
	int			in;
	int			out;
	int			prev_fd;
	int			pipefd[2];
}	t_session;

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:43:38 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/02 15:28:05 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

typedef struct s_temp
{
	char	temp[MAX_PROMT];
	int		i;
	int		j;
}	t_temp;

bool	delimiter_wrong_pos(t_list *token);
bool	consecutive_delimiters(t_list *token);
bool	is_del(char *content);
bool	is_red(char *content);
int		numbers(t_session *session, t_list **token, t_count *count);

int		here_doc_no_lim(t_session *session, t_list **token);
int		here_doc_lim(t_session *session, t_list **token);
int		if_quotes(t_session *session, t_temp *thing, char *args);
int		handle_quotes(t_session *session, t_temp *thing, char *args);
bool	is_delim_or_red(char *str);
int		expansion(t_session *session, t_temp *thing, char *str);
int		expansion_two(t_session *session, char **str);
char	*add_spaces(t_session *session, char *input);
int		split_and_check(t_session *session, t_list **token, char *src);

int		redirection_in(t_command *command, t_list *current);
int		redirection_out(t_command *command, t_list *current);

void	get_delimiter(t_command *command, t_list *current);
int		allocate_struct(t_session *s, t_count *c, int i);
int		handle_command(t_command *command, t_list **current, int i);
int		commands(t_session *session, t_list **token);
int		lexical_analyzer(t_session *session);

int		prompt(t_session *session);
int		history(t_session *session);
int		add_pipe_history(t_session *session, char *line);

int		wild(t_list **token);

////////////////////////DELETE/////////////
void	print_me_num(t_count *count);
void	print_me(t_session *session);
///////////////////////////////////////

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:43:38 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/26 10:17:24 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

bool	delimiter_wrong_pos(t_list *token);
bool	consecutive_delimiters(t_list *token);
bool	is_del(char *content);
bool	is_red(char *content);
int		numbers(t_list **token, t_count *count);

int		here_doc_no_lim(t_list **token);
int		here_doc_lim(t_list **token);
int		if_quotes(char *temp, char *args, int *i, int *j);
int		handle_quotes(char *temp, char *args, int *i);
bool	is_delim_or_red(char *str);
void	copy_delimeter(char *temp, char *str, int *i, int *j);
char	*add_spaces(char *input);
int		split_and_check(t_list **token, char *src);

int		redirection_in(t_command *command, t_list *current);
int		redirection_out(t_command *command, t_list *current);

void	get_delimiter(t_command *command, t_list *current);
int		allocate_struct(t_session *s, t_count *c, int i);
int		handle_command(t_command *command, t_list **current, int i);
int		commands(t_session *session, t_list **token);
int		lexical_analyzer(t_session *session);
void	promt(t_session *session);

#endif
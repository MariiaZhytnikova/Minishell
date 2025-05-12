/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/17 16:43:38 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/11 15:08:58 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# include "minishell.h"

int		dynstr_init(t_temp *thing, char *input);
int		dynstr_char(t_temp *thing, char *str);
int		dynstr_str(t_temp *thing, char *str);
int		dynstr_symb(t_temp *thing, char c);

bool	delimiter_wrong_pos(t_list *token);
bool	consecutive_delimiters(t_list *token);
bool	is_del(char *content);
bool	is_red(char *content);
int		numbers(t_session *session, t_list **token);

int		replace_token(t_list *current, char *buffer);
int		here_doc_no_lim(t_session *session, t_list **token);
int		here_doc_lim(t_list **token);

int		skip_sq(t_temp *thing, char *args);
int		if_quotes(t_temp *thing, char *args);
int		handle_quotes(t_temp *thing, char *args);

int		status(t_session *session, t_temp *thing);
int		expansion(t_session *session, t_temp *thing, char *str, int exp);

int		copy_delimeter(t_temp *thing, char *str);
int		split_input(t_list **token, char *args);
int		split_and_check(t_session *session, t_list **token, char *src);

int		files(t_command *command, t_list *current, char *cont);
int		redirection_in(t_command *command, t_list *current, char *cont);
int		redirection_out(t_command *command, t_list *current, char *cont);

void	get_delimiter(t_command *command, t_list *current);
int		get_redirection(t_session *session, t_command *cmd, t_list *curr);
int		get_arguments(t_session *session, t_list *curr, t_list **args);
t_list	*get_exp(t_session *session, char *content, int split);

int		allocate_struct(t_session *s, int i);
int		red_struct_alloc(t_session *session);

int		commands(t_session *session, t_list **token);
int		lexical_analyzer(t_session *session);

int		prompt(t_session *session);
int		history(t_session *session);
int		add_pipe_history(t_session *session, char *line);

int		skip_copy(char *arg, t_temp *thing, char c);
int		skip_quotes(t_temp *thing, char *arg);
char	*skip(char *content);
int		create_new(t_list **args, t_list *new, char *str);
bool	is_in_quotes(const char *str);
bool	match(const char *str, const char *pattern);
int		wild(t_list **exp_red);

////////////////////////DELETE/////////////
void	print_me_num(t_count *count);
void	print_me(t_session *session);
///////////////////////////////////////

#endif
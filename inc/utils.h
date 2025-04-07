/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:43 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/04 16:08:13 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	error_msg(char *start, char *details, char *c, char *error);
void	free_arr(char **arr);
int		skip_whitespace(const char *str);
size_t	word_count(char *str); // ?????????????????????????????????????????//////
int		longer(char *s1, char *s2);
long	ft_atol(const char *str);
int		ft_isspace(int c);
size_t	ft_var_name_len(const char *s);
void	free_session(t_session *session);
void	*reall(void *ptr, size_t old_size, size_t new_size);

// Linked list utils

void	print_linked_list(t_list *lst);
void	delete_node_by_content(t_list **list, char *variable);
int		create_node(t_list **env_var, char *content);
void	create_env_list(t_list **env_var, char **env);
void	swap_content(t_list *a, t_list *b);
void	add_new_var(t_session *session, t_command *cmd, char *val);
int		split_input(t_session *session, t_list **token, char *args);

#endif
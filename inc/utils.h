/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:43 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/20 14:58:14 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "libft.h"

// Common utils

void	error_msg(char *start, char *details, char *c, char *error);
void	free_arr(char **arr);
int		skip_whitespace(const char *str, int i);
size_t	word_count(char *str);
void	split_input(t_list **token, char *args);
long	ft_atol(const char *str);
int		ft_isspace(int c);

// Linked list utils

void	free_linked_list(t_list *head);
void	print_linked_list(t_list *lst);
void	delete_node_by_content(t_list **list, char *variable, int flag);
int		create_node(t_list **env_var, char *content);
void	create_env_list(t_list **env_var, char **env);
void	delete_node_by_content(t_list **list, char *variable, int flag);

#endif
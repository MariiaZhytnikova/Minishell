/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:43 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/20 17:06:01 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"
# include "libft.h"

void	error_msg(char *beginning, char *details, char *error);
void	free_arr(char **arr);
int		skip_whitespace(const char *str);
size_t	word_count(char *str); //?????????????????????///
int		longer(char *s1, char *s2);
void	*reall(void *ptr, size_t old_size, size_t new_size);

void	print_linked_list(t_list *lst);
int		split_input(t_list **token, char *args, int size);
int		create_node(t_list *env_var, char *value);
t_list	*create_env_list(char **env);
void	free_linked_list(t_list **head);
void	delete_node_by_content(t_list **list, char *variable, int flag);
void	delete_nodes_by_content(t_list **head, char *variable);

#endif
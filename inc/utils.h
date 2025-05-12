/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:43 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/12 13:27:44 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

void	error_msg(char *start, char *details, char *c, char *error);
void	free_arr(char **arr);
int		skip_whitespace(const char *str);
int		longer(char *s1, char *s2);
long	ft_atol(const char *str);
int		ft_isspace(int c);
int		ft_isalnum_plus(int c);
size_t	ft_var_name_len(const char *s);
void	free_session(t_session *session);
void	*reall(void *ptr, size_t old_size, size_t new_size);
int		array_size(t_file **array);
void	d_return(void);

// Linked list utils

void	print_linked_list(t_list *lst);
void	delete_node_by_content(t_list **list, char *variable);
int		create_node(t_list **env_var, char *content);
int		create_env_list(t_list **env_var, char **env);
void	swap_content(t_list *a, t_list *b);
void	add_new_var(t_session *session, t_command *cmd, char *val);
char	**list_to_arr(t_list *list);

// Execution utils

int		num_pipes(t_session *session, int *id);
void	group_free(t_session *session);
char	*get_current_path(t_command *cmd);

// Tokenization utils

int		red_struct_alloc(t_session *session);
int		allocate_struct(t_session *session, int i);
int		copy_args(t_command *cmd, t_list **args);
int		copy_delimeter(t_temp *thing, char *str);
int		status(t_session *session, t_temp *thing);
int		replace_token(t_list *current, char *buffer);
bool	not_valid(char c);

#endif
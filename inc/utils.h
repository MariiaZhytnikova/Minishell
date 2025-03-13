/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 11:39:43 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/13 12:07:53 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_H
# define UTILS_H

# include "minishell.h"

size_t	ft_strlen(const char *str);
void	free_arr(char **arr);
void	*ft_calloc(size_t num, size_t size);
char	*ft_strjoin(char *s1, char *s2);
size_t	word_count(char *str);
void	split_input(char **res, char *args, int k);

void	ft_lstadd_back(t_list **lst, t_list *new_node);
int		ft_lstsize(t_list *lst);


#endif
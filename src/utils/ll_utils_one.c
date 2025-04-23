/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_utils_one.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:33:01 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/22 14:45:43 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	add_new_var(t_session *session, t_command *cmd, char *val)
{
	t_list	*new;

	new = ft_lstnew(val);
	if (!new)
	{
		error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL);
		cmd->status = EXIT_FAILURE;
		return ;
	}
	ft_lstadd_back(&session->env_var, new);
}

char	**list_to_arr(t_list *list)
{
	char	**arr;
	int		i;
	t_list	*current;

	i = 0;
	current = list;
	arr = malloc(sizeof(char *) * (ft_lstsize(list) + 1));
	if (!arr)
		return (NULL);
	while (current)
	{
		arr[i] = ft_strdup(current->content);
		if (!arr[i])
			return (NULL);
		current = current->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

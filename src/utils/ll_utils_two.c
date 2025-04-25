/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ll_utils_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:33:01 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/24 10:42:45 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	create_node(t_list **env_var, char *value)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (new_node == NULL)
		return (1);
	new_node->next = NULL;
	new_node->content = ft_strdup(value);
	if (new_node->content == NULL)
	{
		free(new_node);
		return (1);
	}
	if (*env_var == NULL)
		*env_var = new_node;
	else
	{
		last_node = ft_lstlast(*env_var);
		last_node->next = new_node;
	}
	return (0);
}

void	create_env_list(t_list **env_var, char **env)
{
	int	i;

	i = 0;
	if (!*env || !**env)								// FIX env - i
	{
		create_node(env_var, NULL);
		return;
	}
	while (env[i])
	{
		if (create_node(env_var, env[i]))
		{
			error_msg("create_env_list", NULL, NULL, NULL);
			ft_lstclear(env_var, free);
			return ;
		}
		i++;
	}
}

void	delete_node_by_content(t_list **list, char *variable)
{
	t_list	*current;
	t_list	*prev;
	size_t	len;

	current = *list;
	prev = NULL;
	len = ft_strlen(variable);
	while (current)
	{
		if (!ft_strncmp(current->content, variable, len)
			&& ((char *)current->content)[len] == '=')
		{
			if (prev == NULL)
				*list = current->next;
			else
				prev->next = current->next;
			return (free(current->content), free(current));
		}
		prev = current;
		current = current->next;
	}
}

void	swap_content(t_list *a, t_list *b)
{
	void	*temp;

	temp = a->content;
	a->content = b->content;
	b->content = temp;
}

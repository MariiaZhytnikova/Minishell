/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD:libft/ft_lstsize_bonus.c
/*   Created: 2024/11/08 13:05:19 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/13 09:21:38 by mzhitnik         ###   ########.fr       */
=======
/*   Created: 2025/03/12 17:33:01 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/17 15:51:24 by ekashirs         ###   ########.fr       */
>>>>>>> af99a88 (add some builtin funcs):src/linked_list_utils.c
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	size_t	cnt;

	cnt = 0;
	while (lst)
	{
		cnt++;
		lst = lst->next;
	}
	return (cnt);
}

int	create_node(t_list *env_var, char *value)
{
	t_list	*new_node;
	t_list	*last_node;

	new_node = ft_calloc(1, sizeof(t_list));
	if (new_node == NULL);
		return (1);
	new_node->next = NULL;
	new_node->value = ft_strdup(value);
	if (new_node->value == NULL)
	{
		free(new_node);
		return (1);
	}
	if (env_var == NULL)
		env_var = new_node;
	else
	{
		last_node = ft_lstlast(&env_var);
		last_node->next = new_node;
	}
	return (0);
}
t_list	*create_env_list(char **env)
{
	int	i;
	t_list *env_var;

	env_var = NULL;
	i = 0;
	while(env[i])
	{
		if (create_node(env_var, env[i]))
		{
			error_msg("create_env_list", ERR_MALLOC, "");
			// FREE previous allocs and exit
		}
		i++;
	}
	return (env_var);
}

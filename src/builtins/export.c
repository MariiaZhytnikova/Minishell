/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:10 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/07 13:47:41 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	compare_env(const char *a, const char *b)
{
	while (*a && *b && *a != '=' && *b != '=')
	{
		if (*a != *b)
			return (*a - *b);
		a++;
		b++;
	}
	return (*a - *b);
}

static void	sort_export(t_list *copy)
{
	int		i;
	t_list	*ptr;
	t_list	*last_ptr;

	last_ptr = NULL;
	i = 1;
	while (i)
	{
		i = 0;
		ptr = copy;
		while (ptr->next != last_ptr)
		{
			if (compare_env(ptr->content, ptr->next->content) > 0)
			{
				swap_content(ptr, ptr->next);
				i = 1;
			}
			ptr = ptr->next;
		}
		last_ptr = ptr;
	}
}

static t_list	*copy_list(t_list *start)
{
	t_list	*copy;
	t_list	*new_node;
	char	*content;

	copy = NULL;
	while (start)
	{
		content = ft_strdup((char *)start->content);
		new_node = ft_lstnew(content);
		if (!content || !new_node)
		{
			free(content);
			ft_lstclear(&copy, free);
			return (NULL);
		}
		ft_lstadd_back(&copy, new_node);
		start = start->next;
	}
	return (copy);
}

static void	print_export(t_list *copy)
{
	t_list	*ptr;

	ptr = copy;
	while (ptr)
	{
		printf("declare -x %s\n", (char *)ptr->content);
		ptr = ptr->next;
	}
}

void	export_builtin(t_session *session, t_command *cmd)
{
	t_list	*copy;

	if (!cmd->args[1])
	{
		copy = copy_list(session->env_var);
		if (copy == NULL)
		{
			error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL);
			cmd->status = 1;
			return ;
		}
		sort_export(copy);
		print_export(copy);
		ft_lstclear(&copy, free);
	}
	else
	{
		handle_args(session, cmd);
		if (cmd->status == 1)
			return ;
	}
	cmd->status = 0;
}

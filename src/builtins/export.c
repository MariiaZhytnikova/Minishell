/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:10 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/25 17:27:24 by ekashirs         ###   ########.fr       */
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
	t_list	*current;
	t_list	*original;
	t_list	*copy;

	if (!start)
		return (NULL);
	copy = ft_lstnew((char *)start->content);
	if (!copy)
		return (NULL);
	current = copy;
	original = start->next;
	while (original)
	{
		current->next = ft_lstnew((char *)original->content);
		if (!current->next)
		{
			ft_lstclear(&copy, free);
			return (NULL);
		}
		current = current->next;
		original = original->next;
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
			cmd->status = EXIT_FAILURE;
			return ;
		}
		sort_export(copy);
		print_export(copy);
		ft_lstclear(&copy, free);
	}
	else
	{
		handle_args(session, cmd);
		if (cmd->status == EXIT_FAILURE)
			return ;
	}
	cmd->status = EXIT_SUCCESS;
}

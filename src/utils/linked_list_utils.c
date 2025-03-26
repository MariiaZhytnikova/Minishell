/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:33:01 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/26 13:54:14 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_linked_list(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		printf("%s\n", (char *)current->content);
		current = current->next;
	}
}

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
	while(env[i])
	{
		if (create_node(env_var, env[i]))
		{
			error_msg("create_env_list", NULL, NULL, NULL);
			// FREE previous allocs and exit
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
		if (!strncmp(current->content, variable, len)
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
	void *temp = a->content;
	a->content = b->content;
	b->content = temp;
}

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

int	split_input(t_list **token, char *args, int size)
{
	int		i;
	char	temp[size + 1];
	t_list	*new_token;

	ft_memset(temp, 0, size + 1);
	i = skip_whitespace(args);
	if (!args[i])
		return (1);
	if (handle_quotes(temp, args, &i) < 0)
		return (-1);
	new_token = ft_lstnew(ft_strdup(temp));
	if (!new_token)
		return (-1);
	ft_lstadd_back(token, new_token);
	if (args[i])
	{
		if (split_input(token, &args[i], ft_strlen(&args[i])) < 0)
			return (-1);
	}
	return (1);
}

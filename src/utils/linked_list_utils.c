/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:33:01 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/16 12:54:51 by ekashirs         ###   ########.fr       */
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

int	split_input(t_session *session, t_list **token, char *args)
{
	t_list	*new_token;
	t_temp	thing;

	ft_memset(thing.temp, 0, MAX_PROMT);
	thing.i = skip_whitespace(args);;
	thing.j = 0;
	if (!args[thing.i])
		return (1);
	if (handle_quotes(session, &thing, args) < 0)
		return (-1);
	new_token = ft_lstnew(ft_strdup(thing.temp));
	if (!new_token)
		return (-2);
	ft_lstadd_back(token, new_token);
	if (args[thing.i])
	{
		if (split_input(session, token, &args[thing.i]) < 0)
			return (-2);
	}
	return (1);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linked_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 17:33:01 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/17 15:46:31 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*ft_lstnew(void *content)
{
	t_list	*new;

	new = (t_list *)malloc(sizeof(*new));
	if (!new)
		return (NULL);
	new->content = content;
	new->next = NULL;
	return (new);
}

t_list	*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	last = *lst;
	if (new == NULL)
		return ;
	if (lst == NULL || *lst == NULL)
	{
		*lst = new;
		return ;
	}
	while (last->next != NULL)
		last = last->next;
	last->next = new;
}

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

void	ft_lstdelone(t_list *lst, void (*del)(void *))
{
	if (!del || !lst)
		return ;
	(*del)(lst->content);
	free(lst);
}

void	free_linked_list(t_list *head)
{
	t_list	*current;
	t_list	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->content);
		free(current);
		current = next;
	}
}

void	print_linked_list(t_list *lst)
{
	t_list	*current;

	current = lst;
	while (current != NULL)
	{
		printf("%s\n", current->content);
		current = current->next;
	}
}

void	split_input(t_list **token, char *args)
{
	int	i;
	int	start;
	int	end;
	t_list	*new_token;

	start = 0;
	start = skip_whitespace(&args[start], 0);
	if (!args[start])
		return ;
	end = start;
	while (args[end] && !(args[end] == ' ' || args[end] == '\t' || args[end] == '\n' || args[end] == '\r'))
		end++;
	new_token = ft_lstnew(ft_substr(args, start, end));
	ft_lstadd_back(token, new_token);
	if (args[end])
		split_input(token, &args[end]);
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

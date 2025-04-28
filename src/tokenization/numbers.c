/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:28:21 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/28 12:42:21 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	cmd_number(t_list **token, t_count *count)
{
	t_list	*current;

	current = *token;
	while (current)
	{
		if (is_del(current->content) == false
			&& is_red(current->content) == false)
		{
			count->cmd_nb += 1;
			current = current->next;
			while (current && is_del(current->content) == false)
				current = current->next;
		}
		if (current)
			current = current->next;
	}
}

void	count_arguments(t_list **token, t_count *count)
{
	t_list	*current;
	int		i;

	i = 0;
	current = *token;
	while (current)
	{
		if (is_del(current->content) == false)
		{
			if (is_red(current->content) == true)
				current = current->next->next;
			while (current && is_del(current->content) == false)
			{
				if (is_red(current->content) == true)
					current = current->next;
				else
					count->args_nb[i] += 1;
				current = current->next;
			}
			i++;
		}
		else
			current = current->next;
	}
}

static void	count_red(t_list **current, t_count *count, int i)
{
	if (ft_strncmp((*current)->content, "<",
			longer((*current)->content, "<")) == 0)
	{
		count->red_in_nb[i] += 1;
		*current = (*current)->next;
	}
	if (ft_strncmp((*current)->content, ">",
			longer((*current)->content, ">")) == 0)
	{
		count->red_out_nb[i] += 1;
		*current = (*current)->next;
	}
	if (ft_strncmp((*current)->content, ">>",
			longer((*current)->content, ">>")) == 0)
	{
		count->red_app_nb[i] += 1;
		*current = (*current)->next;
	}
	if (ft_strncmp((*current)->content, "<<<",
			longer((*current)->content, ">>>")) == 0)
		*current = (*current)->next;
}

void	count_delim_and_redir(t_list **token, t_count *count)
{
	t_list	*current;
	int		i;

	current = *token;
	i = 0;
	while (current)
	{
		if (is_del(current->content) == true)
		{
			i++;
			count->delimiter_nb += 1;
			current = current->next;
		}
		else if (is_red(current->content) == true)
		{
			count_red(&current, count, i);
			current = current->next;
		}
		else
			current = current->next;
	}
}

int	numbers(t_session *session, t_list **token, t_count *count)
{
	count->cmd_nb = 0;
	count->delimiter_nb = 0;
	cmd_number(token, count);
	count->args_nb = (int *)ft_calloc(count->cmd_nb + 1, sizeof(int));
	count->red_in_nb = (int *)ft_calloc(count->cmd_nb + 1, sizeof(int));
	count->red_out_nb = (int *)ft_calloc(count->cmd_nb + 1, sizeof(int));
	count->red_app_nb = (int *)ft_calloc(count->cmd_nb + 1, sizeof(int));
	if (!count->args_nb || !count->red_in_nb || !count->red_out_nb
		|| !count->red_app_nb)
		return (-1);
	count_arguments(token, count);
	count_delim_and_redir(token, count);
	if (allocate_struct(session, count, 0) < 0)
		return (-1);
	return (1);
}

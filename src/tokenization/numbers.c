/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   numbers.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 14:28:21 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/12 11:34:31 by mzhitnik         ###   ########.fr       */
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

int	numbers(t_session *s, t_list **token)
{
	s->count = ft_calloc(1, sizeof(t_count));
	if (!s->count)
		return (-1);
	cmd_number(token, s->count);
	s->count->args_nb = (int *)ft_calloc(s->count->cmd_nb + 1, sizeof(int));
	s->count->red_in_nb = (int *)ft_calloc(s->count->cmd_nb + 1, sizeof(int));
	s->count->red_out_nb = (int *)ft_calloc(s->count->cmd_nb + 1, sizeof(int));
	s->count->red_app_nb = (int *)ft_calloc(s->count->cmd_nb + 1, sizeof(int));
	if (!s->count->args_nb || !s->count->red_in_nb || !s->count->red_out_nb
		|| !s->count->red_app_nb)
		return (-1);
	count_arguments(token, s->count);
	count_delim_and_redir(token, s->count);
	if (allocate_struct(s, 0) < 0)
		return (-1);
	if (red_struct_alloc(s) < 0)
		return (-1);
	return (1);
}

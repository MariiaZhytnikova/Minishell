/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:31:53 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/25 15:37:11 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	files_alloc(t_session *session, int num, int id)
{
	session->cmds[id]->last_in = ft_calloc(1, sizeof(t_file));
	session->cmds[id]->last_out = ft_calloc(1, sizeof(t_file));
	session->cmds[id]->files = ft_calloc(num, sizeof(t_file *));
	if (!session->cmds[id]->last_in || !session->cmds[id]->last_out
		|| !session->cmds[id]->files)
		return (-1);
	return (1);
}

int	red_struct_alloc(t_session *session)
{
	int	i;
	int	j;
	int	num_red;

	i = 0;
	while (i < session->count->cmd_nb)
	{
		j = 0;
		num_red = session->count->red_in_nb[i]
			+ session->count->red_out_nb[i] + session->count->red_app_nb[i] + 1;
		if (files_alloc(session, num_red, i) < 0)
			return (-1);
		while (j < num_red - 1)
		{
			session->cmds[i]->files[j] = ft_calloc(1, sizeof(t_file));
			if (!session->cmds[i]->files[j])
				return (-1);
			j++;
		}
		session->cmds[i]->files[j] = NULL;
		i++;
	}
	return (1);
}

int	allocate_struct(t_session *s, t_count *c, int i)
{
	s->cmds = (t_command **)ft_calloc(c->cmd_nb + 1, sizeof(t_command *));
	if (!s->cmds)
		return (error_msg("Command tree alloc failed", NULL, NULL, NULL), -1);
	while (i < c->cmd_nb)
	{
		s->cmds[i] = ft_calloc(1, sizeof(t_command));
		if (!s->cmds)
			return (-1);
		s->cmds[i]->args = ft_calloc(c->args_nb[i] + 1, sizeof(char *));
		if (! s->cmds[i]->args)
			return (error_msg(ERR_BASH, ERR_CRASH,
					"allocate_struct", NULL), -1);
		i++;
	}
	return (1);
}

int	dynstr_init(t_temp *thing, char *input)
{
	thing->i = 0;
	thing->j = 0;
	thing->cap = ft_strlen(input) * 2;
	thing->temp = ft_calloc(1, thing->cap);
	if (!thing->temp)
		return (-1);
	return (1);
}

void	dynstr_append_char(t_temp *thing, char *str)
{
	if (thing->j + 2 >= (int)thing->cap)
	{
		thing->temp = reall(thing->temp, thing->cap, thing->cap * 2);
		thing->cap *= 2;
	}
	thing->temp[(thing->j)++] = str[(thing->i)++];
	thing->temp[(thing->j)] = '\0';
}

void	dynstr_append_str(t_temp *thing, char *str)
{
	int	i;

	if (!str || !*str)
		return ;
	if (thing->j + ft_strlen(str) + 1 >= thing->cap)
	{
		thing->temp = reall(thing->temp, thing->cap, thing->cap * 2);
		thing->cap *= 2;
	}
	i = 0;
	while (str[i])
		thing->temp[(thing->j)++] = str[i++];
	thing->temp[(thing->j)] = '\0';
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_one.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:31:53 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/05 19:28:23 by mzhitnik         ###   ########.fr       */
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

int	allocate_struct(t_session *session, int i)
{
	session->cmds = (t_command **)ft_calloc(session->count->cmd_nb + 1,
			sizeof(t_command *));
	if (!session->cmds)
		return (error_msg("Command tree alloc failed", NULL, NULL, NULL), -1);
	while (i < session->count->cmd_nb)
	{
		session->cmds[i] = ft_calloc(1, sizeof(t_command));
		if (!session->cmds[i])
			return (-1);
		session->cmds[i]->args = NULL;
		i++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:31:53 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/22 12:02:16 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirection(t_command *command, t_list *current)
{
	int	size;

	if (files(command, current) < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "files", NULL), -1);
	if (redirection_in(command, current) < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "redirection_in", NULL), -1);
	if (redirection_out(command, current) < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "redirection_OUT", NULL), -1);
	return (1);
}

void	get_delimiter(t_command *command, t_list *current)
{
	if ((ft_strncmp(current->content,
				"|", longer(current->content, "|")) == 0))
		command->type = PIPE;
	else if ((ft_strncmp(current->content,
				"||", longer(current->content, "||")) == 0))
		command->type = OR;
	else if ((ft_strncmp(current->content,
				"&&", longer(current->content, "&&")) == 0))
		command->type = AND;
}

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

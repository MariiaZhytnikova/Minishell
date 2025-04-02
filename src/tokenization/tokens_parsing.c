/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:31:53 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/02 10:35:40 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_redirection(t_command *command, t_list *current)
{
	int	size;

	if (redirection_in(command, current) < 0)
		return (error_msg("wrong with redirection_in\n", NULL, NULL, NULL), -1);
	if (redirection_out(command, current) < 0)
		return (error_msg("wrong with redirection_out\n", NULL, NULL, NULL), -1);
	return (1);
}

void	get_delimiter(t_command *command, t_list *current)
{
	if ((ft_strncmp(current->content, \
			"|", longer(current->content, "|")) == 0))
		command->type = PIPE;
	else if ((ft_strncmp(current->content, \
			"||", longer(current->content, "||")) == 0))
		command->type = OR;
	else if ((ft_strncmp(current->content, \
			"&&", longer(current->content, "&&")) == 0))
		command->type = AND;
}

int	handle_command(t_command *command, t_list **current, int i)
{
	while (*current && is_del((*current)->content) == false)
	{
		if (is_red((*current)->content) == true)
		{
			if (get_redirection(command, *current) < 0)
				return (-1);
			*current = (*current)->next->next;
		}
		else if (*current)
		{
			if (!command->command)
			{
				command->command = ft_strdup((*current)->content);
				if (!command->command)
					return (-1);
			}
			command->args[i] = ft_strdup((*current)->content);
			if (!command->args[i])
				return (-1);
			*current = (*current)->next;
			i++;
		}
	}
	return (1);
}

static int	alloc_check(t_command *cmd, t_count *c, int i)
{
	if (c->args_nb[i] > 0 && !cmd->args)
		return (-1);
	if (c->red_in_nb[i] > 0 && !cmd->in)
		return (-1);
	if (c->red_out_nb[i] > 0 && !cmd->out)
		return (-1);
	if (c->red_app_nb[i] > 0 && !cmd->out_app)
		return (-1);
	if (c->red_h_doc_nb[i] > 0 && !cmd->h_doc)
		return (-1);
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
			return (error_msg("Comm tree alloc failed", NULL, NULL, NULL), -1);
		if (c->args_nb[i] > 0)
			s->cmds[i]->args = ft_calloc(c->args_nb[i] + 1, sizeof(char *));
		if (c->red_in_nb[i] > 0)
			s->cmds[i]->in = ft_calloc(c->red_in_nb[i] + 1, sizeof(char *));
		if (c->red_out_nb[i] > 0)
			s->cmds[i]->out = ft_calloc(c->red_out_nb[i] + 1, sizeof(char *));
		if (c->red_app_nb[i] > 0)
			s->cmds[i]->out_app = ft_calloc(c->red_app_nb[i] + 1, \
				sizeof(char *));
		if (c->red_h_doc_nb[i] > 0)
			s->cmds[i]->h_doc = ft_calloc(c->red_h_doc_nb[i] + 1, \
				sizeof(char *));
		if (alloc_check(s->cmds[i], c, i) < 0)
			return (error_msg("Smthg wrong allocate_struct", NULL, NULL, NULL), -1);
		i++;
	}
	return (1);
}

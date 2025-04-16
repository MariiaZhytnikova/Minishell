/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_parsing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:31:53 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/16 10:45:47 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_redirection(t_command *command, t_list *current)
{
	int	size;

	if (files(command, current) < 0)
		return(error_msg(ERR_BASH, ERR_CRASH, "files", NULL), -1);
	if (redirection_in(command, current) < 0)
		return(error_msg(ERR_BASH, ERR_CRASH, "redirection_in", NULL), -1);
	if (redirection_out(command, current) < 0)
		return(error_msg(ERR_BASH, ERR_CRASH, "redirection_OUT", NULL), -1);
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

static int	alloc_check(t_command *cmd, t_count *c, int i)
{
	if (c->args_nb[i] > 0 && !cmd->args)
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
			return (-1);
		s->cmds[i]->args = ft_calloc(c->args_nb[i] + 1, sizeof(char *));
		if (c->red_h_doc_nb[i] > 0)
			s->cmds[i]->h_doc = ft_calloc(c->red_h_doc_nb[i] + 1, \
				sizeof(char *));
		if (alloc_check(s->cmds[i], c, i) < 0)
			return(error_msg(ERR_BASH, ERR_CRASH, "allocate_struct", NULL), -1);
		i++;
	}
	return (1);
}

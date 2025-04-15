/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/12 11:52:33 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/15 12:11:57 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	open_last_in(t_command *cmd)
{
	int	fd;

	if (access(cmd->last_in->name, F_OK) == 0 \
		&& access(cmd->last_in->name, R_OK) != 0)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, cmd->args[0], ERR_PERM, NULL), -1);
	}
	fd = open(cmd->last_in->name, O_RDONLY);
	if (fd == -1)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, cmd->args[0], ERR_NOFILE, NULL), -1);
	}
	return (fd);
}

static int	open_last_out(t_command *cmd)
{
	int	fd;

	if (access(cmd->last_out->name, F_OK) == 0 \
		&& access(cmd->last_out->name, W_OK) != 0)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, cmd->args[0], ERR_PERM, NULL), -1);
	}
	fd = open(cmd->last_out->name, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, cmd->args[0], ERR_NOFILE, NULL), -1);
	}
	return (fd);
}

static int	open_last_out_append(t_command *cmd)
{
	int	fd;

	if (access(cmd->last_out->name, F_OK) == 0 \
		&& access(cmd->last_out->name, W_OK) != 0)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, cmd->args[0], ERR_PERM, NULL), -1);
	}
	fd = open(cmd->last_out->name, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, cmd->args[0], ERR_NOFILE, NULL), -1);
	}
	return (fd);
}

void	handle_in_out(t_command *cmd)
{
	int	pipefd[2];

	if (cmd->last_in->type != STD)
	{
		if (cmd->last_in->type == IN_FILE)
			cmd->last_in->fd = open_last_in(cmd);
		else if (cmd->last_in->type == HERE_DOC)
		{
			if (pipe(pipefd) == -1)
				return (error_msg(ERR_BASH, ERR_PIPE, NULL, NULL));
			write(pipefd[1], cmd->last_in->name, ft_strlen(cmd->last_in->name));
			close(pipefd[1]);
			cmd->last_in->fd = pipefd[0];
		}
		dup2(cmd->last_in->fd, STDIN_FILENO);
		close(cmd->last_in->fd);
	}
	if (cmd->last_out->type != STD)
	{
		if (cmd->last_out->type == OUT_FILE)
			cmd->last_out->fd = open_last_out(cmd);
		else if (cmd->last_out->type == OUT_APPEND)
			cmd->last_out->fd = open_last_out_append(cmd);
		dup2(cmd->last_out->fd, STDOUT_FILENO);
		close(cmd->last_out->fd);
	}
}

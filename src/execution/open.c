/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:56:50 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/16 11:30:46 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_file(t_command *cmd, char *file)
{
	int fd;

	if (access(file, F_OK) == 0 && access(file, R_OK) != 0)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, file, ERR_PERM, NULL), -1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, file, ERR_NOFILE, NULL), -1);
	}
	close(fd);
	return (1);
}

static int	out_file(t_command *cmd, char *file)
{
	int fd;

	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, file, ERR_PERM, NULL), -1);
}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, file, ERR_NOFILE, NULL), -1);
	}
	close(fd);
	return (1);
}

static int	out_app_file(t_command *cmd, char *file)
{
	int fd;

	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, file, ERR_PERM, NULL), -1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		cmd->status = 1;
		return (error_msg(ERR_BASH, file, ERR_NOFILE, NULL), -1);
	}
	close(fd);
	return (1);
}

int	open_files(t_session *session, t_command *cmd, int id)
{
	int	i;
	// int	num;

	i = 0;
	// num = session->count->red_in_nb[id] + \
	// 	session->count->red_out_nb[id] + session->count->red_app_nb[id];
	// while (i < num - 1)
	while(cmd->files[i])
	{
		if (cmd->files[i]->type == IN_FILE)
		{
			if (in_file(cmd, cmd->files[i]->name) < 0)
				return (-1);
		}
		else if (cmd->files[i]->type == OUT_FILE)
		{
			if (out_file(cmd, cmd->files[i]->name) < 0)
				return (-1);
		}
		else if (cmd->files[i]->type == OUT_APPEND)
		{
			if (out_app_file(cmd, cmd->files[i]->name) < 0)
				return (-1);
		}
		i++;
	}
	return (1);
}

// grep hi <./test_files/infile

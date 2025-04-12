/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:56:50 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/12 12:08:47 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	in_file(t_command *cmd, char *file)
{
	int	fd;

	if (access(file, F_OK) == 0 && access(file, R_OK) != 0)
	{
		cmd->status = 1;
		return (error_msg("permission denied: in in_file", NULL, NULL, NULL), -1);
	}
	fd = open(file, O_RDONLY);
	if (fd == -1)
	{
		cmd->status = 127;
		return (error_msg("No such file or directory: ", NULL, NULL, NULL), -1);
	}
	close(fd);
	return (1);
}

static int	out_file(t_command *cmd, char *file)
{
	int	fd;

	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
	{
		cmd->status = 1;
		return (error_msg("permission denied: in out_file", NULL, NULL, NULL), -1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		cmd->status = 127;
		return (error_msg("No such file or directory: ", NULL, NULL, NULL), -1);
	}
	close(fd);
	return (1);
}

static int	out_app_file(t_command *cmd, char *file)
{
	int	fd;

	if (access(file, F_OK) == 0 && access(file, W_OK) != 0)
	{
		cmd->status = 1;
		return (error_msg("permission denied: in out_app_file", NULL, NULL, NULL), -1);
	}
	fd = open(file, O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (fd == -1)
	{
		cmd->status = 127;
		return (error_msg("No such file or directory: ", NULL, NULL, NULL), -1);
	}
	close(fd);
	return (1);
}

int	open_files(t_session *session, t_command *cmd, int ind)
{
	int	i;

	i = 0;
	while (i < session->count->red_in_nb[ind])
	{
		if (in_file(cmd, cmd->in[i++]) < 0)
			return (-1);
	}
	i = 0;
	while (i < session->count->red_out_nb[ind])
	{
		if (out_file(cmd, cmd->out[i++]) < 0)
			return (-1);
	}
	i = 0;
	while (i < session->count->red_app_nb[ind])
	{
		if (out_app_file(cmd, cmd->out_app[i++]) < 0)
			return (-1);
	}
	return (1);
}

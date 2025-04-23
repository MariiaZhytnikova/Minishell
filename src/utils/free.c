/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:14:13 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/22 13:31:43 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_arr(char **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

void	free_tfile(t_file **arr)
{
	int	i;

	if (!arr)
		return ;
	i = 0;
	while (arr[i])
	{
		free(arr[i]->name);
		free(arr[i]);
		i++;
	}
	free(arr);
}

static void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->args)
		free_arr(cmd->args);
	if (cmd->files)
		free_tfile(cmd->files);
	if (cmd->last_in)
	{
		if (cmd->last_in->name)
			free(cmd->last_in->name);
		free(cmd->last_in);
	}
	if (cmd->last_out)
	{
		if (cmd->last_out->name)
			free(cmd->last_out->name);
		free(cmd->last_out);
	}
	free(cmd);
}

static void	free_count(t_count *count)
{
	if (!count)
		return ;
	if (count->args_nb)
		free(count->args_nb);
	if (count->red_in_nb)
		free(count->red_in_nb);
	if (count->red_out_nb)
		free(count->red_out_nb);
	if (count->red_app_nb)
		free(count->red_app_nb);
	if (count->red_h_doc_nb)
		free(count->red_h_doc_nb);
	free(count);
}

void	free_session(t_session *session)
{
	int	i;

	if (!session)
		return ;
	if (session->input)
		free(session->input);
	if (session->history_pipe)
		free(session->history_pipe);
	if (session->cmds)
	{
		i = 0;
		while (session->cmds[i])
		{
			free_command(session->cmds[i]);
			i++;
		}
		free(session->cmds);
	}
	if (session->count)
		free_count(session->count);
}

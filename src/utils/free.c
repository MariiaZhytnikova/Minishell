/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 17:14:13 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/01 13:17:31 by ekashirs         ###   ########.fr       */
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

static void	free_history(t_history *history)
{
	t_history	*tmp;

	tmp = NULL;
	while (history)
	{
		tmp = history->next;
		free(history->cmd_line);
		free(history);
		history = tmp;
	}
}

static void	free_command(t_command *cmd)
{
	if (!cmd)
		return ;
	if (cmd->command)
		free(cmd->command);
	if (cmd->args)
		free_arr(cmd->args);
	if (cmd->in)
		free_arr(cmd->in);
	if (cmd->out)
		free_arr(cmd->out);
	if (cmd->out_app)
		free_arr(cmd->out_app);
	if (cmd->h_doc)
		free_arr(cmd->h_doc);
	free(cmd);
}

static void	free_count(t_count *count)
{
	if (!count)
		return;
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
}

void	free_session(t_session *session)
{
	int	i;

	if (!session)
		return ;
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

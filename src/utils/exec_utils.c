/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:11:29 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/07 13:34:50 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_pipes(t_session *session, int *id)
{
	int	count;
	int	i;

	i = *id;
	count = 0;
	while (session->cmds[i]->type == PIPE)
	{
		i++;
		count++;
	}
	return (count);
}

void	group_free(t_session *session)
{
	ft_lstclear(&session->env_var, free);
	rl_clear_history();
	free_session(session);
}

char	*get_current_path(t_command *cmd)
{
	char	cwd[1024];
	char	*cur_cmd;

	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		ft_strlcat(cwd, "/", sizeof(cwd));
		cur_cmd = ft_strjoin(cwd, cmd->args[0]);
		if (!cur_cmd)
			return (error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL), NULL);
		return (cur_cmd);
	}
	cmd->status = 127;
	return (error_msg(ERR_BASH, cmd->args[0], ERR_NO, NULL), NULL);
}

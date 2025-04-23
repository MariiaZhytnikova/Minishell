/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:41 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/22 14:26:00 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_with_code(t_session *session, t_command *cmd)
{
	int		i;
	long	status;
	int		exit_status;

	i = 0;
	if (cmd->args[1][i] == '-' || cmd->args[1][i] == '+')
		i++;
	while (cmd->args[1][i])
	{
		if (!ft_isdigit(cmd->args[1][i]))
		{
			error_msg(ERR_BASH, cmd->args[0], ERR_NUM, NULL);
			close(session->in);
			close(session->out);
			group_free(session);
			exit(2);
		}
		i++;
	}
	status = ft_atol(cmd->args[1]);
	exit_status = (unsigned char)status;
	close(session->in);
	close(session->out);
	group_free(session);
	exit(exit_status);
}

void	exit_builtin(t_session *session, t_command *cmd)
{
	printf("exit\n");
	if (!cmd->args[1])
	{
		close(session->in);
		close(session->out);
		group_free(session);
		exit(0);
	}
	if (cmd->args[2])
	{
		error_msg(ERR_BASH, cmd->args[0], ERR_MANY_ARGS, NULL);
		cmd->status = 1;
		return ;
	}
	exit_with_code(session, cmd);
}

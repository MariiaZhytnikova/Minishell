/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:41 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/25 15:23:49 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_with_code(t_session *session, t_command *cmd)
{
	long	status;
	int		exit_status;

	status = ft_atol(cmd->args[1]);
	exit_status = (unsigned char)status;
	close(session->in);
	close(session->out);
	group_free(session);
	exit(exit_status);
}

static void	check_non_numeric(t_session *session, char *arg)
{
	int	i;

	i = 0;
	if (arg[i] == '-' || arg[i] == '+')
		i++;
	while (arg[i])
	{
		if (!ft_isdigit(arg[i]))
		{
			error_msg(ERR_BASH, arg, ERR_NUM, NULL);
			close(session->in);
			close(session->out);
			group_free(session);
			exit(2);
		}
		i++;
	}
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
	check_non_numeric(session, cmd->args[1]);
	if (cmd->args[2])
	{
		error_msg(ERR_BASH, cmd->args[0], ERR_MANY_ARGS, NULL);
		cmd->status = 1;
		return ;
	}
	exit_with_code(session, cmd);
}

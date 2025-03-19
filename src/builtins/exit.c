/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:41 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/19 13:45:30 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exit_with_code(t_command *cmd)
{
	int		i;
	long	status;
	int		exit_status;

	i = 0;
	if (cmd->args[0][i] == '-' || cmd->args[0][i] == '+')
		i++;
	while (cmd->args[0][i])
	{
		if (!ft_isdigit(cmd->args[0][i]))
		{
			error_msg(ERR_BASH, cmd->command, ERR_NUM);
			free_struct(cmd) // ???
			exit(2);
		}
		i++;
	}
	status = ft_atol(cmd->args[0]);
	exit_status = (unsigned char)status;
	free_struct(cmd) // ???
	exit(exit_status);
}

void	exit_builtin(t_command *cmd)
{
	printf("exit\n");
	if (!cmd->args[0])
	{
		free_struct(cmd) // ???
		exit(0);
	}
	if (cmd->args[1])
	{
		error_msg(ERR_BASH, cmd->command, ERR_MANY_ARGS);
		cmd->status = 1;
		return ;
	}
	exit_with_code(cmd);
}

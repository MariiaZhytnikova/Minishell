/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:17:38 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/02 16:31:10 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(t_session *session, t_command *cmd)
{
	if (!ft_strncmp(cmd->command, "exit", longer(cmd->command, "exit")))
		exit_builtin(session, cmd);
	else if (!ft_strncmp(cmd->command, "cd", longer(cmd->command, "cd")))
		cd_builtin(session, cmd);
	else if (!ft_strncmp(cmd->command, "env", longer(cmd->command, "env")))
		env_builtin(session, cmd);
	else if (!ft_strncmp(cmd->command, "pwd", longer(cmd->command, "pwd")))
		pwd_builtin(cmd);
	else if (!ft_strncmp(cmd->command, "unset", longer(cmd->command, "unset")))
		unset_builtin(session, cmd);
	else if (!ft_strncmp(cmd->command, "echo", longer(cmd->command, "echo")))
		echo_builtin(cmd);
	else if (!ft_strncmp(cmd->command, "export", longer(cmd->command, "export")))
		export_builtin(session, cmd);
	else
		printf("To be done...\n");
}

int exec(t_session *session)
{
	t_command *cmd;
	int	i;

	cmd = *session->cmds;
	i = 0;
	while (session->cmds[i])
	{
		// if (session->cmds[i]->type == PIPE)
		// 	run_pipe(session->cmds[i], session->cmds[i + 1]);
		// if (session->cmds[i]->type == AND)
		// 	run_and(session->cmds[i], session->cmds[i + 1]);
		// if (session->cmds[i]->type == OR)
		// 	run_or(session->cmds[i], session->cmds[i + 1]);
		run_cmd(session, session->cmds[i]);
		i++;
	}
	return (0);
}

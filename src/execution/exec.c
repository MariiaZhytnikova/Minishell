/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:17:38 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/02 12:53:48 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_cmd(t_session *session, t_command *cmd)
{
	if (!ft_strncmp(cmd->command, "exit", ft_strlen("exit")))
		exit_builtin(session, cmd);
	else if (!ft_strncmp(cmd->command, "cd", ft_strlen("cd")))
		cd_builtin(session, cmd);
	else if (!ft_strncmp(cmd->command, "env", ft_strlen("env")))
		env_builtin(session, cmd);
	else if (!ft_strncmp(cmd->command, "pwd", ft_strlen("pwd")))
		pwd_builtin(cmd);
	else if (!ft_strncmp(cmd->command, "unset", ft_strlen("unset")))
		unset_builtin(session, cmd);
	else if (!ft_strncmp(cmd->command, "echo", ft_strlen("echo")))
		echo_builtin(cmd);
	else if (!ft_strncmp(cmd->command, "export", ft_strlen("export")))
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
	// while (session->cmds[i])
	// {
	// 	if (session->cmds[i]->type == PIPE)
	// 		run_pipe(session->cmds[i], session->cmds[i + 1]);
	// 	if (session->cmds[i]->type == AND)
	// 		run_and(session->cmds[i], session->cmds[i + 1]);
	// 	if (session->cmds[i]->type == OR)
	// 		run_or(session->cmds[i], session->cmds[i + 1]);
	// 	run_cmd(session, session->cmds[i]);
	// 	i++;
	// }
	return (0);
}

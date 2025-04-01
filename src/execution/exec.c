/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:17:38 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/31 16:30:00 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int exec(t_session *session)
{
	t_command *cmd;

	cmd = *session->cmds;
	if (cmd->command == NULL)
	{
		printf("Command is null\n");
		return (0);
	}
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
		printf("Command not found\n");

	return (0);
}

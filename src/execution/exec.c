/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:17:38 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/07 14:58:27 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exec_builtin(t_session *session, t_command *cmd)
{
	if (!ft_strncmp(cmd->args[0], "exit", longer(cmd->args[0], "exit")))
		return (exit_builtin(session, cmd));
	else if (!ft_strncmp(cmd->args[0], "cd", longer(cmd->args[0], "cd")))
		return (cd_builtin(session, cmd));
	else if (!ft_strncmp(cmd->args[0], "env", longer(cmd->args[0], "env")))
		return (env_builtin(session, cmd));
	else if (!ft_strncmp(cmd->args[0], "pwd", longer(cmd->args[0], "pwd")))
		return (pwd_builtin(cmd));
	else if (!ft_strncmp(cmd->args[0], "unset", longer(cmd->args[0], "unset")))
		return (unset_builtin(session, cmd));
	else if (!ft_strncmp(cmd->args[0], "echo", longer(cmd->args[0], "echo")))
		return (echo_builtin(cmd));
	else if (!ft_strncmp(cmd->args[0], "export",
			longer(cmd->args[0], "export")))
		return (export_builtin(session, cmd));
}

static bool	is_builtin(t_command *cmd)
{
	if (!cmd->args || !cmd->args[0])
		return (false);
	if (!ft_strncmp(cmd->args[0], "exit", longer(cmd->args[0], "exit")))
		return (true);
	else if (!ft_strncmp(cmd->args[0], "cd", longer(cmd->args[0], "cd")))
		return (true);
	else if (!ft_strncmp(cmd->args[0], "env", longer(cmd->args[0], "env")))
		return (true);
	else if (!ft_strncmp(cmd->args[0], "pwd", longer(cmd->args[0], "pwd")))
		return (true);
	else if (!ft_strncmp(cmd->args[0], "unset", longer(cmd->args[0], "unset")))
		return (true);
	else if (!ft_strncmp(cmd->args[0], "echo", longer(cmd->args[0], "echo")))
		return (true);
	else if (!ft_strncmp(cmd->args[0], "export",
			longer(cmd->args[0], "export")))
		return (true);
	return (false);
}

static void	run_builtin(t_session *session, int *id)
{
	if (open_files(session->cmds[*id]) < 0)
	{
		session->status_last = session->cmds[*id]->status;
		return ;
	}
	session->in = dup(0);
	session->out = dup(1);
	handle_in_out(session->cmds[*id]);
	exec_builtin(session, session->cmds[*id]);
	session->status_last = session->cmds[*id]->status;
	dup2(session->in, 0);
	dup2(session->out, 1);
	close(session->in);
	close(session->out);
}

void	run_cmd(t_session *session, t_command *cmd)
{
	int	status;

	if ((!cmd->args[0] || !cmd->args[0][0])
			&& (cmd->last_in->type != STD || cmd->last_out->type != STD))
	{
		group_free(session);
		exit (0);
	}
	if (is_builtin(cmd))
	{
		exec_builtin(session, cmd);
		status = cmd->status;
		group_free(session);
		exit (status);
	}
	exec_norm(session, cmd);
}

void	exec(t_session *session, int *id)
{
	if (session->count->cmd_nb == 1 && session->count->args_nb[0] > 0
		&& is_builtin(session->cmds[*id]) == true)
	{
		run_builtin(session, id);
		session->status_last = session->cmds[*id]->status;
		return ;
	}
	run_pipe(session, id);
	if (session->cmds[*id] && session->cmds[*id - 1]->type == AND)
		run_and(session, id);
	if (session->cmds[*id] && session->cmds[*id - 1]->type == OR)
		run_or(session, id);
	session->status_last = session->cmds[*id - 1]->status;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:17:38 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/16 09:02:20 by mzhitnik         ###   ########.fr       */
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
	else if (!ft_strncmp(cmd->args[0], "export", \
		longer(cmd->args[0], "export")))
		return (export_builtin(session, cmd));
}

static bool	is_builtin(t_command *cmd)
{
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
	else if (!ft_strncmp(cmd->args[0], "export", \
		longer(cmd->args[0], "export")))
		return (true);
	return (false);
}

static void	run_builtin(t_session *session, int *id)
{
	if (open_files(session, session->cmds[*id], *id) < 0)
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
	if (!cmd->args[0])
	{
		ft_lstclear(&session->env_var, free);
		free_session(session);
		cmd->status = 0;
		exit (cmd->status);
	}
	if (is_builtin(cmd))
	{
		exec_builtin(session, cmd);
		exit (cmd->status);
	}
	exec_norm(session, cmd);
}

void	exec(t_session *session, int *id)
{
	if (session->count->cmd_nb == 1 && session->count->args_nb[0] > 0 \
		&& is_builtin(session->cmds[*id]) == true)
	{
		run_builtin(session, id);
		session->status_last = session->cmds[*id]->status;
		return ;
	}
	run_pipe(session, id);
	// printf("ID of next COMMAND is: %d\n", *id);
	if (session->cmds[*id] && session->cmds[*id - 1]->type == AND)
		run_and(session, id);
	if (session->cmds[*id] && session->cmds[*id - 1]->type == OR)
		run_or(session, id);
	session->status_last = session->cmds[*id - 1]->status;
	// //////////////////////////////////////////////////////////////
	// *id = 0;
	// while (session->cmds[*id])
	// {
	// 	printf("STATUS OF COMMAND [%d] is: %d\n", *id, session->cmds[*id]->status);
	// 	(*id)++;
	// }
	// /////////////////////////////////////////////////////////
	// printf("STATUS OF LAST COMMAND [%d] is: %d\n", *id - 1, session->status_last);
}


// DEAD
// env | sort | grep -v SHLVL | grep -v ^_ 

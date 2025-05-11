/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:23:26 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/11 14:58:36 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child_files(t_session *session, int *id)
{
	int	status;

	if (open_files(session->cmds[*id]) < 0)
	{
		status = session->cmds[*id]->status;
		group_free(session);
		exit(status);
	}
	if (handle_in_out(session->cmds[*id]) < 0)
	{
		group_free(session);
		error_msg(ERR_BASH, "dup2 failed", NULL, NULL);
		exit (1);
	}
}

static void	child(t_session *session, int *id, int runs, int num)
{
	setup_signals(2);
	if (session->prev_fd != -1)
	{
		if (dup2(session->prev_fd, STDIN_FILENO) < 0)
		{
			group_free(session);
			error_msg(ERR_BASH, "dup2 failed", NULL, NULL);
			exit (1);
		}
		close(session->prev_fd);
	}
	if (runs < num - 1)
	{
		if (dup2(session->pipefd[1], STDOUT_FILENO) < 0)
		{
			group_free(session);
			error_msg(ERR_BASH, "dup2 failed", NULL, NULL);
			exit (1);
		}
	}
	close(session->pipefd[0]);
	close(session->pipefd[1]);
	child_files(session, id);
	run_cmd(session, session->cmds[*id]);
	exit(1);
}

static void	parent(t_session *session)
{
	if (session->prev_fd != -1)
		close(session->prev_fd);
	close(session->pipefd[1]);
	session->prev_fd = session->pipefd[0];
}

static void	status_wait(t_session *session, int runs)
{
	int		status;
	int		pid;
	int		i;
	int		j;
	t_flags	flags;

	i = 0;
	flags.sigint_printed = 0;
	flags.sigquit_printed = 0;
	while (i < runs)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			j = -1;
			while (++j < session->count->cmd_nb)
			{
				if (pid == session->cmds[j]->pid)
					session->cmds[j]->status = WEXITSTATUS(status);
			}
		}
		else if (WIFSIGNALED(status))
			handle_signal_status(session, pid, status, &flags);
		i++;
	}
}

void	run_pipe(t_session *session, int *id)
{
	int	runs;
	int	num;

	runs = 0;
	num = num_pipes(session, id) + 1;
	session->prev_fd = -1;
	while (runs < num)
	{
		if (runs < num && pipe(session->pipefd) == -1)
			return ((*id)++, error_msg(ERR_BASH, ERR_PIPE, NULL, NULL));
		session->cmds[*id]->pid = fork();
		if (session->cmds[*id]->pid == -1)
			return ((*id)++, error_msg(ERR_BASH, ERR_FORK, NULL, NULL));
		if (session->cmds[*id]->pid == 0)
			child(session, id, runs, num);
		parent(session);
		runs++;
		(*id)++;
	}
	close(session->pipefd[0]);
	close(session->pipefd[1]);
	signal(SIGINT, SIG_IGN);
	status_wait(session, runs);
	signal(SIGINT, handle_sigint);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:23:26 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/12 12:11:02 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_session *session, int *id, int runs)
{
	handle_in_out(session->cmds[*id]);
	if (session->prev_fd != -1) // NOT FIRST PIPE
	{
		dup2(session->prev_fd, STDIN_FILENO);
		close(session->prev_fd);
	}
	if (runs < session->count->cmd_nb - 1) // IF NOT LAST
	{
		close(session->pipefd[0]);
		dup2(session->pipefd[1], STDOUT_FILENO); // WRITE TO PIPE
		close(session->pipefd[1]);
	}
	run_cmd(session, session->cmds[*id]);
	exit(1);
}

static void	parent(t_session *session, int *id, int runs)
{
	if (session->prev_fd != -1) // close previous read
		close(session->prev_fd);
	if (runs < session->count->cmd_nb - 1) // IF NOT LAST
	{
		close(session->pipefd[1]);
		session->prev_fd = session->pipefd[0]; // save current read end for next child
	}
}

static void	status_wait(t_session *session, int runs)
{
	int		status;
	int		pid;
	int		j;
	int		i;

	i = 0;
	while (i < runs)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
		{
			j = 0;
			while (j < session->count->cmd_nb)
			{
				if (pid == session->cmds[j]->pid)
					session->cmds[j]->status = status;
				j++;
			}
		}
		i++;
	}
}

void	run_pipe(t_session *session, int *id)
{
	int		runs;

	runs = 0;
	session->prev_fd = -1;
	while (runs < session->count->cmd_nb && (session->cmds[*id]->type == PIPE \
			|| session->cmds[*id]->type == NONE))
	{
		if (open_files(session, session->cmds[*id], *id) < 0)
			return ((*id)++, error_msg("open_files failed", NULL, NULL, NULL));
		if (runs < session->count->cmd_nb - 1 && pipe(session->pipefd) == -1) // NOT FOR LAST
			return ((*id)++, error_msg("pipe failed", NULL, NULL, NULL));
		session->cmds[*id]->pid = fork();
		if (session->cmds[*id]->pid == -1)
			return ((*id)++, error_msg("fork failed", NULL, NULL, NULL));
		if (session->cmds[*id]->pid == 0)
			child(session, id, runs);
		parent(session, id, runs);
		runs++;
		(*id)++;
	}
	status_wait(session, runs);
}

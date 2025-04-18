/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 10:23:26 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/16 14:22:13 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	child(t_session *session, int *id, int runs, int num)
{
	setup_signals(2);
	if (session->prev_fd != -1) // NOT FIRST PIPE
	{
		dup2(session->prev_fd, STDIN_FILENO); // IN FILE FROM PREVIOUS PIPE /// HANDLE REDIRECTIONS HERE
		close(session->prev_fd);
	}
	if (runs < num - 1) // IF NOT LAST
	{
		close(session->pipefd[0]);
		dup2(session->pipefd[1], STDOUT_FILENO); // OUT WRITE TO THE NEXT PIPE /// HANDLE REDIRECTIONS HERE
		close(session->pipefd[1]);
	}
	if (open_files(session, session->cmds[*id], *id) < 0)
	{
		ft_lstclear(&session->env_var, free);
		free_session(session);
		rl_clear_history();
		exit(1);
	}
	handle_in_out(session->cmds[*id]);
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

static void	handle_exit_status(t_session *session, int pid, int status)
{
	int j = 0;

	while (j < session->count->cmd_nb)
	{
		if (pid == session->cmds[j]->pid)
			session->cmds[j]->status = WEXITSTATUS(status);
		j++;
	}
}

static void	status_wait(t_session *session, int runs)
{
	int	status;
	int	pid;
	int	i = 0;
	int	sigint_printed = 0;
	int	sigquit_printed = 0;

	while (i < runs)
	{
		pid = waitpid(-1, &status, 0);
		if (WIFEXITED(status))
			handle_exit_status(session, pid, status);
		else if (WIFSIGNALED(status))
			handle_signal_status(session, pid, status, &sigint_printed, &sigquit_printed);
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
		if (runs < num && pipe(session->pipefd) == -1) // NOT FOR LAST
			return ((*id)++, error_msg(ERR_BASH, ERR_PIPE, NULL, NULL));
		session->cmds[*id]->pid = fork();
		if (session->cmds[*id]->pid == -1)
			return ((*id)++, error_msg(ERR_BASH, ERR_FORK, NULL, NULL));
		if (session->cmds[*id]->pid == 0)
			child(session, id, runs, num);
		parent(session, id, runs);
		runs++;
		(*id)++;
	}
	signal(SIGINT, SIG_IGN); 
	status_wait(session, runs);
	signal(SIGINT, handle_sigint);
}

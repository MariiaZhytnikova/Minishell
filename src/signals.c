/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:01:37 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/14 15:13:54 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t signalnum;

void	exit_signal(t_session *session, int code)
{
	ft_lstclear(&session->env_var, free);
	free(session->history_pipe);
	rl_clear_history();
	printf("exit\n");
	exit(code);
}

void	handle_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void heredoc_handle_sigint(int signo)
{
	if (signo == SIGINT) 
	{
		signalnum = 2;
		printf("\n");
		close(STDIN_FILENO);
	}
}

void	setup_signals(int mode)
{
	if (mode == 0)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 1)
	{
		signal(SIGINT, heredoc_handle_sigint);
		signal(SIGQUIT, SIG_IGN);
	}
	if (mode == 2)
	{
		signal(SIGINT, handle_sigint);
		signal(SIGQUIT, SIG_DFL);
	}
}

void	handle_signal_status(t_session *s, int pid, int status, int *si, int *sq)
{
	int sig;
	int j;

	sig = WTERMSIG(status);
	j = 0;
	if (sig == SIGINT && !(*si))
	{
		write(1, "\n", 1);
		*si = 1;
	}
	if (sig == SIGQUIT && !(*sq))
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
		*sq = 1;
	}
	while (j < s->count->cmd_nb)
	{
		if (pid == s->cmds[j]->pid)
			s->cmds[j]->status = 128 + sig;
		j++;
	}
}

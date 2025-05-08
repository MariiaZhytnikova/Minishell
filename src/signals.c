/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:01:37 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/08 19:31:50 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

sig_atomic_t	g_signalnum;

void	handle_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint_after(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	heredoc_handle_sigint(int signo)
{
	if (signo == SIGINT)
	{
		g_signalnum = 2;
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
	if (mode == 3)
	{
		signal(SIGINT, handle_sigint_after);
		signal(SIGQUIT, SIG_IGN);
	}
}

void	handle_signal_status(t_session *s, int pid, int status, t_flags *flags)
{
	int	sig;
	int	j;

	sig = WTERMSIG(status);
	j = 0;
	if (sig == SIGINT && !(flags->sigint_printed))
	{
		write(1, "\n", 1);
		flags->sigint_printed = 1;
	}
	else if (sig == SIGQUIT && !(flags->sigquit_printed))
	{
		write(STDERR_FILENO, "Quit (core dumped)\n", 20);
		flags->sigquit_printed = 1;
	}
	while (j < s->count->cmd_nb)
	{
		if (pid == s->cmds[j]->pid)
			s->cmds[j]->status = 128 + sig;
		j++;
	}
}

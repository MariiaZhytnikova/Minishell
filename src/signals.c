/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 18:01:37 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/14 13:28:40 by ekashirs         ###   ########.fr       */
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

static void	handle_sigint(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}
void	setup_signals()
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, SIG_IGN);
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

void	setup_heredoc_signals() 
{
	signal(SIGINT, heredoc_handle_sigint);
	signal(SIGQUIT, SIG_IGN);
}
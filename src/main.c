/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/08 19:21:28 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_signal(t_session *session, int code)
{
	ft_lstclear(&session->env_var, free);
	free(session->history_pipe);
	rl_clear_history();
	//printf("exit\n");
	exit(code);
}

static int	init_session(int argc, char **argv, char **env, t_session *session)
{
	(void)argv;
	if (argc != 1)
	{
		error_msg(ERR_USAGE, NULL, NULL, NULL);
		return (1);
	}
	session->env_var = NULL;
	session->status_last = 0;
	if (create_env_list(&session->env_var, env))
		return (1);
	return (0);
}

static void	process_input(t_session *session)
{
	int	status;
	int	id;

	status = lexical_analyzer(session);
	if (status != 1)
	{
		if (status == 4)
		{
			ft_lstclear(&session->env_var, free);
			free_session(session);
			rl_clear_history();
			//printf("exit\n");
			exit(2);
		}
		history(session);
		free_session(session);
		return ;
	}
	if (history(session) < 0)
		return ;
	id = 0;
	exec(session, &id);
	free_session(session);
}

int	main(int argc, char **argv, char **env)
{
	t_session	session;

	if (init_session(argc, argv, env, &session) != 0)
		return (1);
	while (1)
	{
		session.input = NULL;
		session.cmds = NULL;
		session.count = NULL;
		session.history_pipe = NULL;
		if (g_signalnum == 3)
			setup_signals(3);
		else
			setup_signals(0);
		g_signalnum = 0;
		if (prompt(&session) < 0)
			exit_signal(&session, session.status_last);
		if (session.input[0] == '\0')
		{
			free_session(&session);
			continue ;
		}
		process_input(&session);
	}
	return (session.status_last);
}

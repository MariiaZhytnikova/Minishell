/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/16 13:31:53 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	create_env_list(&session->env_var, env);
	if (!session->env_var)
		return (1);
	return (0);
}

static void	process_input(t_session *session)
{
	int status;
	int id;

	status = lexical_analyzer(session);
	if (status != 1)
	{
		if (status == 4)
			{	
				ft_lstclear(&session->env_var, free);
				free_session(session);
				rl_clear_history();
				printf("exit\n");
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
		setup_signals(0);
		signalnum = 0;
		if (prompt(&session) < 0)
			exit_signal(&session, 0);
		if (session.input[0] == '\0')
		{
			free_session(&session);
			continue ;
		}
		process_input(&session);
	}
	return (0);
}

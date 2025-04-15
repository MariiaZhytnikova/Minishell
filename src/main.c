/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/14 14:53:17 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env)
{
	t_session	session;
	int status;

	(void)argv;
	if (argc != 1)
		return (error_msg(ERR_USAGE, NULL, NULL, NULL), 1);
	session.env_var = NULL;
	session.status_last = 0;
	create_env_list(&session.env_var, env);
	while (1)
	{
		session.input = NULL;
		session.cmds = NULL;
		session.count = NULL;
		session.history_pipe = NULL;
		setup_signals(0);
		signalnum = 0;
		if(prompt(&session) < 0)
			exit_signal(&session, 0);
		if (session.input[0] == '\0')
		{
			free_session(&session);
			continue ;
		}
		// printf("%s%s%s\n", RED, session.input, RESET);
		status = lexical_analyzer(&session);
		if (status != 1)
		{
			if (status == 4)
			{
				ft_lstclear(&session.env_var, free);
				free_session(&session);
				rl_clear_history();
				printf("exit\n");
				exit(2);
			}
			history(&session);
			free_session(&session);
			continue ;
		}
		if (history(&session) < 0)
			continue ;
		int	id = 0;
		exec(&session, &id);
		free_session(&session);
	}
	return (0);
}

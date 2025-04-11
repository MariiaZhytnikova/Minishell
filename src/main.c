/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/11 18:26:26 by ekashirs         ###   ########.fr       */
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
	setup_signals();
	while (1)
	{
		session.input = NULL;
		session.cmds = NULL;
		session.count = NULL;
		session.history_pipe = NULL;
		signalnum = 0;
		if(prompt(&session) < 0)
			exit_signal(&session, 130);
		if (session.input[0] == '\0')
			continue ;
		printf("%s%s%s\n", RED, session.input, RESET);
		status = lexical_analyzer(&session);
		if (status != 1)
		{
			if (signalnum == 2 || status == 3 || status == -1)
			{
				history(&session);
				free_session(&session);
				continue ;
			}
			if (status == 4)
			{
				ft_lstclear(&session.env_var, free);
				free_session(&session);
				rl_clear_history();
				printf("exit\n");
				exit(2);
			}
			history(&session);
			continue ;
		}
		if (history(&session) < 0)
			continue ;
		if (exec(&session) < 0)
			printf("Oh no....\n");
		free_session(&session);
	}
	return (0);
}

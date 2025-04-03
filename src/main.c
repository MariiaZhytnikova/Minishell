/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/03 19:19:41 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env) 
{
	t_session	session;
	
	(void)argv;
	if (argc != 1)
		return (error_msg(ERR_USAGE, NULL, NULL, NULL), 1);
	session.env_var = NULL;
	create_env_list(&session.env_var, env);
	setup_signals();
	while (1)
	{
		if(prompt(&session) < 0)
		{
			ft_lstclear(&session.env_var, free);
			rl_clear_history();
			printf(" exit\n");
			exit(0);
			// bash-3.2$ cat | ^D
			//> bash: syntax error: unexpected end of file
		}
		if (session.input[0] == '\0')
			continue ;
		printf("%s%s%s\n", RED, session.input, RESET);
		if (lexical_analyzer(&session) < 0)
		{
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

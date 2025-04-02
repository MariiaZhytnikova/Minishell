/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/02 15:19:29 by ekashirs         ###   ########.fr       */
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
	while (1)
	{
		if(prompt(&session) < 0)
		{
			if (session.input)
				free(session.input);
			error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL);
			continue ;
		}
		if (!session.input || *session.input == '\0')
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

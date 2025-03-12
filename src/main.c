/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/10 15:01:44 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env) 
{
	t_session	session;
	
	(void)env;
	(void)argv;
	if (argc != 1)
		return (error_msg(USAGE), 1);
	while (1)
	{
		promt(&session);
		printf("%s%s%s\n", RED, session.input, RESET);
		// lexical_analyzer(&session); // I'm create tokens
		//parse_tokens(tokens);
		free(session.input);
	}
	return (0);
}

	//char *path = getenv("PATH");
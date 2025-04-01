/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/31 18:34:22 by ekashirs         ###   ########.fr       */
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
		printf("%s%s%s\n", RED, session.input, RESET);
		if (session.input && *session.input)
			if (lexical_analyzer(&session) > 0)
				if (exec(&session) < 0)
					continue ;
	}
	ft_lstclear(&session.env_var, free);
	return (0);
}

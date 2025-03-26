/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/26 16:26:17 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env) 
{
	t_session	session;
	
	(void)argv;
	if (argc != 1)
		return (error_msg(ERR_USAGE, NULL, NULL, NULL), 1);
	create_env_list(&session.env_var, env);
	while (1)
	{
		promt(&session);
		printf("%s%s%s\n", RED, session.input, RESET);
		if (session.input && *session.input)
			if (lexical_analyzer(&session) > 0)
				if (exec(&session) < 0)
					continue ;
	}
	ft_lstclear(&session.env_var, free);
	return (0);
}


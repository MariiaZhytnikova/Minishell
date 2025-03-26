/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/26 13:22:54 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **env) 
{
	t_session	session;
	
	//(void)env;
	//(void)argv;
	//if (argc != 1)
		//return (error_msg(ERR_USAGE, NULL, NULL), 1);
	//while (1)
	//{
		//promt(&session);
		//printf("%s%s%s\n", RED, session.input, RESET);
	session = ft_calloc(1, sizeof(t_session));
	command = ft_calloc(1, sizeof(t_command));
	command->args = malloc(sizeof(char *) * 10);
	create_env_list(&session->env_var, env);
	command->command = argv[1];
	command->args[0] = argv[2];
	command->args[1] = argv[3];
	command->args[2] = argv[4];
	if (!strcmp(command->command, "exit"))
		exit_builtin(session, command);
	else if (!strcmp(command->command,"cd"))
		cd_builtin(session, command);
	else if (!strcmp(command->command, "env"))
		env_builtin(session, command);
	else if (!strcmp(command->command, "pwd"))
		pwd_builtin(command);
	else if (!strcmp(command->command, "unset"))
		unset_builtin(session, command);
	else if (!strcmp(command->command, "echo"))
		echo_builtin(command);
	else if (!strcmp(command->command, "export"))
		export_builtin(session , command);
		//lexical_analyzer(&session); // I'm create tokens
		//parse_tokens(tokens);
		//free(session.input);
	return (0);
}

	//char *path = getenv("PATH");

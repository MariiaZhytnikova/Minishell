/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:17:41 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/07 16:47:34 by ekashirs         ###   ########.fr       */
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
		signalnum = 0;
		if(prompt(&session) < 0)
			exit_signal(&session, 0);
		if (session.input[0] == '\0')
			continue ;
		printf("%s%s%s\n", RED, session.input, RESET);
		if (lexical_analyzer(&session) < 0)
		{
			if (signalnum == 2)
			{
				free(session.history_pipe);
				continue ;
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


// CHECK THIS:

// /home/ekashirs/projects/Hive/Minishell$ << lim
// << lim
// > 
// > 
// ==1023606== Invalid write of size 1
// ==1023606==    at 0x407EB7: ft_strlcat (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x404897: here_doc_lim_inp (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x40470D: here_doc_lim (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x403380: split_and_check (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x403467: lexical_analyzer (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x40133B: main (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==  Address 0x4b62fc1 is 0 bytes after a block of size 1 alloc'd
// ==1023606==    at 0x4848899: malloc (in /usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
// ==1023606==    by 0x40793C: ft_calloc (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x40707D: reall (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x4048A8: here_doc_lim_inp (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x40470D: here_doc_lim (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x403380: split_and_check (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x403467: lexical_analyzer (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606==    by 0x40133B: main (in /home/ekashirs/projects/Hive/Minishell/minishell)
// ==1023606== 


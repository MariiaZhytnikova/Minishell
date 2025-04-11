/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:49 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/11 13:53:23 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*create_prompt(void)
{
	char	cwd[1024];
	char	*prompt;
	char	*temp;

	prompt = NULL;
	if (getcwd(cwd, sizeof(cwd)) != NULL)
	{
		temp = ft_strjoin("\001" CYAN BOLD "\002", cwd); // CHECK EVERYTHING
		prompt = ft_strjoin(temp, "\001" CYAN BOLD "\002$ \001" RESET "\002"); // CHECK EVERYTHING
		free(temp);
	}
	else
		return (ft_strdup(PROMPT)); // CHECK EVERYTHING
	return (prompt);
}

int	prompt(t_session *session)
{
	char	*promt;

	session->history_pipe = ft_calloc(1, sizeof(char *));
	if (!session->history_pipe)
		return (-1); // ERROR MSG
	promt = create_prompt();
	
	session->input = readline(promt);
	free(promt);
	if (!session->input || !*session->input)
		return (-1);
	return (1);
}


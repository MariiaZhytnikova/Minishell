/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:49 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/12 15:01:06 by ekashirs         ###   ########.fr       */
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
		temp = ft_strjoin("\001" CYAN BOLD "\002", cwd);
		if (!temp)
			return (NULL);
		prompt = ft_strjoin(temp, "\001" CYAN BOLD "\002$ \001" RESET "\002");
		free(temp);
		if (!prompt)
			return (NULL);
	}
	else
		return (ft_strdup(PROMPT));
	return (prompt);
}

int	prompt(t_session *session)
{
	char	*prompt;

	session->history_pipe = ft_calloc(1, sizeof(char *));
	if (!session->history_pipe)
		return (-1);
	if (search_in_env(session->env_var, "TERM") == NULL)
	{
		prompt = ft_strdup(PROMPT);
		if (!prompt)
			return (-1);
	}
	else
		prompt = create_prompt();
	if (!prompt)
		return (-1);
	session->input = readline(prompt);
	free(prompt);
	if (!session->input)
		return (-1);
	return (1);
}

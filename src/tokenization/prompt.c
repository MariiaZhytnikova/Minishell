/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:49 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/23 17:13:29 by mzhitnik         ###   ########.fr       */
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
		if (!prompt)
		{
			free(temp);
			return (NULL);
		}
		free(temp);
	}
	else
		return (ft_strdup(PROMPT));
	return (prompt);
}

// int	prompt(t_session *session)
// {
// 	char	*promt;

// 	session->history_pipe = ft_calloc(1, sizeof(char *));
// 	if (!session->history_pipe)
// 		return (-1);
// 	promt = create_prompt();
// 	if (!promt)
// 		return (-1);
// 	session->input = readline(promt);
// 	free(promt);
// 	if (!session->input)
// 		return (-1);
// 	return (1);
// }


int    prompt(t_session *session)
{
    char    *promt;
    char    *line;

    session->history_pipe = ft_calloc(1, sizeof(char *));
    if (!session->history_pipe)
        return (-1);

    if (isatty(fileno(stdin)))
    {
        // Interactive mode
        promt = create_prompt();
        if (!promt)
            return (-1);
        session->input = readline(promt);
        free(promt);
        if (!session->input)
            return (-1);
    }
    else
    {
        // Non-interactive mode (e.g. tester)
        line = get_next_line(fileno(stdin));
        if (!line)
            return (-1);
        session->input = ft_strtrim(line, "\n");
        free(line);
        if (!session->input)
            return (-1);
    }

    return (1);
}
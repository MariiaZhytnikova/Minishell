/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 15:05:01 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/04 13:31:35 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_pipe_history(t_session *session, char *line)
{
	char	*temp;

	if (session->history_pipe)
	{
		temp = ft_strjoin(session->history_pipe, " ");
		if (!temp)
			return (-1);
		free(session->history_pipe);
	}
	else
	{
		temp = ft_calloc(1, sizeof(char *));
		if (!temp)
			return (-1);
	}
	session->history_pipe = ft_strjoin(temp, line);
	free(temp);
	if (!session->history_pipe)
		return (-1);
	return (0);
}

static int	is_unfinished(char *input)
{
	int	i;

	i = ft_strlen(input) - 1;
	while (i >= 0 && (input[i] == ' '))
		i--;
	if (i >= 0 && (input[i] == '|' || (input[i] == '|' && input[i - 1] == '|')
			|| (input[i] == '&' && input[i - 1] == '&')))
		return (1);
	return (0);
}

static int	read_multiline_input(t_session *session)
{
	char	*new_line;
	char	*temp;

	if (session->input && is_unfinished(session->input))
	{
		temp = ft_strjoin(session->input, session->history_pipe);
		free(session->input);
		session->input = temp;
		if (!session->input)
			return (-1);
	}
	return (0);
}

int	history(t_session *session)
{
	int		status;
	char	*clean_command;

	status = read_multiline_input(session);
	if (status < 0)
		return (-1);
	clean_command = ft_strtrim(session->input, "\n");
	if (clean_command && *clean_command)
	{
		add_history(clean_command);
		free(clean_command);
		return (0);
	}
	else
	{
		free(clean_command);
		return (-1);
	}
}

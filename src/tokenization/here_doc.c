/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:33:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/11 14:40:31 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc_process(char **line, int stdin)
{
	*line = readline("> ");
	while (1)
	{
		if (!*line && g_signalnum == 2)
		{
			if (dup2(stdin, STDIN_FILENO) == -1)
				return (-1);
			return (2);
		}
		if (!*line)
			return (4);
		if ((*line)[0])
			break ;
		else
		{
			// char *temp = ft_strdup(*line);
			// free(*line);
			// *line = temp;
			free(*line);
			*line = readline("> ");
			// char *temp2 = ft_strdup(*line);
			// free(*line);
			// *line = temp2;
		}
	}
	return (0);
}

static int	here_doc_inp(t_session *session, t_list **token)
{
	char	*line;
	int		stdin_copy;
	int		status;

	setup_signals(1);
	line = NULL;
	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1)
		return (-1);
	status = here_doc_process(&line, stdin_copy);
	close (stdin_copy);
	if (status != 0)
		return (status);
	if (add_pipe_history(session, line) < 0)
		return (-1);
	if (split_and_check(session, token, line) < 0)
		return (-1);
	return (1);
}

int	here_doc_no_lim(t_session *session, t_list **token)
{
	t_list	*last;
	int		status;

	last = ft_lstlast(*token);
	status = 0;
	if ((ft_strncmp(last->content, "|", longer(last->content, "|")) == 0)
		|| (ft_strncmp(last->content, "||", longer(last->content, "||")) == 0)
		|| (ft_strncmp(last->content, "&&", longer(last->content, "&&")) == 0))
	{
		status = here_doc_inp(session, token);
		if (status == 4)
		{
			error_msg(ERR_BASH, ERR_SYNT_END, NULL, NULL);
			return (4);
		}
		if (status != 0)
			return (status);
	}
	return (1);
}

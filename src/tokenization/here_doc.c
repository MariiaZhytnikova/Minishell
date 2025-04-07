/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:33:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/07 17:04:55 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int here_doc_inp(t_session *session, t_list **token)
{
	char *line;
	char *input;
	int stdin_copy;

	setup_heredoc_signals();

	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1) 
	{
		perror("dup");
		return (-1);
	}
	line = readline("> ");
	while (1)
	{
		if (!line && signalnum == 2)
		{
			if (dup2(stdin_copy, STDIN_FILENO) == -1) 
				perror("dup2");
			close(stdin_copy);
			return (2);
		}
		if (!line)
			return (3);
		if (line[0])
			break;
		else
		{
			free(line);
			line = readline("> ");
		}
	}
	if (add_pipe_history(session, line) < 0)
		return (-1);
	if (split_and_check(session, token, line) < 0)
		return (-1);
	return (1);
}

static int replace_token(t_session *session, t_list *current, char *buffer)
{
	t_list *new_token;

	free(current->content);
	current->content = ft_strdup("<<<");
	if (!current->content)
		return (-1);
	free(current->next->content);
	if (!buffer || !buffer[0])
		buffer = ft_calloc(1, sizeof(char));
	if (!buffer)
		return (-1);
	if (ft_strchr(buffer, '$'))
		if (expansion_two(session, &buffer) < 0)
			return (-1);
	current->next->content = buffer;
	return (1);
}

static int here_doc_lim_inp(t_session *session, t_list *current)
{
	char *line;
	char *buffer;
	int new_size;
	int old_size;
	int stdin_copy;

	new_size = 0;
	old_size = 0;
	buffer = NULL;
	setup_heredoc_signals();
	stdin_copy = dup(STDIN_FILENO);
	while (1)
	{		
		line = readline("> ");
		if (!line && signalnum == 2)
		{
			if (dup2(stdin_copy, STDIN_FILENO) == -1) 
				perror("dup2");
			close(stdin_copy);
			return (2);
		}
		if (!line)
		{
			close(stdin_copy);
			return (3);
		}
		if ((line && *line) && ft_strncmp(line, current->next->content,
								longer(line, current->next->content)) == 0)
			break;
		new_size = old_size + ft_strlen(line) + 1;
		if (buffer)
			ft_strlcat(buffer, "\n", new_size);
		buffer = reall(buffer, old_size, new_size);
		if (!buffer)
			return (error_msg("Something wrong with realloc here_doc_lim_inp", NULL, NULL, NULL), -1);
		ft_strlcat(buffer, line, new_size);
		old_size = new_size;
		free(line);
	}
	return (replace_token(session, current, buffer));
}

int here_doc_no_lim(t_session *session, t_list **token)
{
	t_list *last;
	int status;

	last = ft_lstlast(*token);
	status = 0;
	if ((ft_strncmp(last->content, "|", longer(last->content, "|")) == 0) || (ft_strncmp(last->content, "||", longer(last->content, "||")) == 0) || (ft_strncmp(last->content, "&&", longer(last->content, "&&")) == 0))
	{
		status = here_doc_inp(session, token);
		if (status == -1)
			return (-1);
		if (status == 2)
			return (5); // ??
		if (status == 3)
		{
			ft_lstclear(token, free);
			error_msg(ERR_BASH, ERR_SYNT_END, NULL, NULL);
			exit_signal(session, 2);
		}
	}
	return (1);
}

int here_doc_lim(t_session *session, t_list **token)
{
	t_list *curr;
	int status;

	status = 0;
	curr = *token;
	while (curr->next)
	{
		if (ft_strncmp(curr->content, "<<", longer(curr->content, "<<")) == 0)
		{
			status = here_doc_lim_inp(session, curr);
			if (status < 0)
				return (-1);
			if (status == 2)
				return (2);
			if (status == 3)
			{
				error_msg(ERR_BASH, ERR_EOF_HEREDOC, NULL, NULL);
				return (-1);
			}
			curr = curr->next;
		}
		if (curr->next)
			curr = curr->next;
	}
	return (1);
}

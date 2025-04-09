/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_lim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:19:27 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/08 18:24:40 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_token(t_session *session, t_list *current, char *buffer)
{
	t_list	*new_token;

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

static int	handle_line_input(char **buffer, int *old_size, char *line)
{
	int	new_size;

	new_size = *old_size + ft_strlen(line) + 1;
	if (*buffer)
		ft_strlcat(*buffer, "\n", new_size);
	*buffer = reall(*buffer, *old_size, new_size);
	if (!*buffer)
		return (error_msg("Something wrong with realloc here_doc_lim_inp", NULL, NULL, NULL), -1);
	ft_strlcat(*buffer, line, new_size);
	*old_size = new_size;
	return (0);
}

static int	here_doc_lim_inp_process(t_list *current, int stdin_copy, char *line, char *buffer)
{
	int	old_size;

	old_size = 0;
	while (1)
	{
		line = readline("> ");
		if (!line && signalnum == 2)
		{
			if (dup2(stdin_copy, STDIN_FILENO) == -1)
				error_msg(ERR_DUP, NULL, NULL, NULL);
			return (2);
		}
		if (!line)
			return (3);
		if ((line && *line) && ft_strncmp(line, current->next->content,
				longer(line, current->next->content)) == 0)
			break;
		if (handle_line_input(&buffer, &old_size, line) < 0)
			return (-1);
		free(line);
	}
	return (0);
}

static int	here_doc_lim_inp(t_session *session, t_list *current)
{
	char	*line;
	char	*buffer;
	int		stdin_copy;
	int		status;

	buffer = NULL;
	line = NULL;
	setup_heredoc_signals();
	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1)
	{
		error_msg(ERR_DUP, NULL, NULL, NULL);
		return (-1);
	}
	status = here_doc_lim_inp_process(current, stdin_copy, line, buffer);
	return (replace_token(session, current, buffer));
	// free(buffer); ????????????????
}

int	here_doc_lim(t_session *session, t_list **token)
{
	t_list	*curr;
	int		status;

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

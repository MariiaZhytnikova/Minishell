/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_lim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:19:27 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/25 15:25:46 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_token(t_session *session, t_list *current, char *buffer)
{

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
	{
		if (expansion_two(session, &buffer) < 0)
			return (-1);
	}
	current->next->content = ft_strdup(buffer);
	free(buffer);
	return (1);
}

static int	handle_line_input(char **buffer, int *old_size, char *line)
{
	int	new_size;

	new_size = *old_size + ft_strlen(line) + 2;
	if (*buffer)
		ft_strlcat(*buffer, "\n", new_size);
	*buffer = reall(*buffer, *old_size, new_size);
	if (!*buffer)
		return (-1);
	ft_strlcat(*buffer, line, new_size);
	*old_size = new_size;
	return (0);
}

static int	here_doc_lim_process(t_list *cur, int stdin, char *line, char **buf)
{
	int	old_size;

	old_size = 0;
	while (1)
	{
		line = readline("> ");
		if (!line && g_signalnum == 2)
		{
			if (dup2(stdin, STDIN_FILENO) == -1)
				return (-1);
			return (2);
		}
		if (!line)
			return (4);
		if ((line && *line) && ft_strncmp(line, cur->next->content,
				longer(line, cur->next->content)) == 0)
			break ;
		if (handle_line_input(buf, &old_size, line) < 0)
			return (-1);
		free(line);
	}
	if (buf && *buf && **buf)
		ft_strlcat(*buf, "\n", ft_strlen(*buf) + 2);
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
	setup_signals(1);
	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1)
	{
		close(stdin_copy);
		return (-1);
	}
	status = here_doc_lim_process(current, stdin_copy, line, &buffer);
	close(stdin_copy);
	if (status != 0)
	{
		free(buffer);
		return (status);
	}
	if (buffer && ft_strlen(buffer) > 65715)
		return (error_msg(ERR_BUF, NULL, NULL, NULL), 4);
	return (replace_token(session, current, buffer));
}

int	here_doc_lim(t_session *session, t_list **token)
{
	t_list	*curr;
	int		status;

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
			if (status == 4)
			{
				error_msg(ERR_BASH, ERR_EOF_HEREDOC, NULL, NULL);
				return (4);
			}
			curr = curr->next;
		}
		if (curr->next)
			curr = curr->next;
	}
	return (1);
}

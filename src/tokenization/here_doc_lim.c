/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_lim.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:19:27 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/11 16:29:16 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	handle_line_input(char **buffer, char *line)
{
	int	new_size;
	int	old_size;

	if (!*buffer || !*buffer[0])
		old_size = 0;
	else
		old_size = ft_strlen(*buffer);
	new_size = old_size + ft_strlen(line) + 2;
	*buffer = reall(*buffer, old_size, new_size);
	if (!*buffer)
		return (-1);
	ft_strlcat(*buffer, line, new_size);
	old_size = new_size;
	free(line);
	return (0);
}

static int	limiter(t_list *cur, char **lim)
{
	char	*temp;

	temp = skip(cur->next->content);
	if (!temp)
		return (-1);
	*lim = ft_strjoin(temp, "\n");
	free(temp);
	if (!*lim)
		return (-1);
	return (1);
}

static int	here_doc_lim_process(int stdin, char **buf, char **lim)
{
	char	*line;
	char	*temp;

	while (1)
	{
		line = readline("> ");
		if (!line && g_signalnum == 2)
		{
			if (dup2(stdin, STDIN_FILENO) == -1)
				return (free(*lim), -1);
			return (free(*lim), 2);
		}
		if (!line)
			return (free(*lim), 3);
		temp = ft_strjoin(line, "\n");
		free(line);
		if (!temp)
			return (free(*lim), -1);
		if (ft_strncmp(temp, *lim, longer(temp, *lim)) == 0)
			return (free(temp), free(*lim), 0);
		if (handle_line_input(buf, temp) < 0)
			return (free(*lim), free(temp), -1);
	}
	return (0);
}

static int	here_doc_lim_inp(t_list *current)
{
	char	*buffer;
	int		stdin_copy;
	int		status;
	char	*lim;

	buffer = NULL;
	if (limiter(current, &lim) < 0)
		return (-1);
	setup_signals(1);
	stdin_copy = dup(STDIN_FILENO);
	if (stdin_copy == -1)
	{
		close(stdin_copy);
		return (-1);
	}
	status = here_doc_lim_process(stdin_copy, &buffer, &lim);
	close(stdin_copy);
	if (status != 0)
	{
		free(buffer);
		return (status);
	}
	if (buffer && ft_strlen(buffer) > 65715)
		return (error_msg(ERR_BUF, NULL, NULL, NULL), 4);
	return (replace_token(current, buffer));
}

int	here_doc_lim(t_list **token) // Ctrl D do the same as lim but with message bash: warning: here-document at line 13 delimited by end-of-file
{
	t_list	*curr;
	int		status;

	curr = *token;
	while (curr->next)
	{
		if (ft_strncmp(curr->content, "<<", longer(curr->content, "<<")) == 0)
		{
			status = here_doc_lim_inp(curr);
			if (status < 0 || status == 2)
				return (status);
			if (status == 3)
			{
				error_msg(ERR_BASH, ERR_EOF_HEREDOC, NULL, NULL);
				g_signalnum = 3;
			}
			curr = curr->next;
		}
		if (curr->next)
			curr = curr->next;
	}
	if (g_signalnum == 3)
		return (3);
	return (1);
}

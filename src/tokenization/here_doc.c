/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 10:33:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/26 13:47:59 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	here_doc_inp(t_list **token)
{
	char	*line;
	char	*input;

	line = readline("> ");
	while (1)
	{
		if (line[0])
			break ;
		else
		{
			free (line);
			line = readline("> ");
		}
	}
	if (split_and_check(token, line) < 0)
		return (-1);
	return (1);
}

static int	replace_token(t_list **token, t_list *current, char *buffer)
{
	t_list	*new_token;

	free(current->content);
	current->content = ft_strdup("<<<");
	if (!current->content)
		return (-1);
	free(current->next->content);
	if (!buffer || !buffer[0])
		buffer = ft_calloc(1, sizeof(char));
	current->next->content = buffer;
	return (1);
}

static int	here_doc_lim_inp(t_list **token, t_list *current)
{
	char	*line;
	char	*buffer;
	int		new_size;
	int		old_size;

	new_size = 0;
	old_size = 0;
	buffer = NULL;
	while (1)
	{
		line = readline("> ");
		if ((line && *line) && ft_strncmp(line, current->next->content, \
			longer(line, current->next->content)) == 0)
			break ;
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
	return (replace_token(token, current, buffer));
}

int	here_doc_no_lim(t_list **token)
{
	t_list	*last;

	last = ft_lstlast(*token);
	if ((ft_strncmp(last->content, "|", longer(last->content, "|")) == 0)
		|| (ft_strncmp(last->content, "||", longer(last->content, "||")) == 0)
		|| (ft_strncmp(last->content, "&&", longer(last->content, "&&")) == 0))
	{
		if (here_doc_inp(token) < 0)
			return (-1);
	}
	return (1);
}

int	here_doc_lim(t_list **token)
{
	t_list	*curr;

	curr = *token;
	while (curr->next)
	{
		if (ft_strncmp(curr->content, "<<", longer(curr->content, "<<")) == 0)
		{
			if (here_doc_lim_inp(token, curr) < 0)
				return (-1);
			curr = curr->next;
		}
		if (curr->next)
			curr = curr->next;
	}
	return (1);
}

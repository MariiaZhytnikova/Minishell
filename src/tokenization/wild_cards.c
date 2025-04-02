/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:46:24 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/02 10:39:49 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replace_token_two(t_list *current, char *buffer)
{
	t_list	*new_token;

	if (!buffer || !buffer[0])
		return (1);
	free(current->content);
	current->content = ft_strdup(buffer);
	if (!current->content)
		return (-1);
	return (1);
}

bool	match(const char *str, const char *pattern)
{
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
		return (match(str, pattern + 1) || (*str && match(str + 1, pattern)));
	if (*str == *pattern)
		return (match(str + 1, pattern + 1));
	return (false);
}

int	check_files(t_list *current)
{
	struct dirent	*entry;
	DIR				*stream;
	t_temp			thing;

	ft_memset(thing.temp, 0, MAX_PROMT);
	thing.i = 0;
	thing.j = 0;
	stream = opendir(".");
	if (!stream)
		return (error_msg("Smthg with opendir wild", NULL, NULL, NULL), -1);
	entry = readdir(stream);
	while (entry)
	{
		if (match(entry->d_name, current->content) == true)
		{
			if (thing.temp[0])
				ft_strlcat(thing.temp, " ", MAX_PROMT);
			ft_strlcat(thing.temp, entry->d_name, MAX_PROMT);
		}
		entry = readdir(stream);
	}
	closedir(stream);
	if (replace_token_two(current, thing.temp) < 0)
		return (-1);
	return (1);
}

int	wild(t_list **token) // $ echo m*".txt" <- works as m*.txt -< "m.txtx" left as is
{
	t_list	*current;
	int		i;

	i = 0;
	current = *token;
	while (current)
	{
		if (ft_strchr(current->content, '*') && !ft_strchr(current->content, \
			'\'') && !ft_strchr(current->content, '\"'))
		{
			if (check_files(current) < 0)
				return (-1);
		}
		current = current->next;
	}
	return (1);
}

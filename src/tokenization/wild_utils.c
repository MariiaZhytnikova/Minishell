/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:46:24 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/10 14:46:58 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	remove_sq(const char **str, const char **pattern)
{
	(*pattern)++;
	while (**pattern && **str && **pattern == **str && **pattern != '\'')
	{
		if (**pattern != **str)
			return (false);
		(*pattern)++;
		(*str)++;
	}
	return (true);
}

static bool	remove_dq(const char **str, const char **pattern)
{
	(*pattern)++;
	while (**pattern && **str && **pattern != '\"')
	{
		if (**pattern != **str)
			return (false);
		(*pattern)++;
		(*str)++;
	}
	return (true);
}

bool	match(const char *str, const char *pattern)
{
	if (*pattern == '\'')
	{
		if (remove_sq(&str, &pattern) == false)
			return (false);
		return (match(str, pattern + 1));
	}
	if (*pattern == '\"')
	{
		if (remove_dq(&str, &pattern) == false)
			return (false);
		return (match(str, pattern + 1));
	}
	if (*pattern == '\0')
		return (*str == '\0');
	if (*pattern == '*')
		return (match(str, pattern + 1) || (*str && match(str + 1, pattern)));
	if (*str == *pattern)
		return (match(str + 1, pattern + 1));
	return (false);
}

bool	is_in_quotes(const char *str)
{
	while (*str)
	{
		if (*str == '\'')
		{
			str++;
			while (*str != '\'')
				str++;
		}
		else if (*str == '\"')
		{
			str++;
			while (*str != '\"')
				str++;
		}
		else if (*str == '*')
			return (false);
		str++;
	}
	return (true);
}

int	create_new(t_list **args, t_list *new, char *str)
{
	new = ft_lstnew(skip_quotes(str));
	if (!new)
		return (error_msg("ft_lstnew skip_quotes_no_ast", NULL, NULL, NULL), -1);
	ft_lstadd_back(args, new);
	return (1);
}

// https://github.com/osorosia/minishell/blob/main/.test/ok/wildcard.txt
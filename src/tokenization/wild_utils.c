/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:46:24 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/05 20:38:07 by mzhitnik         ###   ########.fr       */
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
	t_temp	thing;

	if (!str)
		return (-1);
	if (dynstr_init(&thing, str) < 0)
		return (1);
	if (skip_quotes(&thing, str) < 0)
	{
		free(thing.temp);
		return (-1);
	}
	new = ft_lstnew(ft_strdup(thing.temp));
	free (thing.temp);
	if (!new)
		return (-1);
	ft_lstadd_back(args, new);
	return (1);
}

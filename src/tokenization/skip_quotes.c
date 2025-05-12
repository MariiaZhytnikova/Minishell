/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:45:50 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/12 11:57:17 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_copy(char *arg, t_temp *thing, char c)
{
	thing->i++;
	while (arg[thing->i] && arg[thing->i] != c)
	{
		if (dynstr_char(thing, arg) < 0)
			return (-1);
	}
	thing->i++;
	return (1);
}

int	skip_quotes(t_temp *thing, char *arg)
{
	while (arg[thing->i])
	{
		if (arg[thing->i] == '\'')
		{
			if (skip_copy(arg, thing, '\'') < 0)
				return (-1);
		}
		else if (arg[thing->i] == '\"')
		{
			if (skip_copy(arg, thing, '\"') < 0)
				return (-1);
		}
		else
		{
			if (dynstr_char(thing, arg) < 0)
				return (-1);
		}
	}
	return (1);
}

static int	skip_loop(char *content, t_temp *thing)
{
	while (content[thing->i])
	{
		if (content[thing->i] == '\'' || content[thing->i] == '\"')
		{
			if (skip_quotes(thing, content) < 0)
				return (-1);
		}
		else
		{
			if (dynstr_char(thing, content) < 0)
				return (-1);
		}
	}
	return (1);
}

char	*skip(char *content)
{
	t_temp	thing;
	char	*res;

	if (!content || !*content)
	{
		res = ft_calloc(1, sizeof(char *));
		if (!res)
			return (NULL);
		return (res);
	}
	if (dynstr_init(&thing, content) < 0)
		return (NULL);
	if (skip_loop(content, &thing) < 0)
		return (NULL);
	res = ft_strdup(thing.temp);
	free(thing.temp);
	if (!res)
		return (NULL);
	return (res);
}

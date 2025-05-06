/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:26:32 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/05 18:07:08 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_sq(t_temp *thing, char *args)
{
	int	is_closed;

	is_closed = 0;
	if (dynstr_char(thing, args) < 0)
		return (-1);
	while (args[thing->i])
	{
		if (args[thing->i] != '\'')
		{
			if (dynstr_char(thing, args) < 0)
				return (-1);
		}
		else
		{
			if (dynstr_char(thing, args) < 0)
				return (-1);
			is_closed = 1;
			break ;
		}
	}
	if (is_closed == 0)
		return (-1);
	return (1);
}

static int	skip_dq(t_temp *thing, char *args)
{
	int	is_closed;

	is_closed = 0;
	if (dynstr_char(thing, args) < 0)
		return (-1);
	while (args[thing->i])
	{
		if (args[thing->i] != '\"')
		{
			if (dynstr_char(thing, args) < 0)
				return (-1);
		}
		else
		{
			if (dynstr_char(thing, args) < 0)
				return (-1);
			is_closed = 1;
			break ;
		}
	}
	if (is_closed == 0)
		return (-1);
	return (1);
}

int	if_quotes(t_temp *thing, char *args)
{
	if (args[thing->i] == '\'')
	{
		if (skip_sq(thing, args) < 0)
			return (error_msg(ERR_BASH, ERR_QUOTES, NULL, NULL), -1);
	}
	else if (args[thing->i] == '\"')
	{
		if (skip_dq(thing, args) < 0)
			return (error_msg(ERR_BASH, ERR_QUOTES, NULL, NULL), -1);
	}
	return (1);
}

int	handle_quotes(t_temp *thing, char *args)
{
	while (args[thing->i] && !ft_isspace(args[thing->i]))
	{
		if (args[thing->i] == '\'' || args[thing->i] == '\"')
		{
			if (if_quotes(thing, args) < 0)
				return (-1);
		}
		else
		{
			if (dynstr_char(thing, args) < 0)
				return (-1);
		}
	}
	return (1);
}

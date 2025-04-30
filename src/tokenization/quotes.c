/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:26:32 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/29 16:33:08 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_sq(t_temp *thing, char *args)
{
	int	is_closed;

	is_closed = 0;
	if (dynstr_append_char(thing, args) < 0)
		return (-1);
	while (args[thing->i])
	{
		if (args[thing->i] != '\'')
		{
			if (dynstr_append_char(thing, args) < 0)
				return (-1);
		}
		else
		{
			if (dynstr_append_char(thing, args) < 0)
				return (-1);
			is_closed = 1;
			break ;
		}
	}
	if (is_closed == 0)
		return (-1);
	return (1);
}

static int	skip_dq(t_session *session, t_temp *thing, char *args, int closed)
{
	if (dynstr_append_char(thing, args) < 0)
		return (-1);
	while (args[thing->i])
	{
		if (args[thing->i] != '\"')
		{
			if (session && args[thing->i] == '$')
			{
				if (expansion(session, thing, args) < 0)
					return (-1);
			}
			else
			{
				if (dynstr_append_char(thing, args) < 0)
					return (-1);
			}
		}
		else
		{
			if (dynstr_append_char(thing, args) < 0)
				return (-1);
			closed = 1;
			break ;
		}
	}
	if (closed == 0)
		return (-1);
	return (1);
}

int	if_quotes(t_session *session, t_temp *thing, char *args)
{
	if (args[thing->i] == '\'')
	{
		if (skip_sq(thing, args) < 0)					// Need error message
			return (error_msg(ERR_BASH, "Quotes not closed", NULL, NULL), -1);  // NEED MSG
	}
	else if (args[thing->i] == '\"')
	{
		if (skip_dq(session, thing, args, 0) < 0)
			return (error_msg(ERR_BASH, "Quotes not closed", NULL, NULL), -1); // NEED MSG
	}
	return (1);
}

int	handle_quotes(t_session *session, t_temp *thing, char *args)
{
	while (args[thing->i] && !ft_isspace(args[thing->i]))
	{
		if (args[thing->i] == '\'' || args[thing->i] == '\"')
		{
			if (if_quotes(session, thing, args) < 0)
				return (-1);
			continue ;
		}
		else
		{
			// if (args[thing->i] == '\\' || args[thing->i] == ';')
			// 	return (free (thing->temp), error_msg(ERR_EXCL, NULL, NULL, NULL), -1);
			if (dynstr_append_char(thing, args) < 0)
				return (-1);
			
		}
	}
	return (1);
}

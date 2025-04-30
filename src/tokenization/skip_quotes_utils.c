/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:45:50 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/29 16:38:49 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_copy(char *arg, t_temp *thing, char c)
{
	thing->i++;
	while (arg[thing->i] && arg[thing->i] != c)
	{
		if (dynstr_append_char(thing, arg) < 0)
			return (-1);
	}
	thing->i++;
	return (1);
}

int	skip_quotes(char *arg, t_temp *thing)
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
		else if (arg[thing->i] == '\\')
		{
			if (skip_copy(arg, thing, '\\') < 0)
				return (-1);
		}
		else
		{
			if (dynstr_append_char(thing, arg) < 0)
				return (-1);
		}
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:45:50 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/27 16:01:41 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_copy(char *arg, t_temp *thing, char c)
{
	thing->i++;
	while (arg[thing->i] && arg[thing->i] != c)
		dynstr_append_char(thing, arg);
	thing->i++;
}

void	skip_quotes(char *arg, t_temp *thing)
{
	while (arg[thing->i])
	{
		if (arg[thing->i] == '\'')
			skip_copy(arg, thing, '\'');
		else if (arg[thing->i] == '\"')
			skip_copy(arg, thing, '\"');
		else if (arg[thing->i] == '\\')
			skip_copy(arg, thing, '\\');
		else
			dynstr_append_char(thing, arg);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dynstr.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/02 13:11:33 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/05 18:00:14 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	dynstr_init(t_temp *thing, char *input)
{
	thing->i = 0;
	thing->j = 0;
	thing->cap = ft_strlen(input) * 2;
	thing->temp = ft_calloc(1, thing->cap);
	if (!thing->temp)
		return (-1);
	return (1);
}

int	dynstr_char(t_temp *thing, char *str)
{
	if (thing->j + 2 >= (int)thing->cap)
	{
		thing->temp = reall(thing->temp, thing->cap, thing->cap * 2);
		if (thing->temp == NULL)
			return (-1);
		thing->cap *= 2;
	}
	thing->temp[(thing->j)++] = str[(thing->i)++];
	return (1);
}

int	dynstr_str(t_temp *thing, char *str)
{
	int	i;

	if (!str || !*str)
		return (1);
	if (thing->j + ft_strlen(str) + 1 >= thing->cap)
	{
		thing->temp = reall(thing->temp, thing->cap, thing->cap * 2);
		if (thing->temp == NULL)
			return (-1);
		thing->cap *= 2;
	}
	i = 0;
	while (str[i])
		thing->temp[(thing->j)++] = str[i++];
	return (1);
}

int	dynstr_symb(t_temp *thing, char c)
{
	if (thing->j + 2 >= (int)thing->cap)
	{
		thing->temp = reall(thing->temp, thing->cap, thing->cap * 2);
		if (thing->temp == NULL)
			return (-1);
		thing->cap *= 2;
	}
	thing->temp[(thing->j)++] = c;
	return (1);
}

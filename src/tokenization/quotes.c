/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:26:32 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/26 13:48:29 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	skip_single_quotes(char *temp, char *args, int *i, int *j)
{
	int	is_closed;

	is_closed = 0;
	temp[(*j)++] = args[(*i)++];
	while (args[*i])
	{
		if (args[*i] != '\'')
			temp[(*j)++] = args[(*i)++];
		else
		{
			temp[(*j)++] = args[(*i)++];
			is_closed = 1;
			break ;
		}
	}
	if (is_closed == 0)
		return (error_msg("Single quotes not closed quotes.c", NULL, NULL, NULL), -1);
	return (1);
}

static int	skip_double_quotes(char *temp, char *args, int *i, int *j)
{
	int	is_closed;

	is_closed = 0;
	temp[(*j)++] = args[(*i)++];
	while (args[*i])
	{
		if (args[*i] != '\"')
			temp[(*j)++] = args[(*i)++];
		else
		{
			temp[(*j)++] = args[(*i)++];
			is_closed = 1;
			break ;
		}
	}
	if (is_closed == 0)
		return (error_msg("Double quotes not closed quotes_utils", NULL, NULL, NULL), -1);
	return (1);
}

int	if_quotes(char *temp, char *args, int *i, int *j)
{
	if (args[*i] == '\'')
	{
		if (skip_single_quotes(temp, args, i, j) < 0)
			return (-1);
	}
	else if (args[*i] == '\"')
	{
		if (skip_double_quotes(temp, args, i, j) < 0)
			return (-1);
	}
	return (1);
}

int	handle_quotes(char *temp, char *args, int *i)
{
	int	j;

	j = 0;
	while (args[*i] && args[*i] != ' ')
	{
		if (args[*i] == '\'' || args[*i] == '\"')
		{
			if (if_quotes(temp, args, i, &j) < 0)
				return (-1);
			continue ;
		}
		else
		{
			if (args[*i] == '\\' || args[*i] == ';')
				return (error_msg(ERR_EXCL, NULL, NULL, NULL), -1);
			temp[j++] = args[(*i)++];
		}
	}
	temp[j] = 0;
	return (1);
}

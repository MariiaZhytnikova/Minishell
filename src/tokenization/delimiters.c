/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:09:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/02 10:20:04 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delim_or_red(char *str)
{
	if (ft_strlen(str) >= 3 && str[0] == '<' && str[1] == '<' && str[2] == '<')
		return (true);
	if (ft_strlen(str) >= 2 && str[0] == '|' && str[1] == '|')
		return (true);
	if (ft_strlen(str) >= 2 && str[0] == '&' && str[1] == '&')
		return (true);
	if (ft_strlen(str) >= 2 && str[0] == '<' && str[1] == '<')
		return (true);
	if (ft_strlen(str) >= 2 && str[0] == '>' && str[1] == '>')
		return (true);
	if (str[0] == '|')
		return (true);
	if (str[0] == '&')
		return (true);
	if (str[0] == '<')
		return (true);
	if (str[0] == '>')
		return (true);
	return (false);
}

static bool	check_two(char *str, int i)
{
	if ((ft_strlen(str) >= 2 && str[i] == '|' && str[i + 1] == '|')
		|| (ft_strlen(str) >= 2 && str[i] == '&' && str[i + 1] == '&')
		|| ft_strlen(str) >= 2 && str[i] == '<' && str[i + 1] == '<'
		|| (ft_strlen(str) >= 2 && str[i] == '>' && str[i + 1] == '>'))
		return (true);
	return (false);
}

static void	copy_delimeter(t_temp *thing, char *str)
{
	if (ft_strlen(str) >= 3 && str[thing->i] == '<' && str[thing->i + 1] == '<'
		&& str[thing->i + 2] == '<')
	{
		thing->temp[thing->j++] = ' ';
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = ' ';
	}
	else if (check_two(str, thing->i) == true)
	{
		thing->temp[thing->j++] = ' ';
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = ' ';
	}
	else if (str[thing->i] == '|' || str[thing->i] == '&' \
		|| str[thing->i] == '<' || str[thing->i] == '>')
	{
		thing->temp[thing->j++] = ' ';
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = ' ';
	}
}

char	*add_spaces(t_session *session, char *input)
{
	t_temp	thing;
	char	*result;

	ft_memset(thing.temp, 0, MAX_PROMT);
	thing.i = 0;
	thing.j = 0;
	while (input[thing.i])
	{
		if (input[thing.i] == '\'' || input[thing.i] == '\"')
		{
			if (if_quotes(NULL, &thing, input) < 0)
				return (NULL);
			continue ;
		}
		if (is_delim_or_red(&input[thing.i]))
			copy_delimeter(&thing, input);
		else if (input[thing.i])
			thing.temp[(thing.j)++] = input[(thing.i)++];
	}
	thing.temp[thing.j] = 0;
	result = ft_strdup(thing.temp);
	if (!*result || !result[0])
		return (NULL);
	return (result);
}

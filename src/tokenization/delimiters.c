/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:09:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/22 11:14:11 by mzhitnik         ###   ########.fr       */
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

void	copy_delimeter(t_temp *thing, char *str)
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
	else if (str[thing->i] == '|' || str[thing->i] == '&'
		|| str[thing->i] == '<' || str[thing->i] == '>')
	{
		thing->temp[thing->j++] = ' ';
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = ' ';
	}
}

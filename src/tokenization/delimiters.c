/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:09:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/26 10:06:16 by mzhitnik         ###   ########.fr       */
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

static bool	check_two(char *str, int *i)
{
	if ((ft_strlen(str) >= 2 && str[*i] == '|' && str[*i + 1] == '|')
		|| (ft_strlen(str) >= 2 && str[*i] == '&' && str[*i + 1] == '&')
		|| ft_strlen(str) >= 2 && str[*i] == '<' && str[*i + 1] == '<'
		|| (ft_strlen(str) >= 2 && str[*i] == '>' && str[*i + 1] == '>'))
		return (true);
	return (false);
}

void	copy_delimeter(char *temp, char *str, int *i, int *j)
{
	if (ft_strlen(str) >= 3 && str[*i] == '<' && str[*i + 1] == '<'
		&& str[*i + 2] == '<')
	{
		temp[(*j)++] = ' ';
		temp[(*j)++] = str[(*i)++];
		temp[(*j)++] = str[(*i)++];
		temp[(*j)++] = str[(*i)++];
		temp[(*j)++] = ' ';
	}
	else if (check_two(str, i) == true)
	{
		temp[(*j)++] = ' ';
		temp[(*j)++] = str[(*i)++];
		temp[(*j)++] = str[(*i)++];
		temp[(*j)++] = ' ';
	}
	else if (str[*i] == '|' || str[*i] == '&' || str[*i] == '<' \
		|| str[*i] == '>')
	{
		temp[(*j)++] = ' ';
		temp[(*j)++] = str[(*i)++];
		temp[(*j)++] = ' ';
	}
}

char	*add_spaces(char *input)
{
	int		i;
	int		j;
	char	temp[MAX_PROMT];
	char	*result;

	ft_memset(temp, 0, MAX_PROMT);
	i = 0;
	j = 0;
	while (input[i])
	{
		if (if_quotes(temp, input, &i, &j) < 0)
			return (NULL);
		else if (is_delim_or_red(&input[i]))
			copy_delimeter(temp, input, &i, &j);
		else if (input[i])
			temp[j++] = input[(i)++];
	}
	temp[j] = 0;
	result = ft_strdup(temp);
	if (!*result || !result[0])
		return (NULL);
	return (result);
}

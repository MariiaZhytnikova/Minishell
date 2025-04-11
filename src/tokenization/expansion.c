/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:18:00 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/11 16:46:48 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnum_plus(int c)
{
	return ((c >= 'a' && c <= 'z')
		|| (c >= 'A' && c <= 'Z')
		|| (c >= '0' && c <= '9') || c == '_');
}

int	expansion(t_session *session, t_temp *thing, char *str)
{
	char	name[MAX_PROMT];
	char	*env;
	int		len_name;
	char	*status_str;
	int		k;

	ft_memset(name, 0, MAX_PROMT);
	if (str[thing->i + 1] == '?')
	{
		status_str = ft_itoa(session->status_last);
		if (!status_str)
			return (-1);
		thing->i += 2; // Skip $ and ?
		k = 0;
		while (status_str[k])
			thing->temp[thing->j++] = status_str[k++];
		free(status_str);
		return (1);
	}
	if (!str[thing->i + 1] || !ft_isalnum_plus(str[thing->i + 1]))
	{
		thing->temp[thing->j++] = str[thing->i++];
		return (1);
	}
	len_name = 0;
	thing->i++;
	while (str[thing->i] && ft_isalnum_plus(str[thing->i]))
		name[len_name++] = str[thing->i++];
	if (search_in_env(session->env_var, name))
	{
		env = ft_strdup(search_in_env(session->env_var, name)->content);
		if (!env)
			return (-1);
	}
	else
		return (1);
	while (env[len_name + 1])
		thing->temp[thing->j++] = env[len_name++ + 1];
	return (free(env), 1);
}

int	expansion_two(t_session *session, char **str)
{
	t_temp	thing;

	ft_memset(thing.temp, 0, MAX_PROMT);
	thing.i = 0;
	thing.j = 0;
	while ((*str)[thing.i])
	{
		if ((*str)[thing.i] == '$')
		{
			if (expansion(session, &thing, *str) < 0)
				return (-1);
		}
		else
			thing.temp[thing.j++] = (*str)[thing.i++];
	}
	free (*str);
	*str = ft_strdup(thing.temp);
	if (!*str)
		return (-1);
	return (1);
}

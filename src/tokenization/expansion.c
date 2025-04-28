/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:18:00 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/28 11:16:22 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_heredoc(t_temp *thing, char *str)
{
	int	i;

	i = thing->i - 1;
	while (str[i] && ft_isspace(str[i]))
		i--;
	if (str[i] == '<' && str[i - 1] && str[i - 1] == '<')
		return (true);
	return (false);
}

static int	find_it(t_session *session, t_temp *thing)
{
	char	*status_str;

	status_str = ft_itoa(session->status_last);
	if (!status_str)
		return (-1);
	thing->i += 2;
	dynstr_append_str(thing, status_str);
	free(status_str);
	return (1);
}

static int	no_expansion(t_session *session, t_temp *thing, char *str)
{
	if (str[thing->i + 1] == '?')
		return (find_it(session, thing), 0);
	if (!str[thing->i + 1] || !ft_isalnum_plus(str[thing->i + 1]))
	{
		if (str[thing->i + 1] == '\"' || str[thing->i + 1] == '\'')
		{
			thing->i++;
			return (0);
		}
			thing->temp[thing->j++] = str[thing->i++];
		return (0);
	}
	if (thing->i - 1 > 0 && is_heredoc(thing, str) == true) // check for previous characters before is_heredoc
	{
		dynstr_append_char(thing, str);
		while (str[thing->i] && ft_isalnum_plus(str[thing->i]))
			dynstr_append_char(thing, str);
		return (0);
	}
	return (1);
}

int	expansion(t_session *session, t_temp *thing, char *str)
{
	char	name[MAX_PR];
	char	*env;
	int		len_name;

	ft_memset(name, 0, MAX_PR);
	if (no_expansion(session, thing, str) == 0)
		return (1);
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
	dynstr_append_str(thing, &env[len_name + 1]);		// No strlcat before and after
	return (free(env), 1);
}

int	expansion_two(t_session *session, char **str)
{
	t_temp	thing;

	if (dynstr_init(&thing, *str) < 0)
		return (1);
	while ((*str)[thing.i])
	{
		if ((*str)[thing.i] == '$')
		{
			if (expansion(session, &thing, *str) < 0)
				return (-1);
		}
		else
			dynstr_append_char(&thing, *str);
	}
	free (*str);
	*str = ft_strdup(thing.temp);
	if (!*str)
		return (-1);
	free (thing.temp);
	return (1);
}

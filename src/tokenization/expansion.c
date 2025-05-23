/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:18:00 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/11 14:37:30 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	no_expansion(t_session *session, t_temp *thing, char *str, int exp)
{
	if (str[thing->i + 1] && str[thing->i + 1] == '?')
		return (status(session, thing), 0);
	if (str[thing->i + 1] && !ft_isalnum_plus(str[thing->i + 1]))
	{
		if (exp && (str[thing->i + 1] == '\"' || str[thing->i + 1] == '\''))
		{
			thing->i++;
			return (0);
		}
		if (dynstr_char(thing, str) < 0)
			return (-1);
		return (0);
	}
	if (!str[thing->i + 1])
	{
		if (dynstr_char(thing, str) < 0)
			return (-1);
		return (0);
	}
	return (1);
}

int	expansion(t_session *session, t_temp *thing, char *str, int exp)
{
	char	name[MAX_PR];
	char	*env;
	int		res[2];

	ft_memset(name, 0, MAX_PR);
	res[0] = no_expansion(session, thing, str, exp);
	if (res[0] == 0)
		return (1);
	else if (res[0] < 0)
		return (-1);
	res[1] = 0;
	thing->i++;
	while (str[thing->i] && ft_isalnum_plus(str[thing->i]))
		name[res[1]++] = str[thing->i++];
	if (search_in_env(session->env_var, name))
	{
		env = ft_strdup(search_in_env(session->env_var, name)->content);
		if (!env)
			return (-1);
	}
	else
		return (1);
	if (dynstr_str(thing, &env[res[1] + 1]) < 0)
		return (free(env), -1);
	return (free(env), 1);
}

static int	dq_exp(t_session *session, t_temp *thing, char *content)
{
	if (dynstr_char(thing, content) < 0)
		return (-1);
	while (content[thing->i])
	{
		if (content[thing->i] != '\"')
		{
			if (session && content[thing->i] == '$')
			{
				if (expansion(session, thing, content, 0) < 0)
					return (-1);
			}
			else
			{
				if (dynstr_char(thing, content) < 0)
					return (-1);
			}
		}
		else
		{
			if (dynstr_char(thing, content) < 0)
				return (-1);
			break ;
		}
	}
	return (1);
}

int	exp_loop(t_session *session, t_temp *thing, char *content)
{
	while (content[thing->i])
	{
		if (content[thing->i] == '$')
		{
			if (expansion(session, thing, content, 1) < 0)
				return (free(thing->temp), -1);
		}
		else if (content[thing->i] == '\'')
		{
			if (skip_sq(thing, content) < 0)
				return (free(thing->temp), -1);
		}
		else if (content[thing->i] == '\"')
		{
			if (dq_exp(session, thing, content) < 0)
				return (free(thing->temp), -1);
		}
		else
		{
			if (dynstr_char(thing, content) < 0)
				return (free(thing->temp), -1);
		}
	}
	return (1);
}

t_list	*get_exp(t_session *session, char *content, int split)
{
	t_temp	thing;
	t_list	*exp_args;

	if (dynstr_init(&thing, content) < 0)
		return (NULL);
	if (exp_loop(session, &thing, content) < 0)
		return (NULL);
	exp_args = NULL;
	if (split)
	{
		if (split_input(&exp_args, thing.temp) < 0)
			return (free(thing.temp), NULL);
	}
	else if (!split)
	{
		exp_args = ft_calloc(1, sizeof(t_list));
		if (!exp_args)
			return (free(thing.temp), NULL);
		exp_args->content = ft_strdup(thing.temp);
		if (!exp_args->content)
			return (free(thing.temp), NULL);
	}
	return (free(thing.temp), exp_args);
}

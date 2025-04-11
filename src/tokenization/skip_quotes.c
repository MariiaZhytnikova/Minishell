/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:45:50 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/10 13:36:15 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*skip_quotes(const char *arg)
{
	t_temp	thing;

	ft_memset(thing.temp, 0, MAX_PROMT);
	thing.i = 0;
	thing.j = 0;
	while (arg[thing.i])
	{
		if (arg[thing.i] == '\'')
		{
			thing.i++;
			while (arg[thing.i] && arg[thing.i] != '\'')
				thing.temp[thing.j++] = arg[thing.i++];
			thing.i++;
		}
		else if (arg[thing.i] == '\"')
		{
			thing.i++;
			while (arg[thing.i] && arg[thing.i] != '\"')
				thing.temp[thing.j++] = arg[thing.i++];
			thing.i++;
		}
		else
			thing.temp[thing.j++] = arg[thing.i++];
	}
	return (ft_strdup(thing.temp));
}

int	check_in(char **input)
{
	int		i;
	char	*buffer;

	i = 0;
	buffer = NULL;
	while (input[i])
	{
		if (ft_strchr(input[i], '\'') || ft_strchr(input[i], '\"'))
		{
			free(input[i]);
			input[i] = skip_quotes(input[i]);
		}
		i++;
	}
	return (1);
}

static int	check_case(t_session *session, t_command	*cmd, int id)
{
	if (session->count->red_in_nb[id] > 0)
	{
		if (check_in(cmd->in) < 0)
			return (-1);
	}
	if (session->count->red_out_nb[id] > 0)
	{
		if (check_in(cmd->out) < 0)
			return (-1);
	}
	if (session->count->red_app_nb[id] > 0)
	{
		if (check_in(cmd->out_app) < 0)
			return (-1);
	}
	if (session->count->red_h_doc_nb[id] > 0)
	{
		if (check_in(cmd->h_doc) < 0)
			return (-1);
	}
	return (1);
}

int	skip(t_session *session)
{
	int	id;

	id = 0;
	if (wild(session) < 0)
		return (-1);
	while (id < session->count->cmd_nb)
	{
		if (check_case(session, session->cmds[id], id) < 0)
			return (-1);
		id++;
	}
	return (1);
}

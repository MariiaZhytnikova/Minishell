/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:45:50 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/16 11:18:52 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(const char *arg, t_temp *thing)
{
	while (arg[thing->i])
	{
		if (arg[thing->i] == '\'')
		{
			thing->i++;
			while (arg[thing->i] && arg[thing->i] != '\'')
				thing->temp[thing->j++] = arg[thing->i++];
			thing->i++;
		}
		else if (arg[thing->i] == '\"')
		{
			thing->i++;
			while (arg[thing->i] && arg[thing->i] != '\"')
				thing->temp[thing->j++] = arg[thing->i++];
			thing->i++;
		}
		else
			thing->temp[thing->j++] = arg[thing->i++];
	}
}

int	check_in(char **input)
{
	t_temp	thing;
	int		id;

	id = 0;
	while (input[id])
	{
		ft_memset(thing.temp, 0, MAX_PROMT);
		thing.i = 0;
		thing.j = 0;
		if (ft_strchr(input[id], '\'') || ft_strchr(input[id], '\"'))
		{
			skip_quotes(input[thing.i], &thing);
			free(input[id]);
			input[id] = ft_strdup(thing.temp);
			if (!input[id])
				return (error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL), -1);
		}
		id++;
	}
	return (1);
}

int	check_last(char **input)
{
	t_temp	thing;

	ft_memset(thing.temp, 0, MAX_PROMT);
	thing.i = 0;
	thing.j = 0;
	if (ft_strchr(*input, '\'') || ft_strchr(*input, '\"'))
	{
		skip_quotes(*input, &thing);
		free(*input);
		*input = ft_strdup(thing.temp);
		if (!*input)
			return (error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL), -1);
	}
	return (1);
}

static int	check_case(t_session *session, t_command *cmd, int id)
{
	int	i;
	int	num;
	
	i = 0;
	while (cmd->files[i])
	{
		if (check_last(&cmd->files[i]->name) < 0)
			return (-1);
		// printf("check_last >%s<\n", cmd->files[i]->name);
		i++;
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

	// printf("skip\n");
	id = 0;
	if (wild(session) < 0)
		return (-1);
	while (id < session->count->cmd_nb)
	{
		if (check_case(session, session->cmds[id], id) < 0)
			return (-1);
		// printf("after check_case\n");
		if (check_last(&session->cmds[id]->last_in->name) < 0)
			return (-1);
		// printf("after check_last\n");
		if (check_last(&session->cmds[id]->last_out->name) < 0)
			return (-1);
		// printf("after check_last\n");
		id++;
	}
	// printf("after skip\n");
	return (1);
}

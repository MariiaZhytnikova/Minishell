/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skip_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 09:45:50 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/30 14:51:05 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_last(char **input)
{
	t_temp	thing;

	if (!*input || !**input)
		return (1);
	if (ft_strchr(*input, '\'') || ft_strchr(*input, '\"'))
	{
		if (dynstr_init(&thing, *input) < 0)
			return (-1);
		if (skip_quotes(*input, &thing) < 0)
		{
			free(thing.temp);
			return (-1);
		}
		free(*input);
		*input = ft_strdup(thing.temp);
		free(thing.temp);
		if (!*input)
			return (error_msg(ERR_BASH, ERR_MALLOC, NULL, NULL), -1);
	}
	return (1);
}

static int	check_case(t_command *cmd)
{
	int	i;

	i = 0;
	while (cmd->files[i])
	{
		if (check_last(&cmd->files[i]->name) < 0)
			return (-1);
		i++;
	}
	return (1);
}

static int	check_exp_two(t_session *session, char *args, t_temp *thing)
{
	while (args[thing->i])
	{
		if (args[thing->i] == '$')
		{
			if (expansion(session, thing, args) < 0)
				return (-1);
		}
		else if (args[thing->i] == '\'' || args[thing->i] == '\"')
		{
			if (if_quotes(session, thing, args) < 0)
				return (-1);
			continue ;
		}
		else
		{
			if (dynstr_append_char(thing, args) < 0)
				return (-1);
		}
	}
	return (1);
}

static int	check_exp(t_session *session, t_command *cmd) // NEW FUNCTION
{
	int		i;
	t_temp	thing;

	i = 0;
	while (cmd->args[i])
	{
		if (dynstr_init(&thing, cmd->args[i]) < 0)
			return (-1);
		if (check_exp_two(session, cmd->args[i], &thing) < 0)
		{
			printf("%s\n", thing.temp);
			free (thing.temp);
			return (-1);
		}
		free(cmd->args[i]);
		cmd->args[i] = ft_strdup(thing.temp);
		free(thing.temp);
		i++;
	}
	return (1);
}

int	skip(t_session *session)
{
	int	id;

	id = 0;
	while (id < session->count->cmd_nb)
	{
		if (check_exp(session, session->cmds[id]) < 0)
		{
			printf("check_exp failed\n");
			return (-1);
		}
		if (check_case(session->cmds[id]) < 0)
			return (-1);
		if (check_last(&session->cmds[id]->last_in->name) < 0)
			return (-1);
		if (check_last(&session->cmds[id]->last_out->name) < 0)
			return (-1);
		id++;
	}
	if (wild(session) < 0)
		return (-1);
	return (1);
}

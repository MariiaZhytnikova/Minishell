/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:49 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/23 13:21:25 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_command(t_command *command, t_list **current, int i)
{
	while (*current && is_del((*current)->content) == false)
	{
		if (is_red((*current)->content) == true)
		{
			if (get_redirection(command, *current) < 0)
				return (-1);
			*current = (*current)->next->next;
		}
		else if (*current)
		{
			command->args[i] = ft_strdup((*current)->content);
			if (!command->args[i])
				return (-1);
			*current = (*current)->next;
			i++;
		}
	}
	command->args[i] = NULL;
	return (1);
}

int	commands(t_session *session, t_list **token)
{
	t_list	*curr;
	int		i;

	if (red_struct_alloc(session) < 0)
		return (-1);
	i = 0;
	curr = *token;
	while (curr)
	{
		if (is_del(curr->content) == false)
		{
			if (handle_command(session->cmds[i], &curr, 0) < 0)
				return (-1);
			if (curr && is_del(curr->content) == true)
				get_delimiter(session->cmds[i++], curr);
		}
		if (curr)
			curr = curr->next;
	}
	return (1);
}

static int	handle_tokenization(t_session *session, t_list **token)
{
	int	status;

	status = split_and_check(session, token, session->input);
	if (status < 0)
	{
		if (status == -2)
			session->status_last = 2;
		if (*token)
			ft_lstclear(token, free);
		return (-1);
	}
	if (status == 3 || status == 4)
	{
		if (*token)
			ft_lstclear(token, free);
		return (status);
	}
	if (g_signalnum == 2)
	{
		if (*token)
			ft_lstclear(token, free);
		session->status_last = 130;
		return (-1);
	}
	return (1);
}

int	lexical_analyzer(t_session *session)
{
	t_list	*token;
	t_count	*cnt;
	int		status;

	token = NULL;
	status = handle_tokenization(session, &token);
	if (status != 1)
		return (status);
	cnt = ft_calloc(1, sizeof(t_count));
	if (!cnt)
		return (-1);
	if (numbers(session, &token, cnt) < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "numbers", NULL), -1);
	session->count = cnt;
	if (commands(session, &token) < 0)
		return (ft_lstclear(&token, free), free_session(session),
			error_msg(ERR_BASH, ERR_CRASH, "commands", NULL), -1);
	ft_lstclear(&token, free);
	if (skip(session) < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "skip", NULL), -1);
	return (1);
}

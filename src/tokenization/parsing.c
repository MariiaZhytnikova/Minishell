/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:32:49 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/12 13:20:45 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	split_cmd(t_session *s, t_command *cmd, t_list **cur, t_list **arg)
{
	int		i;

	i = 0;
	while (*cur && is_del((*cur)->content) == false)
	{
		if (is_red((*cur)->content) == true)
		{
			if (get_redirection(s, cmd, *cur) < 0)
				return (-1);
			*cur = (*cur)->next->next;
		}
		else
		{
			if (get_arguments(s, *cur, arg) < 0)
				return (-1);
			*cur = (*cur)->next;
		}
	}
	return (1);
}

int	commands(t_session *session, t_list **token)
{
	t_list	*curr;
	t_list	*args;
	int		i;

	args = NULL;
	i = 0;
	curr = *token;
	while (curr)
	{
		if (is_del(curr->content) == false)
		{
			if (split_cmd(session, session->cmds[i], &curr, &args) < 0)
				return (ft_lstclear(&args, free), -1);
			if (curr && is_del(curr->content) == true)
				get_delimiter(session->cmds[i], curr);
		}
		if (!curr || is_del(curr->content) == true)
			if (copy_args(session->cmds[i++], &args) < 0)
				return (-1);
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
		return (status);
	}
	if (status == 3 || status == 4)
	{
		if (*token)
			ft_lstclear(token, free);
		return (status);
	}
	if (g_signalnum == 2 || status == 2)
	{
		if (*token)
			ft_lstclear(token, free);
		session->status_last = 130;
		return (2);
	}
	return (1);
}

int	lexical_analyzer(t_session *session)
{
	t_list	*token;
	int		status;

	token = NULL;
	status = handle_tokenization(session, &token);
	if (status != 1)
		return (status);
	if (numbers(session, &token) < 0)
	{
		ft_lstclear(&token, free);
		return (error_msg(ERR_BASH, ERR_CRASH, "numbers", NULL), -1);
	}
	if (commands(session, &token) < 0)
		return (ft_lstclear(&token, free), -1);
	ft_lstclear(&token, free);
	return (1);
}

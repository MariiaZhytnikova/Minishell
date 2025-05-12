/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:09:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/12 11:59:21 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_arguments(t_session *session, t_list *curr, t_list **args)
{
	t_list	*exp_args;
	t_list	*new;
	t_list	*current;

	exp_args = get_exp(session, curr->content, 1);
	if (!exp_args)
		return (1);
	if (ft_strchr(curr->content, '*'))
		if (wild(&exp_args) < 0)
			return (-1);
	current = exp_args;
	while (current)
	{
		new = ft_lstnew(skip(current->content));
		if (!new)
		{
			ft_lstclear(&exp_args, free);
			return (-1);
		}
		ft_lstadd_back(args, new);
		current = current->next;
	}
	ft_lstclear(&exp_args, free);
	return (1);
}

int	red_handler(t_session *session, t_list *curr, t_list **exp_red)
{
	if ((ft_strncmp(curr->content, "<<<",
				longer(curr->content, "<<<")) == 0))
	{
		*exp_red = get_exp(session, curr->next->content, 0);
		if (!*exp_red)
		{
			*exp_red = ft_calloc(1, sizeof(t_list));
			if (!*exp_red)
				return (-1);
			return (1);
		}
	}
	else
	{
		*exp_red = get_exp(session, curr->next->content, 1);
		if (!exp_red)
			return (error_msg(ERR_BASH, ERR_REDIR, NULL, NULL), -1);
		if (ft_strchr(curr->next->content, '*'))
			if (wild(exp_red) < 0)
				return (-1);
	}
	if (!*exp_red || (*exp_red && (*exp_red)->next))
		return (ft_lstclear(exp_red, free),
			error_msg(ERR_BASH, ERR_REDIR, NULL, NULL), -1);
	return (1);
}

int	get_content(t_list *curr, t_list *exp_red, char **cont)
{
	if ((ft_strncmp(curr->content, "<<<",
				longer(curr->content, "<<<")) == 0))
	{
		*cont = ft_strdup(exp_red->content);
		if (!cont)
			return (-1);
		if (!*cont)
			*cont = ft_strdup("\0");
		if (!cont)
			return (-1);
	}
	else
		*cont = skip(exp_red->content);
	return (1);
}

int	get_redirection(t_session *session, t_command *cmd, t_list *curr)
{
	char	*cont;
	t_list	*exp_red;
	int		exp_status;

	exp_red = NULL;
	exp_status = red_handler(session, curr, &exp_red);
	if (exp_status < 0)
		return (-1);
	else if (exp_status == 0)
		return (1);
	if (get_content(curr, exp_red, &cont) < 0)
		return (-1);
	ft_lstclear(&exp_red, free);
	if (!cont)
		return (1);
	if (!(ft_strncmp(curr->content, "<<<",
				longer(curr->content, "<<<")) == 0))
		if (files(cmd, curr, cont) < 0)
			return (free(cont), error_msg(ERR_BASH, ERR_CRASH, NULL, NULL), -1);
	if (redirection_in(cmd, curr, cont) < 0)
		return (free(cont), error_msg(ERR_BASH, ERR_CRASH, NULL, NULL), -1);
	if (redirection_out(cmd, curr, cont) < 0)
		return (free(cont), error_msg(ERR_BASH, ERR_CRASH, NULL, NULL), -1);
	free(cont);
	return (1);
}

void	get_delimiter(t_command *command, t_list *current)
{
	if ((ft_strncmp(current->content,
				"|", longer(current->content, "|")) == 0))
		command->type = PIPE;
	else if ((ft_strncmp(current->content,
				"||", longer(current->content, "||")) == 0))
		command->type = OR;
	else if ((ft_strncmp(current->content,
				"&&", longer(current->content, "&&")) == 0))
		command->type = AND;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:25:56 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/05 20:25:04 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_del(char *content)
{
	if (ft_strncmp(content, "|", longer(content, "|")) == 0)
		return (true);
	if (ft_strncmp(content, "||", longer(content, "||")) == 0)
		return (true);
	if (ft_strncmp(content, "&&", longer(content, "&&")) == 0)
		return (true);
	return (false);
}

bool	is_red(char *content)
{
	if (ft_strncmp(content, ">", longer(content, ">")) == 0)
		return (true);
	if (ft_strncmp(content, ">>", longer(content, ">>")) == 0)
		return (true);
	if (ft_strncmp(content, "<", longer(content, "<")) == 0)
		return (true);
	if (ft_strncmp(content, "<<", longer(content, "<<")) == 0)
		return (true);
	if (ft_strncmp(content, "<<<", longer(content, "<<<")) == 0)
		return (true);
	return (false);
}

bool	consecutive_delimiters(t_list *token)
{
	t_list	*c;

	c = token;
	while (c && c->next)
	{
		if (is_del(c->content) && is_del(c->next->content))
			return (error_msg(ERR_BASH, ERR_SYNTAX, c->next->content, 0), true);
		if (is_red(c->content) && is_red(c->next->content))
			return (error_msg(ERR_BASH, ERR_SYNTAX, c->next->content, 0), true);
		if (is_red(c->content) && is_del(c->next->content))
			return (error_msg(ERR_BASH, ERR_SYNTAX, c->next->content, 0), true);
		if (ft_strchr(c->content, '*') && ft_strchr(c->next->content, '('))
			return (error_msg(ERR_BASH, ERR_SYNTAX, c->next->content, 0), true);
		if (ft_strchr(c->content, '*') && ft_strchr(c->next->content, ')'))
			return (error_msg(ERR_BASH, ERR_SYNTAX, c->next->content, 0), true);
		if (ft_strncmp(c->content, "&", 2) == 0)
			return (error_msg(ERR_BASH, ERR_EXCL, NULL, NULL), true);
		c = c->next;
	}
	return (false);
}

bool	delimiter_wrong_pos(t_list *token)
{
	t_list	*last;

	last = ft_lstlast(token);
	if ((ft_strncmp(token->content, "|", longer(token->content, "|")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, token->content, NULL), true);
	if ((ft_strncmp(token->content, "||", longer(token->content, "||")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, token->content, NULL), true);
	if ((ft_strncmp(token->content, "&&", longer(token->content, "&&")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, token->content, NULL), true);
	if ((ft_strncmp(last->content, "<<", longer(last->content, "<<")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, last->content, NULL), true);
	if ((ft_strncmp(last->content, "<", longer(last->content, "<")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, last->content, NULL), true);
	if ((ft_strncmp(last->content, ">>", longer(last->content, ">>")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, last->content, NULL), true);
	if ((ft_strncmp(last->content, ">", longer(last->content, ">")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, last->content, NULL), true);
	if ((ft_strncmp(last->content, "&", longer(last->content, "&")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, last->content, NULL), true);
	return (false);
}

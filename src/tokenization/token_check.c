/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:25:56 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/15 16:10:13 by ekashirs         ###   ########.fr       */
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

static bool	is_red_mini(char *content)
{
	if (ft_strncmp(content, ">", longer(content, ">")) == 0)
		return (true);
	if (ft_strncmp(content, ">>", longer(content, ">>")) == 0)
		return (true);
	if (ft_strncmp(content, "<", longer(content, "<")) == 0)
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
	t_list	*curr;

	curr = token;
	while (curr && curr->next)
	{
		if (is_del(curr->content) && is_del(curr->next->content))
			return (error_msg(ERR_BASH, ERR_SYNTAX, curr->next->content, NULL), true);
		if (is_red(curr->content) && is_red(curr->next->content))
			return (error_msg(ERR_BASH, ERR_SYNTAX, curr->next->content, NULL), true);
		if (is_red(curr->content) && is_del(curr->next->content))
			return (error_msg(ERR_BASH, ERR_SYNTAX, curr->next->content, NULL), true);
		if (ft_strchr(curr->content, '*') && ft_strchr(curr->next->content, '('))
			return (error_msg(ERR_BASH, ERR_SYNTAX, curr->next->content, NULL), true);
		if (ft_strchr(curr->content, '*') \
			&& ft_strchr(curr->next->content, ')'))
			return (error_msg(ERR_BASH, ERR_SYNTAX, curr->next->content, NULL), true);
		if (is_red_mini(curr->content) \
			&& ((char *)curr->next->content)[0] == '*')
			return (error_msg(ERR_BASH, "*:", ERR_REDIR, NULL), true);
		if (ft_strncmp(curr->content, "&", 2) == 0)
			return (error_msg(ERR_BASH, ERR_EXCL, NULL, NULL), true);
		curr = curr->next;
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
		return (error_msg(ERR_BASH, ERR_SYNTAX, token->content, NULL), true);
	if ((ft_strncmp(last->content, "<", longer(last->content, "<")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, token->content, NULL), true);
	if ((ft_strncmp(last->content, ">>", longer(last->content, ">>")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, token->content, NULL), true);
	if ((ft_strncmp(last->content, ">", longer(last->content, ">")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, token->content, NULL), true);
	if ((ft_strncmp(last->content, "&", longer(last->content, "&")) == 0))
		return (error_msg(ERR_BASH, ERR_SYNTAX, token->content, NULL), true);
	return (false);
}

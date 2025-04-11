/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:25:56 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/10 10:16:55 by mzhitnik         ###   ########.fr       */
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
			return (error_msg("syntax error near unexpected token `last valid token'", NULL, NULL, NULL), true);
		if (is_red(curr->content) && is_red(curr->next->content))
			return (error_msg("syntax error near unexpected token `last valid token'", NULL, NULL, NULL), true);
		if (is_red(curr->content) && is_del(curr->next->content))
			return (error_msg("syntax error near unexpected token `last valid token'", NULL, NULL, NULL), true);
		if (ft_strchr(curr->content, '*') && ft_strchr(curr->next->content, '('))
			return (error_msg("syntax error near unexpected token `('", NULL, NULL, NULL), true);
		if (ft_strchr(curr->content, '*') \
			&& ft_strchr(curr->next->content, ')'))
			return (error_msg("syntax error near unexpected token `)'", NULL, NULL, NULL), true);
		if (is_red_mini(curr->content) \
			&& ((char *)curr->next->content)[0] == '*')
			return (error_msg("bash: curr->next->content: ambiguous redirect", NULL, NULL, NULL), true);
		if (ft_strncmp(curr->content, "&", 2) == 0)
			return (error_msg("& operator not implemented", NULL, NULL, NULL), true);
		curr = curr->next;
	}
	return (false);
}

bool	delimiter_wrong_pos(t_list *token)
{
	t_list	*last;

	last = ft_lstlast(token);
	if ((ft_strncmp(token->content, "|", longer(token->content, "|")) == 0))
		return (error_msg("syntax error near unexpected token `|'", NULL, NULL, NULL), true);
	if ((ft_strncmp(token->content, "||", longer(token->content, "||")) == 0))
		return (error_msg("syntax error near unexpected token `||'", NULL, NULL, NULL), true);
	if ((ft_strncmp(token->content, "&&", longer(token->content, "&&")) == 0))
		return (error_msg("syntax error near unexpected token `&&'", NULL, NULL, NULL), true);
	if ((ft_strncmp(last->content, "<<", longer(last->content, "<<")) == 0))
		return (error_msg("syntax error near unexpected token `newline'", NULL, NULL, NULL), true);
	if ((ft_strncmp(last->content, "<", longer(last->content, "<")) == 0))
		return (error_msg("syntax error near unexpected token `newline'", NULL, NULL, NULL), true);
	if ((ft_strncmp(last->content, ">>", longer(last->content, ">>")) == 0))
		return (error_msg("syntax error near unexpected token `newline'", NULL, NULL, NULL), true);
	if ((ft_strncmp(last->content, ">", longer(last->content, ">")) == 0))
		return (error_msg("syntax error near unexpected token `newline'", NULL, NULL, NULL), true);
	if ((ft_strncmp(last->content, "&", longer(last->content, "&")) == 0))
		return (error_msg("syntax error near unexpected token `newline'", NULL, NULL, NULL), true);
	return (false);
}

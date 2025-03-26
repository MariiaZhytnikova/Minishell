/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 09:25:56 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/26 10:04:20 by mzhitnik         ###   ########.fr       */
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
	t_list	*curr;

	curr = token;
	while (curr)
	{
		if (is_del(curr->content) && is_del(curr->next->content))
			return (error_msg("syntax error near unexpected token `last valid token'", NULL, NULL), true);
		if (is_red(curr->content) && is_red(curr->next->content))
			return (error_msg("syntax error near unexpected token `last valid token'", NULL, NULL), true);
		if (is_red(curr->content) && is_del(curr->next->content))
			return (error_msg("syntax error near unexpected token `last valid token'", NULL, NULL), true);
		if (ft_strncmp(curr->content, "&", 2) == 0)
			return (error_msg("& operator not implemented", NULL, NULL), true);
		curr = curr->next;
	}
	return (false);
}

bool	delimiter_wrong_pos(t_list *token)
{
	t_list	*last;

	last = ft_lstlast(token);
	if ((ft_strncmp(token->content, "|", longer(token->content, "|")) == 0))
		return (error_msg("syntax error near unexpected token `|'", NULL, NULL), true);
	if ((ft_strncmp(token->content, "||", longer(token->content, "||")) == 0))
		return (error_msg("syntax error near unexpected token `||'", NULL, NULL), true);
	if ((ft_strncmp(token->content, "&&", longer(token->content, "&&")) == 0))
		return (error_msg("syntax error near unexpected token `&&'", NULL, NULL), true);
	if ((ft_strncmp(last->content, "<<", longer(last->content, "<<")) == 0))
		return (error_msg("syntax error near unexpected token `newline'", NULL, NULL), true);
	if ((ft_strncmp(last->content, "<", longer(last->content, "<")) == 0))
		return (error_msg("syntax error near unexpected token `newline'", NULL, NULL), true);
	if ((ft_strncmp(last->content, ">>", longer(last->content, ">>")) == 0))
		return (error_msg("syntax error near unexpected token `newline'", NULL, NULL), true);
	if ((ft_strncmp(last->content, ">", longer(last->content, ">")) == 0))
		return (error_msg("syntax error near unexpected token `newline'", NULL, NULL), true);
	return (false);
}

int	split_and_check(t_list **token, char *src)
{
	char	*input;

	input = add_spaces(src);
	if (!input)
		return (error_msg("Something wrong add_spaces", NULL, NULL), -1);
	if (split_input(token, input, ft_strlen(input)) < 0)
		return (error_msg("Something wrong split_input", NULL, NULL), -1);
	if (delimiter_wrong_pos(*token) == true)
		return (error_msg("Something wrong delimiter_wrong_pos", NULL, NULL), -1);
	if (consecutive_delimiters(*token) == true)
		return (error_msg("Something wrong consecutive_delimiters", NULL, NULL), -1);
	if (here_doc_lim(token) < 0)
		return (error_msg("Herre doc no lim problem", NULL, NULL), -1);
	if (here_doc_no_lim(token) < 0)
		return (error_msg("Herre doc lim problem", NULL, NULL), -1);
	free(input);
	free(src);
	return (1);
}

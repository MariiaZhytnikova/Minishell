/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:08:58 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/25 15:48:13 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_spaces(t_session *session, char *input)
{
	t_temp	thing;

	if (dynstr_init(&thing, input) < 0)
		return (NULL);
	while (input[thing.i])
	{
		if (input[thing.i] == '\n')
			return (free (thing.temp), error_msg(ERR_EXCL, NULL, NULL, NULL), NULL);
		if (input[thing.i] == '$')
		{
			if (expansion(session, &thing, input) < 0)
				return (NULL);
		}
		else if (input[thing.i] == '\'' || input[thing.i] == '\"')
		{
			if (if_quotes(NULL, &thing, input) < 0)
				return (NULL);
		}
		else if (is_delim_or_red(&input[thing.i]))
			copy_delimeter(&thing, input);
		else if (input[thing.i])
			dynstr_append_char(&thing, input);
	}
	thing.temp[thing.j] = 0;
	return (thing.temp);
}

int	split_input(t_session *session, t_list **token, char *args)
{
	t_list	*new_token;
	t_temp	thing;

	if (dynstr_init(&thing, args) < 0)
		return (-1);
	thing.i = skip_whitespace(args);
	if (!args[thing.i])
		return (free (thing.temp), 1);
	if (handle_quotes(session, &thing, args) < 0)
		return (free (thing.temp), -1);
	new_token = ft_lstnew(ft_strdup(thing.temp));
	free (thing.temp);
	if (!new_token)
		return (-2);
	ft_lstadd_back(token, new_token);
	if (args[thing.i])
	{
		if (split_input(session, token, &args[thing.i]) < 0)
			return (-2);
	}
	return (1);
}

int	split_and_check(t_session *session, t_list **token, char *src)
{
	char	*input;
	int		status;

	input = add_spaces(session, src);
	if (!input || !input[0])
		return (-1);
	if (split_input(session, token, input) < 0)
		return (free(input), error_msg(ERR_BASH, ERR_CRASH,
				"split_input", NULL), -1);
	free(input);
	if (delimiter_wrong_pos(*token) == true)
		return (-2);
	if (consecutive_delimiters(*token) == true)
		return (-2);
	status = here_doc_lim(session, token);
	if (status < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "here_doc_lim", NULL), -1);
	if (status == 2 || status == 4)
		return (status);
	status = here_doc_no_lim(session, token);
	if (status < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "here_doc_no_lim", NULL), -1);
	if (status > 0)
		return (status);
	return (1);
}

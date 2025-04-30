/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:08:58 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/30 14:16:16 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*add_spaces(char *in)							// it static, new declaration
{
	t_temp	buf;

	if (dynstr_init(&buf, in) < 0)
		return (NULL);
	while (in[buf.i])
	{
		if (in[buf.i] == '\n' || in[buf.i] == '\\' || in[buf.i] == ';')		// NEW
			return (free (buf.temp), error_msg(ERR_EXCL, 0, 0, 0), NULL);	// NEW
		// if (in[buf.i] == '$')
		// {
		// 	if (expansion(session, &buf, in) < 0)
		// 		return (NULL);
		// }

		// FREE buf.temp ??????????
		else if (in[buf.i] == '\'' || in[buf.i] == '\"')
		{
			if (if_quotes(NULL, &buf, in) < 0)
				return (free(buf.temp), NULL);
		}
		else if (is_delim_or_red(&in[buf.i]))
		{
			if (copy_delimeter(&buf, in) < 0)
				return (free(buf.temp), NULL);
		}
		else if (in[buf.i])
		{
			if (dynstr_append_char(&buf, in) < 0)
				return (free(buf.temp), NULL);
		}
	}
	buf.temp[buf.j] = 0;
	return (buf.temp);
}

static int	split_input(t_session *session, t_list **token, char *args)
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

	input = add_spaces(src); // NEW CALL
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
		return (-1);
	if (status == 2 || status == 4)
		return (status);
	status = here_doc_no_lim(session, token);
	if (status < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "here_doc_no_lim", NULL), -1);
	if (status > 0)
		return (status);
	return (1);
}

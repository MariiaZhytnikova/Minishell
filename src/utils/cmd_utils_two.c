/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_utils_two.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 16:31:53 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/11 15:02:57 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	check_two(char *str, int i)
{
	if ((ft_strlen(str) >= 2 && str[i] == '|' && str[i + 1] == '|')
		|| (ft_strlen(str) >= 2 && str[i] == '&' && str[i + 1] == '&')
		|| (ft_strlen(str) >= 2 && str[i] == '<' && str[i + 1] == '<')
		|| (ft_strlen(str) >= 2 && str[i] == '>' && str[i + 1] == '>'))
		return (true);
	return (false);
}

int	copy_delimeter(t_temp *thing, char *str)
{
	if (ft_strlen(str) >= 3 && str[thing->i] == '<' && str[thing->i + 1] == '<'
		&& str[thing->i + 2] == '<')
	{
		if (dynstr_symb(thing, ' ') == -1 || dynstr_char(thing, str) == -1
			|| dynstr_char(thing, str) == -1 || dynstr_char(thing, str) == -1
			|| dynstr_symb(thing, ' ') == -1)
			return (-1);
	}
	else if (check_two(str, thing->i) == true)
	{
		if (dynstr_symb(thing, ' ') == -1 || dynstr_char(thing, str) == -1
			|| dynstr_char(thing, str) == -1 || dynstr_symb(thing, ' ') == -1)
			return (-1);
	}
	else if (str[thing->i] == '|' || str[thing->i] == '&'
		|| str[thing->i] == '<' || str[thing->i] == '>')
	{
		if (dynstr_symb(thing, ' ') == -1 || dynstr_char(thing, str) == -1
			|| dynstr_symb(thing, ' ') == -1)
			return (-1);
	}
	return (0);
}

int	status(t_session *session, t_temp *thing)
{
	char	*status_str;

	status_str = ft_itoa(session->status_last);
	if (!status_str)
		return (-1);
	thing->i += 2;
	if (dynstr_str(thing, status_str) < 0)
	{
		free(status_str);
		return (-1);
	}
	free(status_str);
	return (1);
}

int	replace_token(t_list *current, char *buffer)
{
	free(current->content);
	current->content = ft_strdup("<<<");
	if (!current->content)
		return (free(buffer), -1);
	if (!buffer || !buffer[0])
		buffer = ft_calloc(1, sizeof(char));
	if (!buffer)
		return (-1);
	free(current->next->content);
	current->next->content = ft_strdup(buffer);
	free(buffer);
	if (!current->next->content)
		return (-1);
	return (1);
}

int	copy_args(t_command *cmd, t_list **args)
{
	cmd->args = list_to_arr(*args);
	ft_lstclear(args, free);
	if (!cmd->args)
		return (-1);
	*args = NULL;
	return (1);
}

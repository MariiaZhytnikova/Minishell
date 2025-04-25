/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delimiters.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/22 14:09:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/25 15:35:41 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	is_delim_or_red(char *str)
{
	if (ft_strlen(str) >= 3 && str[0] == '<' && str[1] == '<' && str[2] == '<')
		return (true);
	if (ft_strlen(str) >= 2 && str[0] == '|' && str[1] == '|')
		return (true);
	if (ft_strlen(str) >= 2 && str[0] == '&' && str[1] == '&')
		return (true);
	if (ft_strlen(str) >= 2 && str[0] == '<' && str[1] == '<')
		return (true);
	if (ft_strlen(str) >= 2 && str[0] == '>' && str[1] == '>')
		return (true);
	if (str[0] == '|')
		return (true);
	if (str[0] == '&')
		return (true);
	if (str[0] == '<')
		return (true);
	if (str[0] == '>')
		return (true);
	return (false);
}

static bool	check_two(char *str, int i)
{
	if ((ft_strlen(str) >= 2 && str[i] == '|' && str[i + 1] == '|')
		|| (ft_strlen(str) >= 2 && str[i] == '&' && str[i + 1] == '&')
		|| (ft_strlen(str) >= 2 && str[i] == '<' && str[i + 1] == '<')
		|| (ft_strlen(str) >= 2 && str[i] == '>' && str[i + 1] == '>'))
		return (true);
	return (false);
}

void	copy_delimeter(t_temp *thing, char *str)
{
	if (ft_strlen(str) >= 3 && str[thing->i] == '<' && str[thing->i + 1] == '<'
		&& str[thing->i + 2] == '<')
	{
		thing->temp[thing->j++] = ' ';
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = ' ';
	}
	else if (check_two(str, thing->i) == true)
	{
		thing->temp[thing->j++] = ' ';
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = ' ';
	}
	else if (str[thing->i] == '|' || str[thing->i] == '&'
		|| str[thing->i] == '<' || str[thing->i] == '>')
	{
		thing->temp[thing->j++] = ' ';
		thing->temp[thing->j++] = str[thing->i++];
		thing->temp[thing->j++] = ' ';
	}
}

int	get_redirection(t_command *command, t_list *current)
{
	if (files(command, current) < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "files", NULL), -1);
	if (redirection_in(command, current) < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "redirection_in", NULL), -1);
	if (redirection_out(command, current) < 0)
		return (error_msg(ERR_BASH, ERR_CRASH, "redirection_OUT", NULL), -1);
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

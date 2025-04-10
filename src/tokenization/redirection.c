/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:12:52 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/10 15:32:13 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	array_size(char **array)
{
	int	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

int	redirection_in(t_command *command, t_list *current)
{
	int	size;

	if ((ft_strncmp(current->content, "<", \
		longer(current->content, "<")) == 0))
	{
		size = array_size(command->in);
		command->in[size] = ft_strdup(current->next->content);
		if (!command->in[size])
			return (-1);
	}
	if ((ft_strncmp(current->content, "<<<", \
		longer(current->content, "<<<")) == 0))
	{
		size = array_size(command->h_doc);
		command->h_doc[size] = ft_strdup(current->next->content);
		if (!command->h_doc[size])
			return (-1);
	}
	return (1);
}

int	redirection_out(t_command *command, t_list *current)
{
	int	size;

	if ((ft_strncmp(current->content, ">", \
		longer(current->content, ">")) == 0))
	{
		size = array_size(command->out);
		command->out[size] = ft_strdup(current->next->content);
		if (!command->out[size])
			return (-1);
	}
	if ((ft_strncmp(current->content, ">>", \
		longer(current->content, ">>")) == 0))
	{
		size = array_size(command->out_app);
		command->out_app[size] = ft_strdup(current->next->content);
		if (!command->out_app[size])
			return (-1);
	}
	return (1);
}

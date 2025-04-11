/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:12:52 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/10 17:19:17 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	array_size(char **array)
{
	int	size;

	size = 0;
	while (array[size])
		size++;
	return (size);
}

static int	replase_last_in(t_command *command, t_list *current)
{
	if (command->last_in->name)
		free(command->last_in->name);
	command->last_in->name = ft_strdup(current->next->content);
	if (!command->last_in->name)
		return (error_msg("ft_strdup in replase_last_in\n", NULL, NULL, NULL), -1);
	return (1);
}

static int	replase_last_out(t_command *command, t_list *current)
{
	if (command->last_out->name)
		free(command->last_out->name);
	command->last_out->name = ft_strdup(current->content);
	if (!command->last_out->name)
		return (error_msg("ft_strdup in replase_last_out\n", NULL, NULL, NULL), -1);
	return (1);
}

int	redirection_in(t_command *command, t_list *current)
{
	int	size;

	if ((ft_strncmp(current->content, "<", \
		longer(current->content, "<")) == 0))
	{
		command->last_in->type = IN_FILE;
		if (replase_last_in(command, current) < 0)
			return (-1);
		size = array_size(command->in);
		command->in[size] = ft_strdup(current->next->content);
		if (!command->in[size])
			return (-1);
	}
	else if ((ft_strncmp(current->content, "<<<", \
		longer(current->content, "<<<")) == 0))
	{
		command->last_in->type = HERE_DOC;
		if (replase_last_in(command, current) < 0)
			return (-1);
		size = array_size(command->h_doc);
		command->h_doc[size] = NULL;
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
		command->last_out->type = OUT_FILE;
		if (replase_last_out(command, current) < 0)
			return (-1);
		size = array_size(command->out);
		command->out[size] = ft_strdup(current->next->content);
		if (!command->out[size])
			return (-1);
	}
	else if ((ft_strncmp(current->content, ">>", \
		longer(current->content, ">>")) == 0))
	{
		command->last_out->type = OUT_APPEND;
		if (replase_last_out(command, current) < 0)
			return (-1);
		size = array_size(command->out_app);
		command->out_app[size] = ft_strdup(current->next->content);
		if (!command->out_app[size])
			return (-1);
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:12:52 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/22 11:31:16 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	replase_last_in(t_command *command, t_list *current)
{
	if (command->last_in->name)
		free(command->last_in->name);
	command->last_in->name = ft_strdup(current->next->content);
	if (!command->last_in->name)
		return (-1);
	return (1);
}

static int	replase_last_out(t_command *command, t_list *current)
{
	if (command->last_out->name)
		free(command->last_out->name);
	command->last_out->name = ft_strdup(current->next->content);
	if (!command->last_out->name)
		return (-1);
	return (1);
}

int	redirection_in(t_command *command, t_list *current)
{
	if ((ft_strncmp(current->content, "<",
				longer(current->content, "<")) == 0))
	{
		command->last_in->type = IN_FILE;
		if (replase_last_in(command, current) < 0)
			return (-1);
	}
	if ((ft_strncmp(current->content, "<<<",
				longer(current->content, "<<<")) == 0))
	{
		command->last_in->type = HERE_DOC;
		if (replase_last_in(command, current) < 0)
			return (-1);
	}
	return (1);
}

int	redirection_out(t_command *command, t_list *current)
{
	if ((ft_strncmp(current->content, ">",
				longer(current->content, ">")) == 0))
	{
		command->last_out->type = OUT_FILE;
		if (replase_last_out(command, current) < 0)
			return (-1);
	}
	if ((ft_strncmp(current->content, ">>",
				longer(current->content, ">>")) == 0))
	{
		command->last_out->type = OUT_APPEND;
		if (replase_last_out(command, current) < 0)
			return (-1);
	}
	return (1);
}

int	files(t_command *command, t_list *curr)
{
	int	size;

	size = array_size(command->files);
	if (ft_strncmp(curr->content, "<", longer(curr->content, "<")) == 0)
	{
		command->files[size]->type = IN_FILE;
		command->files[size]->name = ft_strdup(curr->next->content);
		if (!command->files[size]->name)
			return (-1);
	}
	if (ft_strncmp(curr->content, ">", longer(curr->content, ">")) == 0)
	{
		command->files[size]->type = OUT_FILE;
		command->files[size]->name = ft_strdup(curr->next->content);
		if (!command->files[size]->name)
			return (-1);
	}
	if (ft_strncmp(curr->content, ">>", longer(curr->content, ">>")) == 0)
	{
		command->files[size]->type = OUT_APPEND;
		command->files[size]->name = ft_strdup(curr->next->content);
		if (!command->files[size]->name)
			return (-1);
	}
	return (1);
}

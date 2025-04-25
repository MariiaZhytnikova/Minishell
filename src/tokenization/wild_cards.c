/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:46:24 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/25 15:33:30 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	copy_file_name(char *name, t_list **args, int *count)
{
	char	*temp;
	t_list	*new;

	new = NULL;
	(*count)++;
	temp = ft_strdup(name);
	if (create_new(args, new, temp) < 0)
		return (-1);
	free(temp);
	return (1);
}

int	skip_quotes_ast(char *pattern, t_list **args, int count, t_list *new)
{
	struct dirent	*entry;
	DIR				*stream;

	stream = opendir(".");
	if (!stream)
		return (error_msg(ERR_BASH, ERR_DIR, "'.'", ERR_PE), -1);
	entry = readdir(stream);
	while (entry)
	{
		if (match(entry->d_name, pattern) == true)
		{
			if (entry->d_name[0] != '.')
			{
				if (copy_file_name(entry->d_name, args, &count) < 0)
					return (-1);
			}
		}
		entry = readdir(stream);
	}
	closedir(stream);
	if (count == 0)
		if (create_new(args, new, pattern) < 0)
			return (-1);
	return (1);
}

static int	wild_check(char *arg, t_list **args)
{
	t_list	*new;
	int		count;

	count = 0;
	new = NULL;
	if (ft_strchr(arg, '*') && !is_in_quotes(arg))
	{
		if (skip_quotes_ast(arg, args, count, new) < 0)
			return (-1);
	}
	else
		if (create_new(args, new, arg) < 0)
			return (-1);
	return (1);
}

int	wild(t_session *session)
{
	t_list	*args;
	int		id;
	int		i;

	id = 0;
	args = NULL;
	while (id < session->count->cmd_nb)
	{
		i = 0;
		while (session->cmds[id]->args[i])
		{
			if (wild_check(session->cmds[id]->args[i], &args) < 0)
				return (-1);
			i++;
		}
		free_arr(session->cmds[id]->args);
		session->cmds[id]->args = list_to_arr(args);
		ft_lstclear(&args, free);
		id++;
	}
	return (1);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:46:24 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/15 16:16:59 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	skip_quotes_ast(char *pattern, t_list **args)
{
	struct dirent	*entry;
	DIR				*stream;
	t_list			*new;
	int				count;

	count = 0;
	stream = opendir(".");
	if (!stream)
		return (error_msg(ERR_BASH, ERR_DIR, "'.'", ERR_PERM), -1);
	entry = readdir(stream);
	while (entry)
	{
		if (match(entry->d_name, pattern) == true)
		{
			count++;
			printf("FILE NAME IS %s\n", entry->d_name);
			if (create_new(args, new, ft_strdup(entry->d_name)) < 0)
				return (-1);
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

	if (ft_strchr(arg, '*') && !is_in_quotes(arg))
	{
		if (skip_quotes_ast(arg, args) < 0)
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

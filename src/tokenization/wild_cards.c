/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild_cards.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 10:46:24 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/05/07 13:43:47 by mzhitnik         ###   ########.fr       */
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

int	wild(t_list **exp_red)
{
	t_list	*args;
	t_list	*current;

	current = *exp_red;
	args = NULL;
	while (current)
	{
		if (wild_check(current->content, &args) < 0)
			return (-1);
		current = current->next;
	}
	ft_lstclear(exp_red, free);
	*exp_red = args;
	return (1);
}

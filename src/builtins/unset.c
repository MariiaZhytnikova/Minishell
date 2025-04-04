/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:17 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/02 11:24:39 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*search_in_env(t_list *env_var, char *variable)
{
	size_t	len;
	t_list	*current;

	if (env_var == NULL)
		return (NULL);
	current = env_var;
	len = ft_strlen(variable);
	while (current)
	{
		if (!ft_strncmp(current->content, variable, len)
			&& ((char *)current->content)[len] == '=')
			return (current);
		current = current->next;
	}
	return (NULL);
}

void	unset_builtin(t_session *session, t_command *cmd)
{
	t_list	*var_to_unset;
	t_list	*tmp;
	int		i;

	if (!cmd->args || !cmd->args[1])
	{
		cmd->status = EXIT_SUCCESS;
		return ;
	}
	i = 1;
	while (cmd->args[i])
	{
		tmp = session->env_var;
		var_to_unset = search_in_env(tmp, cmd->args[i]);
		if (var_to_unset)
			delete_node_by_content(&(session->env_var), cmd->args[i]);
		i++;
	}
	cmd->status = EXIT_SUCCESS;
}

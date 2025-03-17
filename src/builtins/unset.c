/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:17 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/17 17:23:12 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	unset_builtin(t_command *cmd)
{
	t_list	*var_to_unset;
	int		i;

	if	(!cmd->args[0])
	{
		cmd->status = EXIT_SUCCESS;
		return ;
	}
	i = 0;
	while (cmd->args[i])
	{
		var_to_unset = search_in_env(cmd->envp, cmd->args[i]);
		if (var_to_unset == NULL)
		{
			cmd->status = EXIT_SUCCESS;
			return ;
		}
		else
			delete_node();
	}
}
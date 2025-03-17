/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:32 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/17 16:48:31 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_command *cmd)
{
	t_list	*current;

	if(cmd->args[0])
	{
		error_msg (ERR_ENV, cmd->args[0], ERR_NOFILE);
		cmd->status = EXIT_FAILURE;
		return ;
	}
	current = cmd->envp;
	while(current)
	{
		if(ft_strchr(current->content, '='))
			printf("%s\n", current->content);
		current = current->next;
	}
	cmd->status = EXIT_SUCCESS;
}
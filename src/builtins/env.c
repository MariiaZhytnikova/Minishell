/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:32 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/25 15:00:45 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_session *session, t_command *cmd)
{
	if (cmd->args[1])
	{
		error_msg (ERR_ENV, cmd->args[1], ERR_NOFILE, NULL);
		cmd->status = EXIT_FAILURE;
		return ;
	}
	print_linked_list(session->env_var);
	cmd->status = EXIT_SUCCESS;
}

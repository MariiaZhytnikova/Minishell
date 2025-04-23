/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:32 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/23 13:27:20 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_session *session, t_command *cmd)
{
	if (cmd->args[1])
	{
		error_msg (ERR_ENV, cmd->args[1], ERR_NO, NULL);
		cmd->status = EXIT_FAILURE;
		return ;
	}
	print_linked_list(session->env_var);
	cmd->status = EXIT_SUCCESS;
}

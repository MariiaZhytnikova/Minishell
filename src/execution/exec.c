/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:17:38 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/26 15:30:45 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec(t_session *session)
{
	if (!strcmp((*session->cmds)->command, "exit"))
		exit_builtin(session, *session->cmds);
	else if (!strcmp((*session->cmds)->command,"cd"))
		cd_builtin(session, *session->cmds);
	else if (!strcmp((*session->cmds)->command, "env"))
		env_builtin(session, *session->cmds);
	else if (!strcmp((*session->cmds)->command, "pwd"))
		pwd_builtin(*session->cmds);
	else if (!strcmp((*session->cmds)->command, "unset"))
		unset_builtin(session, *session->cmds);
	else if (!strcmp((*session->cmds)->command, "echo"))
		echo_builtin(*session->cmds);
	else if (!strcmp((*session->cmds)->command, "export"))
		export_builtin(session , *session->cmds);
	return (0);
}
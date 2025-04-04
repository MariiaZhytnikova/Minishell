/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 15:14:49 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/24 14:23:20 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pwd_builtin(t_command *cmd)
{
	char	cur_dir[LEN_PATH];

	if (!getcwd(cur_dir, LEN_PATH))
	{
		error_msg(ERR_GETCWD, ERR_NOFILE, NULL, NULL);
		cmd->status = EXIT_FAILURE;
	}
	else
	{
		cmd->status = EXIT_SUCCESS;
		printf("%s\n", cur_dir);
	}
}

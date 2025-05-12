/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 13:36:00 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/12 12:52:25 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_env_value(t_list *env_var, char *variable)
{
	t_list	*node;
	size_t	len;

	node = search_in_env(env_var, variable);
	if (!node)
		return (NULL);
	len = ft_strlen(variable);
	return (((char *)node->content) + len + 1);
}

void	cd_no_path(t_session *session, t_command *cmd)
{
	char	*home;

	home = get_env_value(session->env_var, "HOME");
	if (!home)
	{
		error_msg(ERR_CD, ERR_HOME, NULL, NULL);
		cmd->status = 1;
		return ;
	}
	if (chdir(home) == -1)
	{
		error_msg(ERR_CD, home, ": ", strerror(errno));
		cmd->status = 1;
		return ;
	}
	update_env(session->env_var, cmd);
}

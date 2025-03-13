/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:17:32 by ekashirs          #+#    #+#             */
/*   Updated: 2025/03/13 17:07:38 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	env_builtin(t_command *cmd)
{
	int	i;

	i = 0;
	while(cmd->envp[i])
	{
		if(ft_strchr(cmd->envp[i], '='))
			printf("%s\n", cmd->envp[i]);
		i++;
	}
	cmd->status = EXIT_SUCCESS;
}
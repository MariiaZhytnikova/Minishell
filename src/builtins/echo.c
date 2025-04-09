/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:16:47 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/08 18:40:38 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(t_command *cmd)
{
	bool	n_flag;
	int		i;

	n_flag = false;
	i = 1;
	if (cmd->args[i] && !(ft_strncmp(cmd->args[i], "-n", 2))
		&& ft_strlen(cmd->args[i]) == 2)
	{
		n_flag = true;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[++i])
			printf(" ");
	}
	if (n_flag == false || cmd->args[1] == NULL)
		printf("\n");
	cmd->status = 0;
}

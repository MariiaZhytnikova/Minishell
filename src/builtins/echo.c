/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 14:16:47 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/25 12:46:14 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_builtin(t_command *cmd)
{
	bool	n_flag;
	int		i;
	int		j;

	n_flag = false;
	i = 1;
	while (cmd->args[i] && !ft_strncmp(cmd->args[i], "-n", 2))
	{
		j = 2;
		while (cmd->args[i][j] == 'n')
			j++;
		if (cmd->args[i][j] != '\0')
			break ;
		n_flag = true;
		i++;
	}
	while (cmd->args[i])
	{
		printf("%s", cmd->args[i]);
		if (cmd->args[++i])
			printf(" ");
	}
	if (!n_flag)
		printf("\n");
	cmd->status = 0;
}

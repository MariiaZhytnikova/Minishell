/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:11:29 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/22 14:39:48 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	num_pipes(t_session *session, int *id)
{
	int	count;
	int	i;

	i = *id;
	count = 0;
	while (session->cmds[i]->type == PIPE)
	{
		i++;
		count++;
	}
	return (count);
}

void	group_free(t_session *session)
{
	ft_lstclear(&session->env_var, free);
	rl_clear_history();
	free_session(session);
}

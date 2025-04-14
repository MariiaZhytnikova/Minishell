/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:11:29 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/14 15:12:00 by ekashirs         ###   ########.fr       */
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

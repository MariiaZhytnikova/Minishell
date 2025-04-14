/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:02:06 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/13 19:59:14 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_and(t_session *session, int *id)
{
	if (session->cmds[*id - 1]->status == 0)
		exec(session, id);
	else if (session->cmds[*id - 1]->status != 0)
		session->cmds[(*id)++]->status = session->cmds[*id - 1]->status;
}

void	run_or(t_session *session, int *id)
{
	if (session->cmds[*id - 1]->status != 0)
		exec(session, id);
	else
		session->cmds[(*id)++]->status = 0;
}

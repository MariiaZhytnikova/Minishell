/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   and_or.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 11:02:06 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/12 11:46:16 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_and(t_session *session, int *id)
{
	if (session->cmds[*id - 1]->status == 0)
		run_pipe(session, id);
	else if (session->cmds[*id - 1]->status != 0)
		session->cmds[(*id)++]->status = session->cmds[*id - 1]->status;
}

void	run_or(t_session *session, int *id)
{
	if (session->cmds[*id - 1]->status != 0)
		run_pipe(session, id);
	else
		session->cmds[(*id)++]->status = 0;
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:19:54 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/21 18:51:14 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

void	handle_in_out(t_session *session, t_command *cmd);
int		open_files(t_session *session, t_command *cmd, int ind);
void	run_and(t_session *session, int *id);
void	run_or(t_session *session, int *id);
void	run_pipe(t_session *session, int *id);

void	exec_norm(t_session *session, t_command *cmd);
void	run_cmd(t_session *session, t_command *cmd);
void	exec(t_session *session, int *id);

#endif
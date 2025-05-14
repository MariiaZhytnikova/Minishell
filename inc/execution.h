/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:19:54 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/14 17:04:53 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTION_H
# define EXECUTION_H

# include "minishell.h"

int		handle_in_out(t_command *cmd);
int		open_files(t_command *cmd);
int		is_directory(const char *path);

void	run_and(t_session *session, int *id);
void	run_or(t_session *session, int *id);
void	run_pipe(t_session *session, int *id);

void	exec_norm(t_session *session, t_command *cmd);
void	run_cmd(t_session *session, t_command *cmd);
void	exec(t_session *session, int *id);

#endif
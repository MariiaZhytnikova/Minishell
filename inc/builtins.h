/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:34:31 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/07 15:21:00 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

# include "minishell.h"

void	cd_builtin(t_session *session, t_command *cmd);
void	env_builtin(t_session *session, t_command *cmd);
void	exit_builtin(t_session *session, t_command *cmd);
void	pwd_builtin(t_command *cmd);
void	unset_builtin(t_session *session, t_command *cmd);
void	echo_builtin(t_command *cmd);
void	export_builtin(t_session *session, t_command *cmd);
void	handle_args(t_session *session, t_command *cmd);
t_list	*search_in_env(t_list *env_var, char *variable);
void	append_env(t_session *session, t_command *cmd, char *var);
int		check_for_plus(char *var);
void	cd_no_path(t_session *session, t_command *cmd);
void	update_env(t_list *env_var, t_command *cmd);

#endif
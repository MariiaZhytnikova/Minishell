/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 11:34:31 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/22 10:06:53 by mzhitnik         ###   ########.fr       */
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

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:07:40 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/14 15:13:50 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

#ifndef SIGNALS_H
# define SIGNALS_H

extern sig_atomic_t	signalnum;

void	exit_signal(t_session *session, int code);
void	setup_signals(int mode);
void	handle_sigint(int signal);
void	handle_signal_status(t_session *s, int pid, int status, int *si, int *sq);

#endif
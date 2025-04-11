/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:07:40 by ekashirs          #+#    #+#             */
/*   Updated: 2025/04/07 15:35:03 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

#ifndef SIGNALS_H
# define SIGNALS_H

extern sig_atomic_t	signalnum;

void	setup_signals();
void	exit_signal(t_session *session, int code);
void	setup_heredoc_signals();

#endif
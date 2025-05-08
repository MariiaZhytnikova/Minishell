/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 16:07:40 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/08 19:31:38 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SIGNALS_H
# define SIGNALS_H

# include "minishell.h"

extern sig_atomic_t	g_signalnum;

typedef struct s_flags
{
	int	sigint_printed;
	int	sigquit_printed;
}	t_flags;

void	setup_signals(int mode);
void	handle_sigint(int signal);
void	handle_signal_status(t_session *s, int pid, int status, t_flags *flags);

#endif
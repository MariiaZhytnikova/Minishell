/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:24:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/09 17:18:10 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *msg)
{
	int	msg_len;

	msg_len = 0;
	while (msg[msg_len++]);
	write(2, msg, msg_len);
	write(2, "\n", 1);
}
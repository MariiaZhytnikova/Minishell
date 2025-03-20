/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:24:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/20 14:57:52 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *start, char *details, char *c, char *error)
{
	if (start)
		write(2, start, ft_strlen(start));
	if (details)
		write(2, details, ft_strlen(details));
	if (c)
		write(2, c, ft_strlen(c));
	if (error)
		write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

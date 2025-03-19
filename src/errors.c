/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 14:24:22 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/03/19 13:28:40 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error_msg(char *beginning, char *details, char *error)
{
	if (beginning)
		write(2, beginning, ft_strlen(beginning));
	if (details)
		write(2, details, ft_strlen(details));
	if (error)
		write(2, error, ft_strlen(error));
	write(2, "\n", 1);
}

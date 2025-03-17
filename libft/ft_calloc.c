/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/09 18:26:18 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/15 12:13:14 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdint.h>

void	*ft_calloc(size_t num, size_t size)
{
	size_t			byte_size;
	size_t			i;
	unsigned char	*object;

	if (size != 0 && num > (SIZE_MAX / size))
		return (NULL);
	byte_size = num * size;
	if (byte_size == 0)
		return (NULL);
	object = malloc(byte_size);
	if (!object)
		return (NULL);
	i = 0;
	while (i < byte_size)
	{
		object[i] = 0;
		i++;
	}
	return ((void *)object);
}

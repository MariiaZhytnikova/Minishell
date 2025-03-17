/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 17:45:47 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/16 11:54:41 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dest_l;
	size_t	src_l;

	if (!dst)
		dest_l = 0;
	else
		dest_l = ft_strlen(dst);
	src_l = ft_strlen(src);
	if (size <= dest_l)
		return (src_l + size);
	i = 0;
	while ((dest_l + i) < (size - 1) && src[i] != '\0')
	{
		dst[dest_l + i] = src[i];
		i++;
	}
	dst[dest_l + i] = '\0';
	return (dest_l + src_l);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 21:04:10 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/12 18:37:06 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_compare(char *str, char *to_find, size_t i, size_t len)
{
	size_t	j;

	j = 0;
	while (to_find[j] != '\0' && i + j < len)
	{
		if (to_find[j] != str[i + j])
			return (0);
		j++;
	}
	return (to_find[j] == '\0');
}

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	size_t	i;
	char	*d;
	char	*s;

	if (!str || !to_find)
		return (NULL);
	d = (char *)str;
	s = (char *)to_find;
	if (s[0] == '\0')
		return (d);
	i = 0;
	while (d[i] != '\0')
	{
		if (ft_compare(d, s, i, len) == 1)
			return (&d[i]);
		i++;
	}
	return (NULL);
}

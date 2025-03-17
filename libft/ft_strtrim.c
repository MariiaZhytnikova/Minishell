/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:48:56 by yuritkachen       #+#    #+#             */
/*   Updated: 2025/02/15 13:26:52 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_find(char *charset, char to_find)
{
	while (*charset)
	{
		if (*charset == to_find)
			return (1);
		charset++;
	}
	return (0);
}

static size_t	ft_first(char *str, char *set)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0' && ft_find(set, str[i]))
		i++;
	return (i);
}

static unsigned int	ft_last(char *str, char *set)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	if (i == 0)
		return (0);
	i--;
	while (i > 0 && ft_find(set, str[i]))
		i--;
	return (i);
}

char	*ft_strtrim(char const *str, char const *set)
{
	size_t	first;
	size_t	last;
	size_t	i;
	size_t	len;
	char	*res;

	if (!str || !set)
		return (NULL);
	first = ft_first((char *)str, (char *)set);
	last = ft_last((char *)str, (char *)set);
	if (first > last)
		len = 0;
	else
		len = last - first + 1;
	res = (char *)ft_calloc((len + 1), sizeof(char));
	if (res == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		res[i] = str[first + i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

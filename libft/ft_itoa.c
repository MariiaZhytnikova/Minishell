/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/02 20:48:56 by yuritkachen       #+#    #+#             */
/*   Updated: 2025/02/15 13:22:48 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	ft_rec(int num, char *str, int *i)
{
	if (num >= 10)
		ft_rec(num / 10, str, i);
	str[(*i)++] = (num % 10 + '0');
}

char	*ft_itoa(int num)
{
	int		i;
	char	*str;

	i = 0;
	str = (char *)ft_calloc(12, sizeof(char));
	if (str == NULL)
		return (NULL);
	else if (num == -2147483648)
	{
		ft_strlcpy(str, "-2147483648", 12);
		return (str);
	}
	if (num < 0)
	{
		str[i++] = '-';
		num = -num;
	}
	ft_rec(num, str, &i);
	str[i] = '\0';
	return (str);
}

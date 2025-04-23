/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_two.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 16:33:30 by mzhitnik          #+#    #+#             */
/*   Updated: 2025/04/22 14:38:36 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

void	*reall(void *ptr, size_t old_size, size_t new_size)
{
	void	*new_ptr;
	size_t	copy_size;

	if (new_size == 0)
		return (free(ptr), NULL);
	if (!ptr)
		return (ft_calloc(new_size, sizeof(char)));
	new_ptr = ft_calloc(new_size, sizeof(char));
	if (new_ptr == NULL)
		return (NULL);
	if (old_size > new_size)
		copy_size = new_size;
	else
		copy_size = old_size;
	ft_memcpy(new_ptr, ptr, copy_size);
	free(ptr);
	return (new_ptr);
}

int	array_size(t_file **array)
{
	int	size;

	if (!array || !*array)
		return (0);
	size = 0;
	while (array[size]->name)
		size++;
	return (size);
}

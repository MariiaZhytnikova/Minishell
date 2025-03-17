/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mzhitnik <mzhitnik@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 12:38:39 by mzhitnik          #+#    #+#             */
/*   Updated: 2024/11/30 17:46:18 by mzhitnik         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	read_from_file(char **big_buffer, int fd)
{
	char	*buff;
	char	*temp;
	int		bytes_read;

	buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (!buff)
		return ;
	bytes_read = 1;
	while (bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buff);
			return ;
		}
		buff[bytes_read] = 0;
		temp = ft_strjoin(*big_buffer, buff);
		free(*big_buffer);
		*big_buffer = temp;
		if (ft_strchr(buff, '\n'))
			break ;
	}
	free(buff);
}

static void	ft_line_res(char **big_buffer, char **line, size_t line_len)
{
	char	*next;
	size_t	i;

	*line = ft_calloc(line_len + 2, sizeof(char));
	if (!(*line))
		return ;
	i = 0;
	while (i < line_len)
	{
		(*line)[i] = (*big_buffer)[i];
		i++;
	}
	if ((*big_buffer)[i] == '\n')
		(*line)[i++] = '\n';
	(*line)[i] = '\0';
	if ((*big_buffer)[i])
	{
		next = ft_strjoin(*big_buffer + i, "");
		free(*big_buffer);
		*big_buffer = next;
		return ;
	}
	free(*big_buffer);
	*big_buffer = NULL;
}

char	*get_next_line(int fd)
{
	static char	*big_buffer;
	char		*line;
	size_t		line_len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!big_buffer)
		big_buffer = ft_calloc(1, sizeof (char));
	if (!big_buffer)
		return (NULL);
	if (!ft_strchr(big_buffer, '\n'))
		read_from_file(&big_buffer, fd);
	if (!big_buffer || !*big_buffer)
	{
		free(big_buffer);
		big_buffer = NULL;
		return (NULL);
	}
	line_len = 0;
	while (big_buffer[line_len] && big_buffer[line_len] != '\n')
		line_len++;
	line = NULL;
	ft_line_res(&big_buffer, &line, line_len);
	return (line);
}

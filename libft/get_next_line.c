/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekashirs <ekashirs@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/02 14:08:16 by ekashirs          #+#    #+#             */
/*   Updated: 2025/05/12 13:44:44 by ekashirs         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_append_to_buffer(char **buffer, char *tmp_buff)
{
	char	*tmp_line;

	tmp_line = ft_strjoin(*buffer, tmp_buff);
	if (tmp_line == NULL)
	{
		free(tmp_buff);
		free(*buffer);
		*buffer = NULL;
		return (1);
	}
	free(*buffer);
	*buffer = tmp_line;
	return (0);
}

void	ft_read_line(char **buffer, int fd)
{
	char	*tmp_buff;
	int		bytes;

	tmp_buff = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (tmp_buff == NULL)
		return ;
	bytes = 1;
	while (bytes > 0)
	{
		bytes = read(fd, tmp_buff, BUFFER_SIZE);
		if (bytes < 0)
		{
			free(tmp_buff);
			return ;
		}
		tmp_buff[bytes] = '\0';
		if (ft_append_to_buffer(buffer, tmp_buff))
			return ;
		if (ft_strchr(tmp_buff, '\n'))
			break ;
	}
	free(tmp_buff);
}

static void	ft_remaining_data(char **buffer, size_t i, char **line)
{
	char	*remaining_data;

	if ((*buffer)[i])
	{
		remaining_data = ft_strjoin(*buffer + i, "");
		if (remaining_data == NULL)
		{
			free(*buffer);
			*buffer = NULL;
			free(line);
			return ;
		}
		free(*buffer);
		*buffer = remaining_data;
		return ;
	}
	free(*buffer);
	*buffer = NULL;
}

void	ft_extract_line(char **buffer, char **line, size_t len)
{
	size_t	i;

	*line = ft_calloc(len + 2, sizeof(char));
	if (!(*line))
	{
		free(*buffer);
		*buffer = NULL;
		return ;
	}
	i = 0;
	while (i < len)
	{
		(*line)[i] = (*buffer)[i];
		i++;
	}
	if ((*buffer)[i] == '\n')
		(*line)[i++] = '\n';
	(*line)[i] = '\0';
	ft_remaining_data(buffer, i, line);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;
	size_t		len;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer)
		buffer = ft_calloc(1, sizeof (char));
	if (!buffer)
		return (NULL);
	if (!ft_strchr(buffer, '\n'))
		ft_read_line(&buffer, fd);
	if (!buffer || !*buffer)
	{
		free(buffer);
		buffer = NULL;
		return (NULL);
	}
	len = 0;
	while (buffer[len] != '\n' && buffer[len] != '\0')
		len++;
	line = NULL;
	ft_extract_line(&buffer, &line, len);
	return (line);
}

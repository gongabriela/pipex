/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ggoncalv <ggoncalv@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/27 11:18:44 by ggoncalv          #+#    #+#             */
/*   Updated: 2025/01/25 14:30:00 by ggoncalv         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char		*buffer;
	char			*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = read_file(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = set_line(buffer);
	if (line == NULL)
		return (free(buffer), NULL);
	if (ft_strlen(line) == 0)
		return (free(buffer), free(line), NULL);
	buffer = set_nextline(buffer, line);
	if (buffer == NULL)
		return (free(line), NULL);
	return (line);
}

char	*read_file(int fd, char *buffer)
{
	char	*temp;
	int		bytes_read;

	if (buffer == NULL)
		buffer = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	if (buffer == NULL)
		return (NULL);
	bytes_read = 1;
	while (buffer != NULL && bytes_read > 0 && !ft_strchr(buffer, '\n'))
	{
		temp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
		if (temp == NULL)
			return (NULL);
		bytes_read = read(fd, temp, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(temp), free(buffer), NULL);
		if (bytes_read == 0)
		{
			if (buffer[0] == '\0' && temp[0] == '\0')
				return (free(temp), free(buffer), NULL);
			return (free(temp), buffer);
		}
		buffer = gnl_ft_strjoin(buffer, temp);
	}
	return (buffer);
}

char	*set_line(char *buffer)
{
	char	*line;
	char	*start;
	int		i;

	i = 0;
	while (buffer[i] != '\n' && buffer[i] != '\0')
		i++;
	line = ft_calloc(i + 2, sizeof(char));
	if (line == NULL)
		return (NULL);
	start = line;
	while (i-- >= 0 && *buffer != '\0')
		*line++ = *buffer++;
	return (start);
}

char	*set_nextline(char	*buffer, char	*line)
{
	char	*newbuffer;
	int		i;
	int		j;

	i = ft_strlen(buffer) - ft_strlen(line);
	newbuffer = ft_calloc(i + 1, sizeof(char));
	if (newbuffer == NULL)
		return (NULL);
	i = ft_strlen(line);
	j = 0;
	while (buffer[i] != '\0')
	{
		newbuffer[j] = buffer[i];
		i++;
		j++;
	}
	return (free(buffer), newbuffer);
}

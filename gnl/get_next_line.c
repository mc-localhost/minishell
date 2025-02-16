/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vvasiuko <vvasiuko@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 18:18:07 by vvasiuko          #+#    #+#             */
/*   Updated: 2025/02/15 14:17:31 by vvasiuko         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

static char	*free_n_null(char *p)
{
	if (p)
		free(p);
	return (NULL);
}

static char	*read_line(int fd, char *buffer, int bytes_read)
{
	char	*buf;
	char	*temp;

	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (free_n_null(buffer));
	while (bytes_read > 0 && (!buffer || !ft_strchr(buffer, '\n')))
	{
		bytes_read = read(fd, buf, BUFFER_SIZE);
		if (bytes_read == -1)
			return (free(buf), free_n_null(buffer));
		if (bytes_read == 0)
			break ;
		buf[bytes_read] = '\0';
		if (!buffer)
			buffer = ft_strdup("");
		if (!buffer)
			return (free(buf), NULL);
		temp = buffer;
		buffer = ft_strjoin(temp, buf);
		temp = free_n_null(temp);
		if (!buffer)
			return (free(buf), NULL);
	}
	return (free(buf), buffer);
}

static char	*handle_n(char *buffer)
{
	int		i;
	char	*line;

	i = 0;
	if (!buffer[i])
		return (NULL);
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n')
		i++;
	line = malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
	{
		line[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
		line[i++] = '\n';
	line[i] = '\0';
	return (line);
}

static char	*update_buffer(char *buffer)
{
	int		i;
	char	*new_buffer;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
		return (free_n_null(buffer));
	new_buffer = ft_strdup(buffer + i + 1);
	free(buffer);
	if (!new_buffer || !new_buffer[0])
		return (free_n_null(new_buffer));
	return (new_buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!buffer || !ft_strchr(buffer, '\n'))
	{
		buffer = read_line(fd, buffer, 1);
		if (!buffer)
			return (NULL);
	}
	line = handle_n(buffer);
	if (!line)
	{
		buffer = free_n_null(buffer);
		return (NULL);
	}
	buffer = update_buffer(buffer);
	return (line);
}

// #include <fcntl.h> //open
// #include <stdio.h> //printf
// int	main(void)
// {
// 	int		fd;
// 	char	*line;
// 	fd = open("test.txt", O_RDONLY);
// 	while ((line = get_next_line(fd)))
// 	{
// 		printf("%s", line);
// 		free(line);
// 	}
// 	close(fd);
// 	return(0);
// }
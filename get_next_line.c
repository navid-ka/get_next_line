/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <nkeyani-@student.42barcelona.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:21:10 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/05/30 13:52:26 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>

static char	*read_storage(int fd, char *storage)
{
	char	*temp_storage;
	int		read_bytes;

	temp_storage = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_storage)
		return (NULL);
	read_bytes = 1;
	while (!ft_strchr(storage, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, temp_storage, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(temp_storage);
			return (NULL);
		}
		temp_storage[read_bytes] = '\0';
		storage = ft_strjoin(storage, temp_storage);
	}
	free(temp_storage);
	return (storage);
}

static char	*extract_line(char *storage)
{
	int		i;
	char	*line;

	i = 0;
	if (!storage[i])
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
	{
		line[i] = storage[i];
		i++;
	}
	if (storage[i] == '\n')
	{
		line[i] = storage[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static void	*clean_storage(char *storage)
{
	int		i;
	int		j;
	char	*new_storage;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (!storage[i])
	{
		free(storage);
		return (NULL);
	}
	new_storage = malloc(sizeof(char) * (ft_strlen(storage) - i + 1));
	if (!new_storage)
		return (NULL);
	i++;
	j = 0;
	while (storage[i])
		new_storage[j++] = storage[i++];
	new_storage[j] = '\0';
	free(storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*storage;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	storage = read_storage(fd, storage);
	if (!storage)
		return (NULL);
	line = extract_line(storage);
	storage = clean_storage(storage);
	return (line);
}

int main()
{
	int fd;
	int i;
	char *line;

	i = 0;
	fd = open("./hello.txt", O_RDONLY);
	while (i < 10)
	{
		line = get_next_line(fd);
		printf("return value %d: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd);
	return (0);
}

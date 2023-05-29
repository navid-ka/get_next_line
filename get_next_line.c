/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <nkeyani-@student.42barcelona.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:21:10 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/05/29 03:28:30 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static void	*free_storage(char *storage)
{
	if (storage)
	{
		free(storage);
		storage = NULL;
	}
	return (NULL);
}

static char	*read_storage(int fd, char *storage)
{
	int		bytes_read;
	char	*temp_storage;

	temp_storage = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_storage)
		return (NULL);
	bytes_read = 1;
	while (bytes_read && !ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, temp_storage, BUFFER_SIZE);
		temp_storage[bytes_read] = '\0';
		temp_storage = ft_strjoin(storage, temp_storage);
	}
	free_storage(temp_storage);
	return (storage);
}

static char	*new_line(char *storage)
{
	char	*temp_storage;
	char	*new_line;
	int		i;

	i = 0;
	temp_storage = storage;
	while (temp_storage[i] != '\n' && temp_storage[i] != '\0')
		i++;
	if (ft_strchr(storage, '\n'))
	{
		new_line = ft_strjoin(storage, temp_storage);
		free_storage(temp_storage);
	}
	free_storage(temp_storage);
	return (new_line);
}

char	*get_next_line(int fd)
{
	static char	*storage = {0};
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	storage = read_storage(fd, storage);
	if (!storage)
		return (NULL);
	line = new_line(storage);
	return (line);
}

int	main(void)
{
	int	fd = open("hello.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file");
		return 1;
	}
	char	*line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}
	close(fd);
	return (0);
}

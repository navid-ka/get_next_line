/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <nkeyani-@student.42barcelona.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:21:10 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/05/26 15:27:32 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static char *read_storage(int fd, char *storage)
{
	int bytes_read;
	char *temp_storage;

	temp_storage = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_storage)
		return (NULL);

	while (!ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, temp_storage, BUFFER_SIZE);
		if (bytes_read <= 0)
			break;
		temp_storage[bytes_read] = '\0';

		printf("storage: %s\n", storage); 
	}
	free(temp_storage);
	return (storage);
}

static char	*copy_storage(char *storage)
{
	char	*temp_storage;
	char	*new_storage;

	temp_storage = read_storage(0, storage);
	new_storage = ft_strjoin(storage, temp_storage);
	free(temp_storage);
	return (new_storage);
}

char	*get_next_line(int fd)
{
	static char	*storage = { 0 };
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	storage = read_storage(fd, storage);
	if (!storage)
		return (NULL);
	line = copy_storage(storage);
	return (line);
}

int	main(void)
{
	int fd = open("hello.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Failed to open file");
		return 1;
	}

	char *line;
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s\n", line);
		free(line);
	}

	close(fd);
	return 0;
}
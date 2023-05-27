/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:21:10 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/05/27 14:34:44 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

static void	*free_storage(char *storage)
{
	free(storage);
	storage = NULL;
}

static char	*read_storage(int fd, char *storage)
{
	int		bytes_read;
	char	*temp_storage;

	temp_storage = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_storage)
		return (NULL);
	bytes_read = 1;
	while (bytes_read > 0 && !ft_strchr(storage, '\n'))
	{
		bytes_read = read(fd, temp_storage, BUFFER_SIZE);
		temp_storage[bytes_read] = '\0';
	}
	free(temp_storage);
	return (storage);
}

static char	*delete_storage(char *stroage)
{
	
}

static char	*new_line(char *storage)
{
	char	*temp_storage;
	char	*new_line;

	temp_storage = read_storage(0, storage);
	new_line = ft_strjoin(storage, temp_storage);
	free(temp_storage);
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
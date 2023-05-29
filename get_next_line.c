/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:21:10 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/05/29 18:58:38 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

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
	char	*temp_storage;
	int		bytes;

	bytes = 1;
	temp_storage = malloc(BUFFER_SIZE + 1);
	if (!temp_storage)
		return (NULL);
	while (bytes && !ft_strchr(storage, '\n'))
	{
		bytes = read(fd, storage, BUFFER_SIZE);
		if (bytes == -1)
			return (0);
		temp_storage[bytes] = '\0';
		storage = ft_strjoin(temp_storage, storage);
		if (temp_storage == NULL)
			free_storage(temp_storage);
	}
	free_storage(temp_storage);
	return (storage);
}

//static char	*new_line(char *storage);

char	*get_next_line(int fd)
{
	static char	*storage = NULL;
	char		*line = NULL;

	printf("checkpoint fd\n");
	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	printf("%zd DID I READ IT???", read(fd, storage, BUFFER_SIZE));
	storage = read_storage(fd, storage);
	return (line);
}

#include <unistd.h>
#include <fcntl.h>

#include <string.h>

int		main(void)
{
	int		file;
	int		ret;
	char	*line;

	file = 0;
	while ((ret = get_next_line(file, &line)) == 1)
	{
		printf("[%d] |%s|\n", ret, line);
		free(line);
		line = NULL;
	}
	printf("[%d] |%s|\n", ret, line);
	free(line);
	line = NULL;
}


/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:21:10 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/06/02 12:13:36 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>

static char	*read_storage(int fd, char *storage)
{
	char	*temp_storage;
	int		read_bytes;

	temp_storage = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!temp_storage)
		return (free_storage(storage));
	read_bytes = 42;
	while (!ft_strchr(storage, '\n') && read_bytes > 0)
	{
		read_bytes = read(fd, temp_storage, BUFFER_SIZE);
		if (read_bytes < 0)
		{
			free(temp_storage);
			if (storage)
				free(storage);
			return (NULL);
		}
		temp_storage[read_bytes] = '\0';
		storage = ft_strjoin(storage, temp_storage);
	}
	free(temp_storage);
	temp_storage = NULL;
	return (storage);
}

static void	magical_copy(char *s1, char *s2, int i)
{
	s1[i] = s2[i];
}

static char	*extract_line(char *storage)
{
	int		i;
	char	*line;

	i = 0;
	if (storage[0] == '\0')
		return (NULL);
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\0')
		line = malloc(sizeof(char) * (i + 1));
	else
		line = malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (storage[i] && storage[i] != '\n')
		magical_copy(line, storage, i++);
	if (storage[i] == '\n')
		magical_copy(line, storage, i++);
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
	{
		free(storage);
		return (NULL);
	}
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
	static char	*storage[OPEN_MAX];

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
	{
		free(storage[fd]);
		return (NULL);
	}
	if (!storage[fd] || (storage[fd] && !ft_strchr(storage[fd], '\n')))
		storage[fd] = read_storage(fd, storage[fd]);
	if (!storage[fd])
		return (NULL);
	line = extract_line(storage[fd]);
	if (!line)
	{
		free(storage[fd]);
		storage[fd] = NULL;
		return (NULL);
	}
	storage[fd] = clean_storage(storage[fd]);
	return (line);
}

/*int main()
{
	int fd1;
	int fd2;
	int i;
	char *line;

	i = 0;
	fd1 = open("./0.txt", O_RDONLY);
	fd2 = open("./hello.txt", O_RDONLY);
	while (i < 10)
	{
		line = get_next_line(fd1);
		printf("1return value %d: %s\n", i, line);
		free(line);
		line = get_next_line(fd2);
		printf("2return value %d: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd1);
	close(fd2);
	return (0);
}
*/
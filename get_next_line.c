/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bifrost <nkeyani-@student.42barcelona.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:21:10 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/05/26 12:36:35 by bifrost          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*read_storage(int fd, char *storage)
{
	int		bytes_read;
	char	*temp_storage;
	
	temp_storage = malloc(size(char) * BUFFER_SIZE + 1);
	if (!temp_storage)
		return (NULL);
	bytes_read = 1;
	while (!ft_strchr(storage,'\n'))
		bytes_read = read(fd, temp_storage, BUFFER_SIZE);
	free(temp_storage);
	return (storage);
}

static char	*copy_storage(char *storage)
{
	char	*temp_storage;
	char	*new_storage;

	temp_storage = read_storage(storage);
	new_storage = ft_strjoin(storage, temp_storage);
	free(temp_storage);
	return (new_storage);
}

static char *clean_storage(char *storage);

char	*get_next_line(int fd)
{
	static char	*storage = { 0 };
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0)
		return (NULL);
	return (line);
}

#include <stdio.h>
int	main(void)
{
	printf("%s", ft_strjoin("Hola ", "Que Tal"));
	return (0);
}

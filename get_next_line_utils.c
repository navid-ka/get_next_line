/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nkeyani- < nkeyani-@student.42barcelona    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 13:09:31 by nkeyani-          #+#    #+#             */
/*   Updated: 2023/05/24 15:51:17 by nkeyani-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (*s++)
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		i;
	int		s1len;
	int		s2len;
	char	*joined;

	joined = (char *)s1;
	s1len = ft_strlen((char *)s1);
	s2len = ft_strlen((char *)s2);
	joined = malloc((s1len + s2len) + 1 * sizeof(char *));
	if (!joined)
		return (NULL);
	i = 0;
	while (s2len--)
	{
		joined[s1len + i] = s2[i];
		i++;
	}
	joined[s1len + i] = '\0';
	return (joined);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == (char)c)
			return ((char *)&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)&s[i]);
	return (NULL);
}


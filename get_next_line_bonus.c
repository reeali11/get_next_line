/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: reeali <reeali@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 10:01:11 by reeali            #+#    #+#             */
/*   Updated: 2023/09/18 10:31:15 by reeali           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*ft_get_line(char *strread)
{
	int		i;
	char	*line;

	i = 0;
	if (!strread[i])
		return (NULL);
	while (strread[i] && strread[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (strread[i] && strread[i] != '\n')
	{
		line[i] = strread[i];
		i++;
	}
	if (strread[i] == '\n')
	{
		line[i] = strread[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_rest(char *strread)
{
	int		i;
	int		c;
	char	*rest;

	i = 0;
	while (strread[i] && strread[i] != '\n')
		i++;
	if (!strread[i])
	{
		free(strread);
		return (NULL);
	}
	rest = (char *)malloc(sizeof(char) * (ft_strlen(strread) - i + 1));
	if (!rest)
		return (NULL);
	i++;
	c = 0;
	while (strread[i])
		rest[c++] = strread[i++];
	rest[c] = '\0';
	free(strread);
	return (rest);
}

char	*ft_read(int fd, char *strread)
{
	char	*buff;
	int		readbytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	readbytes = 1;
	while (readbytes != 0)
	{
		readbytes = read(fd, buff, BUFFER_SIZE);
		if (readbytes == -1)
		{
			free(buff);
			free(strread);
			return (NULL);
		}
		buff[readbytes] = '\0';
		strread = ft_strjoin(strread, buff);
		if (ft_strchr(strread, '\n'))
			break ;
	}
	free(buff);
	return (strread);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*strread[10000];

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE > 2147483648)
		return (0);
	strread[fd] = ft_read(fd, strread[fd]);
	if (!strread[fd])
		return (NULL);
	line = ft_get_line(strread[fd]);
	strread[fd] = ft_rest(strread[fd]);
	return (line);
}

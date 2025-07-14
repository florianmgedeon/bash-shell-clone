/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aszabo <aszabo@student.42vienna.com>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 11:22:43 by aszabo            #+#    #+#             */
/*   Updated: 2023/11/27 15:40:22 by aszabo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
/* #include <stdio.h>
#include <fcntl.h> */

char	*ft_new_str(char *str)
{
	int		i;
	int		j;
	char	*new;

	i = 0;
	j = 0;
	if (!str)
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new = (char *)malloc(sizeof(char) * (len(str) - i + 1));
	if (!new)
		return (NULL);
	i++;
	while (str[i])
		new[j++] = str[i++];
	new[j] = '\0';
	free(str);
	return (new);
}

char	*ft_get_line(char *str)
{
	int		i;
	char	*line;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 2));
	if (!line)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read_str(int fd, char *str)
{
	char	*buff;
	int		read_chars;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	read_chars = 1;
	while (!chr(str, '\n') && read_chars != 0)
	{
		read_chars = read(fd, buff, BUFFER_SIZE);
		if (read_chars == -1)
		{
			free(buff);
			free(str);
			return (NULL);
		}
		buff[read_chars] = '\0';
		str = join(str, buff);
	}
	free(buff);
	return (str);
}

char	*get_next_line(int fd)
{
	char			*line;
	static char		*str;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	str = ft_read_str(fd, str);
	if (!str)
		return (NULL);
	line = ft_get_line(str);
	str = ft_new_str(str);
	return (line);
}
/*
int	main(void)
{
	char *line;
	int	i = 1;
	int fd;
	fd = open("test.txt", O_RDONLY);
	while (i < 7)
	{
		line = get_next_line(fd);
		printf("line %d:   %s\n", i, line);
		i++;
	}
	close(fd);
	return (0);
}*/
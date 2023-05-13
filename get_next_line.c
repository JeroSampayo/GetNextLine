/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiras-s <jmiras-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:53:47 by jmiras-s          #+#    #+#             */
/*   Updated: 2023/05/13 18:24:09 by jmiras-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

void	*ft_free(char **str)
{
	if (str && *str)
		free(*str);
	return (NULL);
}

static char	*read_and_join(int fd, char *buf, char *backup)
{
	int		read_line;

	read_line = 1;
	while (read_line > 0 && !ft_strchr(backup, '\n'))
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		else if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		backup = ft_strjoin(backup, buf);
		if (!backup)
			return (ft_free(&backup));
	}
	return (backup);
}

char	*extract(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == '\0')
		return (NULL);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count - 1);
	if (!backup || *backup == '\0')
	{
		ft_free(&backup);
		return (NULL);
	}
	if (line[count] == '\n')
		count++;
	line[count] = '\0';
	return (backup);
}

char	*clean_line(char *line)
{
	char	*str;
	int		len;

	len = 0;
	if (!line)
		return (ft_free(&line));
	while (line[len])
		len++;
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (!str)
		return (ft_free(&line));
		len = -1;
	while (line[++len])
		str[len] = line[len];
	str[len] = '\0';
	ft_free(&line);
	return (str);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup = NULL;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > OPEN_MAX)
		return (NULL);
	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (ft_free(&backup));
	printf("Backup abans de read&join: %s\n", backup);
	line = read_and_join(fd, buf, backup);
	ft_free(&buf);
	if (!line)
		return (ft_free(&backup));
	printf("Backup despres de read&join: %s\n", backup);
	printf("Line despres de read&join: %s\n", line);
	backup = extract(line);
	printf("Backup despres de extract: %s\n", backup);
	printf("Line despres de extract: %s\n", line);
	line = clean_line(line);
	printf("Line despres de clean line: %s\n", line);
	return (line);
}

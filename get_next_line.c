/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmiras-s <jmiras-s@student.42barcel>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/17 15:53:47 by jmiras-s          #+#    #+#             */
/*   Updated: 2023/05/02 21:20:22 by jmiras-s         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static void *ft_free(char **str)
{
    if (str)
    {
        free (*str);
        *str = NULL;
    }
    return (NULL);
}

static char *read_and_join(int fd, char *buf, char *backup)
{
    int     read_line;
    char    *temp;

    read_line = 1;
    while (read_line != '\0')
    {
        read_line = read(fd, buf, BUFFER_SIZE);
        if (read_line == -1)
            return (NULL);
        else if (read_line == 0)
            break ;
        buf[read_line] = '\0';
        if (!backup)
            backup = ft_strdup("");
        temp = backup;
        backup = ft_strjoin(temp, buf);
        ft_free(&temp);
        if (ft_strchr(buf, '\n'))
            break ;
        if (read_line == 0 && !ft_strchr(backup, '\n'))
            break ;
    }
    return (backup);
}

static char *extract(char *line)
{
    size_t  count;
    char    *backup;

    count = 0;
    while (line[count] != '\n' && line[count] != '\0')
        count++;
    if (line[count] == '\0' || line[1] == '\0')
        return (NULL);
    backup = ft_substr(line, count + 1, ft_strlen(line) - count);
    if (!backup || *backup == '\0')
        return (ft_free(&backup));
    line[count + 1] = '\0';
    return (backup);
}

char    *get_next_line(int fd)
{
    char        *line;
    char        *buf;
    static char *backup = NULL;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!buf)
        return (NULL);
    line = read_and_join(fd, buf, backup);
    ft_free(&buf);
    if (!line)
 // {
 //     if (backup)
 //        return (ft_free(&backup));
 //     return (NULL);
 // }
    backup = extract(line);
 // if(!backup && line)
 // {
 //     ft_free(&line);
 //     return (NULL);
 // }
    return (line);
}




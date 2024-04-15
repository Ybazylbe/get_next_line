/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybazylbe <ybazylbe@student.42prague.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/22 11:01:47 by ybazylbe          #+#    #+#             */
/*   Updated: 2023/12/22 11:14:09 by ybazylbe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
// #include <stdio.h>
// #include <fcntl.h>

char	*ft_read_to_left_str(int fd, char *left_str)
{
	char	*buff;
	int		rd_bytes;

	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
		return (NULL);
	rd_bytes = 1;
	while (!ft_strchr(left_str, '\n') && rd_bytes != 0)
	{
		rd_bytes = read(fd, buff, BUFFER_SIZE);
		if (rd_bytes == -1)
		{
			free(buff);
			return (NULL);
		}
		buff[rd_bytes] = '\0';
		left_str = ft_strjoin(left_str, buff);
	}
	free(buff);
	return (left_str);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*left_str[4096];

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	left_str[fd] = ft_read_to_left_str(fd, left_str[fd]);
	if (!left_str[fd])
		return (NULL);
	line = ft_get_line(left_str[fd]);
	left_str[fd] = ft_new_left_str(left_str[fd]);
	return (line);
}

// int main(void)
// {
//     int fd1, fd2;
//     char *line;

//     fd1 = open("test", O_RDONLY);
//     fd2 = open("test1", O_RDONLY);

//     if (fd1 < 0 || fd2 < 0)
//     {
//         perror("Error");
//         return -1;
//     }

//     while ((line = get_next_line(fd1)) != NULL)
//     {
//         printf("File 1: %s\n", line);
//         free(line);
//     }

//     while ((line = get_next_line(fd2)) != NULL)
//     {
//         printf("File 2: %s\n", line);
//         free(line);
//     }

//     close(fd1);
//     close(fd2);
//     return 0;
// }
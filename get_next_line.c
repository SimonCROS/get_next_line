/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:45:01 by scros             #+#    #+#             */
/*   Updated: 2020/12/02 11:40:10 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static char	*remain;
	char		*tmp;
	char		**current;
	ssize_t		result;

	if (!(*line = malloc(0)))
		return (-1);
	**line = 0;
	if (remain)
	{
		current = ft_split_first(remain, '\n');
		free(*line);
		*line = current[0];
	}
	result = 1;
	while (result > 0 && (!current || !current[1]))
	{
		if (!(remain = malloc(BUFFER_SIZE + 1)))
			return (-1);
		result = read(fd, remain, BUFFER_SIZE);
		remain[BUFFER_SIZE] = 0;
		if (current)
			free(current);
		current = ft_split_first(remain, '\n');
		tmp = *line;
		*line = ft_strjoin(tmp, current[0]);
		free(current[0]);
		free(tmp);
	}
	remain = current[1];
	free(current);
	return (0);
}

// TESTS TESTS TESTS

#include <time.h>
#include <errno.h>

int msleep(long msec)
{
    struct timespec ts;
    int res;

    if (msec < 0)
    {
        errno = EINVAL;
        return -1;
    }

    ts.tv_sec = msec / 1000;
    ts.tv_nsec = (msec % 1000) * 1000000;

    do {
        res = nanosleep(&ts, &ts);
    } while (res && errno == EINTR);

    return res;
}

int		main(void)
{
	int		fd;
	char	*line;
	int		r;

	if ((fd = open("get_next_line.h", O_RDONLY)) == -1)
		return (0);

	r = 30;
	while (r--)
	{
		get_next_line(fd, &line);
		printf("%s\n", line);
		msleep(50);
		free(line);
	}

	// while ((r = get_next_line(fd, &line));
	// {
	// 	printf("%s\n", line);
	// 	if (r == -1)
	// 		break ;
	// }
	close(fd);
	while (1)
	{
	}
	return (0);
}

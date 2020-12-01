/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:45:01 by scros             #+#    #+#             */
/*   Updated: 2020/12/01 11:40:08 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

int		ft_next_step(char ***join, char **remain, char *old)
{
	char	**current;

	old = (*join)[0];
	if (old)
	{
		current = ft_split_first((*join)[1], '\n');
		if (!((*join)[0] = ft_strjoin((*join)[0], current[0])))
			return (-1);
		if (*(current[1]))
		{
			*remain = current[1];
			return (1);
		}
	}
	else
		(*join)[0] = (*join)[1];
	free(old);
	return (0);
}

int		get_next_line(int fd, char **line)
{
	static char		**remain;
	unsigned int	current_len;
	char			**join;
	char			*old;
	int				result;

	if (!(join = malloc(sizeof(join) * 2)))
		return (-1);
	if (!(join[0] = malloc(0)))
		return (-1);
	if (!remain)
	{
		if (!(remain = malloc(sizeof(remain))))
			return (-1);
		if (!(*remain = malloc(0)))
			return (-1);
	}
	if ((join[1] = *remain))
		ft_next_step(&join, remain, old);
	if (!(*remain = malloc(0)))
		return (-1);
	if (!(join[1] = malloc(BUFFER_SIZE)))
		return (-1);
	join[1][BUFFER_SIZE] = 0;
	while ((current_len = read(fd, join[1], BUFFER_SIZE)))
	{
		result = ft_next_step(&join, remain, old);
		if (result == -1)
			return (-1);
		else if (result == 1)
			break ;
	}
	*line = join[0];
	if (!current_len)
		return (-1);
	free(join[1]);
	if (result == 0)
		return (0);
	return (1);
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
		msleep(100);
	}

	// while ((r = get_next_line(fd, &line));
	// {
	// 	printf("%s\n", line);
	// 	if (r == -1)
	// 		break ;
	// }
	if (close(fd) == -1)
		return (0);
	return (0);
}

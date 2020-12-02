/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:45:01 by scros             #+#    #+#             */
/*   Updated: 2020/12/02 17:23:30 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		get_next_line(int fd, char **line)
{
	static char	*remain;
	char		*tmp;
	char		**current;
	char		*tmp_line;
	ssize_t		result;

	if (BUFFER_SIZE < 1 || !(tmp_line = malloc(0)))
		return (-1);
	*tmp_line = 0;
	current = NULL;
	if (remain)
	{
		current = ft_split_first(remain, '\n');
		free(tmp_line);
		tmp_line = current[0];
	}
	result = BUFFER_SIZE;
	while (result == BUFFER_SIZE && (!current || !current[1]))
	{
		if (!(remain = malloc(BUFFER_SIZE + 1)))
			return (-1);
		result = read(fd, remain, BUFFER_SIZE);
		if (result < 0)
			return (-1);
		if (current)
			free(current);
		if (result >= 0)
		{
			remain[result] = 0;
			if (!(current = ft_split_first(remain, '\n')))
				return (-1);
			if (result > 0)
			{
				tmp = tmp_line;
				if (!(tmp_line = ft_strjoin(tmp, current[0])))
					return (-1);
				free(tmp);
			}
			free(current[0]);
		}
	}
	remain = current[1];
	free(current);
	*line = tmp_line;
	if (result == BUFFER_SIZE || (result && remain))
		return (1);
	free(remain);
	remain = NULL;
	return (0);
}

// int		main(void)
// {
// 	int		fd;
// 	char	*line;

// 	if ((fd = open("line.o", O_RDONLY)) == -1)
// 		return (0);

// 	int r;
// 	while ((r = get_next_line(fd, &line)) > 0)
// 	{
// 		printf("%s\n", line);
// 		free(line);
// 	}
// 	printf("%s\n", line);
// 	free(line);

// 	close(fd);
// 	while (1)
// 	{
// 	}
// 	return (0);
// }

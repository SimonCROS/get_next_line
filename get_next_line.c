/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:45:01 by scros             #+#    #+#             */
/*   Updated: 2020/12/03 14:25:47 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	char *cp;

	cp = (char*)s;
	while (1)
	{
		if (*cp == c)
		{
			if (c != 0)
				return (cp + 1);
			else
				return (cp);
		}
		if (!*cp)
			break ;
		++cp;
	}
	return (NULL);
}

ssize_t	read_line(int fd, char **line, char ***current, char **remain)
{
	char	*tmp;
	ssize_t	result;

	if (!(*remain = malloc(BUFFER_SIZE + 1)))
		return (-1);
	result = read(fd, *remain, BUFFER_SIZE);
	if (result < 0)
		return (-1);
	if (*current)
		free(*current);
	if (result >= 0)
	{
		(*remain)[result] = 0;
		if (!(*current = ft_split_first(*remain, '\n')))
			return (-1);
		if (result > 0)
		{
			tmp = *line;
			if (!(*line = ft_strjoin(tmp, (*current)[0])))
				return (-1);
			free(tmp);
		}
		free((*current)[0]);
	}
	return (result);
}

int		load_remain(char *remain, char **line, char ***current)
{
	if (remain)
	{
		if (!(*current = ft_split_first(remain, '\n')))
			return (-1);
		free(*line);
		*line = (*current)[0];
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static char	*remain;
	char		**current;
	char		*tmp_line;
	ssize_t		result;

	if (BUFFER_SIZE < 1 || !(tmp_line = malloc(0)))
		return (-1);
	*tmp_line = 0;
	current = NULL;
	if (load_remain(remain, &tmp_line, &current) == -1)
		return (-1);
	result = BUFFER_SIZE;
	while (result == BUFFER_SIZE && (!current || !current[1]))
		if ((result = read_line(fd, &tmp_line, &current, &remain)) == -1)
			return (-1);
	remain = current[1];
	free(current);
	*line = tmp_line;
	if (result == BUFFER_SIZE || (result && remain))
		return (1);
	free(remain);
	remain = NULL;
	return (0);
}

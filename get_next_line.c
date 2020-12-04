/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:45:01 by scros             #+#    #+#             */
/*   Updated: 2020/12/04 14:38:37 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		delete(t_list **remain, t_list *element, int ret)
{
	t_list *elem;

	if (element == *remain)
		*remain = element->next;
	else
	{
		elem = *remain;
		while (elem)
		{
			if (elem->next == element)
			{
				elem->next = element->next;
				break ;
			}
			elem = elem->next;
		}
	}
	free(element->content);
	free(element);
	return (ret);
}

t_list	*get_or_create_remain(t_list **remain, int fd)
{
	t_list *new_element;
	t_list *elem;

	elem = *remain;
	while (elem)
	{
		if (elem->fd == fd)
			return (elem);
		elem = elem->next;
	}
	if (!(new_element = malloc(sizeof(*new_element))))
		return (NULL);
	new_element->content = NULL;
	new_element->fd = fd;
	new_element->next = *remain;
	*remain = new_element;
	return (new_element);
}

ssize_t	read_line(int fd, char **line, char ***current, t_list *remain)
{
	char	*tmp;
	ssize_t	result;

	if (!(remain->content = malloc(BUFFER_SIZE + 1)))
		return (-1);
	result = read(fd, remain->content, BUFFER_SIZE);
	if (result < 0)
		return (-1);
	if (*current)
		free(*current);
	if (result >= 0)
	{
		remain->content[result] = 0;
		if (!(*current = ft_split_first(remain->content, '\n')))
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

int		load_remain(t_list *remain, char **line, char ***current)
{
	if (remain->content)
	{
		if (!(*current = ft_split_first(remain->content, '\n')))
			return (-1);
		free(*line);
		*line = (*current)[0];
	}
	return (1);
}

int		get_next_line(int fd, char **line)
{
	static t_list	*remain_lst;
	char			**current;
	char			*tmp_line;
	t_list			*remain;
	ssize_t			result;

	if (BUFFER_SIZE < 1 || !(tmp_line = malloc(0)))
		return (-1);
	*tmp_line = 0;
	if (!(remain = get_or_create_remain(&remain_lst, fd)))
		return (-1);
	current = NULL;
	if (load_remain(remain, &tmp_line, &current) == -1)
		return (-1);
	result = BUFFER_SIZE;
	while (result == BUFFER_SIZE && (!current || !current[1]))
		if ((result = read_line(fd, &tmp_line, &current, remain)) == -1)
			return (-1);
	remain->content = current[1];
	free(current);
	*line = tmp_line;
	if (result == BUFFER_SIZE || (result && remain->content))
		return (1);
	return (delete(&remain_lst, remain, 0));
}

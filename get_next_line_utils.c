/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: scros <scros@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/26 13:44:58 by scros             #+#    #+#             */
/*   Updated: 2020/12/02 17:23:02 by scros            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char    *ft_strdup(const char *s1)
{
	char	*pointer;
	size_t	size;
	int		i;

	size = ft_strlen(s1) + 1;
	if (!(pointer = malloc(size)))
			return (NULL);
	i = 0;
	while (s1[i])
	{
		pointer[i] = s1[i];
		i++;
	}
	pointer[i] = 0;
	return (pointer);
}

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

size_t	ft_strlen(const char *s)
{
	size_t i;

	i = -1;
	while (s[++i])
		;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*str;
	int		len1;
	int		len2;

	if (!s1 || !s2)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (!(str = malloc(len1 + len2 + 1)))
		return (NULL);
	ft_memcpy(str, s1, len1);
	ft_memcpy(str + len1, s2, len2);
	str[len1 + len2] = 0;
	return (str);
}

char	**ft_split_first(char *s, char c)
{
	char	**parts;
	size_t	len;

	if (!(parts = malloc(sizeof(parts) * 2)))
		return (NULL);
	len = 0;
	parts[1] = ft_strchr(s, c);
	if (!parts[1])
		len = -1;
	else
		len += parts[1] - s - 1;
	if (!(parts[0] = ft_substr(s, 0, len)))
		return (NULL);
	if (parts[1])
		parts[1] = ft_strdup(parts[1]);
	free(s);
	return (parts);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t			i;
	unsigned char	*sstr;
	unsigned char	*dstr;

	i = 0;
	sstr = (unsigned char*)src;
	dstr = dst;
	if (!dst && !src)
		return (NULL);
	while (i < n)
	{
		dstr[i] = sstr[i];
		++i;
	}
	return (dst);
}

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*str;
	size_t	size;

	if (!s)
		return (NULL);
	size = ft_strlen(s) - start;
	if (len < size)
		size = len;
	if (start >= ft_strlen(s))
		size = 0;
	if (!(str = malloc(size + 1)))
		return (NULL);
	ft_memcpy(str, s + start, size);
	str[size] = 0;
	return (str);
}

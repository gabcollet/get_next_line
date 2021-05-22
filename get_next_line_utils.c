/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gcollet <gcollet@student.42quebec.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/14 15:27:19 by gcollet           #+#    #+#             */
/*   Updated: 2021/05/22 18:45:46 by gcollet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dest && !src)
		return (NULL);
	while (i < n)
	{
		((unsigned char *)dest)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (dest);
}


char	*ft_strchr(const char *s, int c)
{
	char	*str;

	str = (char *)s;
	while (*str != c)
	{
		if (*str == '\0')
			return (NULL);
		str++;
	}
	return (str);
}

size_t	ft_strlen(const char *s)
{
	size_t			i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*tab;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	tab = (char *)malloc(sizeof(*tab) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (tab == NULL)
		return (NULL);
	while (s1[i])
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		tab[i + j] = s2[j];
		j++;
	}
	tab[i + j] = '\0';
	free((void *)s1);
	return (tab);
}

char	*ft_strdup(const char *s)
{
	char	*tab;
	int		i;

	i = 0;
	tab = (char *)malloc(sizeof(*tab) * (ft_strlen(s) + 1));
	if (!tab)
		return (NULL);
	while (s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}

// size_t	ft_strlen(const char *str)
// {
// 	const char	*end;

// 	end = str;
// 	while (*end != '\0')
// 		++end;
// 	return (end - str);
// }

// char	*ft_strchr(const char *str, int c)
// {
// 	c = (unsigned char)c;
// 	while (*str != '\0')
// 	{
// 		if (*str == c)
// 			return ((char *)str);
// 		++str;
// 	}
// 	return ((*str == c) ? (char *)str : NULL);
// }

// void	*ft_memcpy(void *dest, const void *src, size_t num)
// {
// 	char	*pdest;
// 	char	*psrc;

// 	if (dest == src)
// 		return (dest);
// 	pdest = (char *)dest;
// 	psrc = (char *)src;
// 	while (num-- != 0)
// 		*pdest++ = *psrc++;
// 	return (dest);
// }

// char	*ft_strdup(const char *str)
// {
// 	size_t		block_size;
// 	void		*ptr;

// 	block_size = ft_strlen(str) + 1;
// 	if (!(ptr = malloc(block_size)))
// 		return (NULL);
// 	return (ft_memcpy(ptr, str, block_size));
// }

// char	*ft_strjoin(const char *str1, const char *str2)
// {
// 	char		*big;
// 	size_t		len1;
// 	size_t		len2;

// 	if (!str1 || !str2)
// 		return (NULL);
// 	len1 = ft_strlen(str1);
// 	len2 = ft_strlen(str2);
// 	if (!(big = (char *)malloc(len1 + len2 + 1)))
// 		return (NULL);
// 	ft_memcpy(big, str1, len1);
// 	ft_memcpy(big + len1, str2, len2 + 1);
// 	return (big);
// }

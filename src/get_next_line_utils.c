/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:40:08 by smatthes          #+#    #+#             */
/*   Updated: 2023/07/26 14:52:54 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	length;

	length = 0;
	while (*s++)
		length++;
	return (length);
}

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	src_len;
	size_t	i;

	i = 0;
	src_len = ft_strlen(src);
	if (size <= 0)
		return (src_len);
	while (i < (size - 1) && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (src_len);
}

// n must contain space for null byte
char	*ft_str_n_join(char const *s1, char const *s2, int n)
{
	size_t	str_len_1;
	size_t	str_len_2;
	char	*res_str;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
		return (ft_str_n_dup(s2, n));
	if (!s2)
		return (ft_str_n_dup(s1, n));
	str_len_2 = ft_strlen(s2);
	str_len_1 = ft_strlen(s1);
	if (n == 0)
		n = str_len_2 + 1;
	res_str = malloc(sizeof(*res_str) * (str_len_1 + n));
	if (!res_str)
		return (NULL);
	ft_strlcpy(res_str, s1, str_len_1 + 1);
	ft_strlcpy(res_str + str_len_1, s2, n);
	return (res_str);
}

ssize_t	ft_str_chr_index(const char *s, int c)
{
	char	c_cast;
	int		i;

	i = 0;
	c_cast = (unsigned char)c;
	while (s[i] != c_cast && s[i])
		i++;
	if (s[i] == c_cast)
		return (i);
	return (-1);
}

char	*ft_str_n_dup(const char *s, int n)
{
	size_t	str_len;
	char	*new_str;
	int		i;

	i = 0;
	if (!s)
		return (NULL);
	if (n == 0)
	{
		str_len = ft_strlen(s);
		n = str_len + 1;
	}
	new_str = malloc((n) * sizeof(*new_str));
	if (!new_str)
		return (NULL);
	while (s[i] && i < n - 1)
	{
		new_str[i] = s[i];
		i++;
	}
	new_str[i] = '\0';
	return (new_str);
}

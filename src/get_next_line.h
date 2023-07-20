/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:40:10 by smatthes          #+#    #+#             */
/*   Updated: 2023/07/20 18:57:27 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

// remove at the end
# include <stdio.h>
// remove at the end

# define BOOLEAN int
# define TRUE 1
# define FALSE 0

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

char		*get_next_line(int fd);
size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_str_n_join(char const *s1, char const *s2, int n);
ssize_t		ft_str_chr_index(const char *s, int c);
char		*ft_str_n_dup(const char *s, int n);

typedef struct s_get_next
{
	int		total_chars_read;
	int		i_last_newline;
	BOOLEAN	all_buffer_parsed;
	char	last_buffer_read[BUFFER_SIZE + 1];
}			t_get_next;

#endif

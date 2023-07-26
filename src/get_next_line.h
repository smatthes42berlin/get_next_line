/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:40:10 by smatthes          #+#    #+#             */
/*   Updated: 2023/07/26 15:18:36 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# define BOOLEAN int
# define TRUE 1
# define FALSE 0
# define ERROR -1
# define BUFFER_PARSED -2
# define NEW_BUFFER -1

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 3
# endif

typedef struct s_get_next
{
	int		total_chars_read;
	int		i_last_newline;
	char	last_buffer_read[BUFFER_SIZE + 1];
}			t_get_next;

typedef struct s_search_state
{
	int		chars_left;
	int		newline_index;
	char	*tmp_ptr;
	char	*start;
}			t_search_state;

char		*get_next_line(int fd);
BOOLEAN		check_if_newline_in_buffer(t_get_next *gnl_info, char **next_line);
int			process_newline_search_result(t_get_next *gnl_info,
				char **next_line,
				t_search_state search);
void		reset_gnl_static(t_get_next *gnl_info);
char		*reset_gnl_static_null(t_get_next *gnl_info, char **next_line);

size_t		ft_strlen(const char *s);
size_t		ft_strlcpy(char *dst, const char *src, size_t size);
char		*ft_str_n_join(char const *s1, char const *s2, int n);
ssize_t		ft_str_chr_index(const char *s, int c);
char		*ft_str_n_dup(const char *s, int n);

#endif

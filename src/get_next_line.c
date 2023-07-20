/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:40:06 by smatthes          #+#    #+#             */
/*   Updated: 2023/07/20 20:07:23 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// read one character at a time?
// BUFFER_SIZE is buffer size for read
// realloc -> always save length of current buffer

#include "./get_next_line.h"

// make sure it can also read from STDINPUT
// hint: A File descriptor does not only point to regular files

BOOLEAN	check_if_newline_in_buffer(t_get_next *gnl_info, char **next_line)
{
	char	*search_start;
	ssize_t	num_chars_left;
	char	*tmp;
	ssize_t	found_new_line;

	if (gnl_info->all_buffer_parsed)
	{
		return (FALSE);
	}
	num_chars_left = gnl_info->total_chars_read - (gnl_info->i_last_newline
			+ 1);
	search_start = &gnl_info->last_buffer_read[gnl_info->i_last_newline + 1];
	found_new_line = ft_str_chr_index(search_start, '\n');
	// printf("current next line is $%s$\n", *next_line);
	// printf("last newline is $%d$\n", gnl_info->i_last_newline);
	// printf("search start = $%s$\n", search_start);
	// printf("num chars left = $%lu$\n", num_chars_left);
	// printf("index new line = $%ld$\n", found_new_line);
	if (found_new_line == -1)
	{
		tmp = *next_line;
		*next_line = ft_str_n_join(*next_line, search_start, 0);
		// printf("no newline found joined string is $%s$\n", *next_line);
		gnl_info->all_buffer_parsed = TRUE;
		gnl_info->i_last_newline = -1;
		free(tmp);
		return (FALSE);
	}
	else
	{
		// printf("index new line = $%ld$\n", found_new_line);
		// printf("num chars left = $%lu$\n", num_chars_left);
		tmp = *next_line;
		gnl_info->i_last_newline = gnl_info->i_last_newline + found_new_line
			+ 1;
		*next_line = ft_str_n_join(*next_line, search_start, found_new_line
				+ 2);
		// printf("newline found joined string is $%s$\n", *next_line);
		free(tmp);
		if (found_new_line == num_chars_left - 1)
		{
			gnl_info->all_buffer_parsed = TRUE;
			gnl_info->i_last_newline = -1;
		}
		return (TRUE);
	}
}

char	*get_next_line(int fd)
{
	char *next_line;
	BOOLEAN new_line_in_buffer;
	static t_get_next gnl_info = {.i_last_newline = -1,
									.all_buffer_parsed = TRUE,
									.total_chars_read = 0};

	next_line = NULL;
	if (read(fd, NULL, 0) == -1)
	{
		// gnl_info.all_buffer_parsed = TRUE;
		return (NULL);	
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	new_line_in_buffer = check_if_newline_in_buffer(&gnl_info, &next_line);
	while (!new_line_in_buffer)
	{
		gnl_info.total_chars_read = read(fd, gnl_info.last_buffer_read,
				BUFFER_SIZE);
		if (gnl_info.total_chars_read == -1)
		{
			free(next_line);
			return (NULL);
		}
		gnl_info.last_buffer_read[gnl_info.total_chars_read] = '\0';
		gnl_info.all_buffer_parsed = FALSE;
		if (gnl_info.total_chars_read == 0)
			gnl_info.all_buffer_parsed = TRUE;
		if (gnl_info.total_chars_read == 0 && next_line
			&& ft_strlen(next_line) > 0)
			return (next_line);
		if (gnl_info.total_chars_read == 0)
			return (NULL);
		new_line_in_buffer = check_if_newline_in_buffer(&gnl_info, &next_line);
	}
	return (next_line);
}
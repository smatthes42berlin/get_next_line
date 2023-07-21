/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:40:06 by smatthes          #+#    #+#             */
/*   Updated: 2023/07/21 11:37:33 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.h"

char	*get_next_line(int fd)
{
	char				*next_line;
	BOOLEAN				newline_found;
	static t_get_next	gnl_info = {.i_last_newline = BUFFER_PARSED,
		.total_chars_read = 0};

	next_line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, NULL, 0) == -1)
		return (reset_gnl_static_null(&gnl_info, &next_line));
	newline_found = check_if_newline_in_buffer(&gnl_info, &next_line);
	while (!newline_found && newline_found != ERROR)
	{
		gnl_info.total_chars_read = read(fd, gnl_info.last_buffer_read,
				BUFFER_SIZE);
		if (gnl_info.total_chars_read == -1)
			return (reset_gnl_static_null(&gnl_info, &next_line));
		gnl_info.last_buffer_read[gnl_info.total_chars_read] = '\0';
		if (gnl_info.total_chars_read > 0)
			gnl_info.i_last_newline = NEW_BUFFER;
		if (gnl_info.total_chars_read == 0)
			return (next_line);
		newline_found = check_if_newline_in_buffer(&gnl_info, &next_line);
	}
	if (newline_found == ERROR)
		return (reset_gnl_static_null(&gnl_info, &next_line));
	return (next_line);
}

BOOLEAN	check_if_newline_in_buffer(t_get_next *gnl_info, char **next_line)
{
	t_search_state	search;

	if (gnl_info->i_last_newline == BUFFER_PARSED)
		return (FALSE);
	search.chars_left = gnl_info->total_chars_read - (gnl_info->i_last_newline
			+ 1);
	search.start = &gnl_info->last_buffer_read[gnl_info->i_last_newline + 1];
	search.newline_index = ft_str_chr_index(search.start, '\n');
	return (process_newline_search_result(gnl_info, next_line, search));
}

int	process_newline_search_result(t_get_next *gnl_info,
									char **next_line,
									t_search_state search)
{
	if (search.newline_index == -1)
	{
		search.tmp_ptr = *next_line;
		*next_line = ft_str_n_join(*next_line, search.start, 0);
		if (!*next_line)
			return (ERROR);
		gnl_info->i_last_newline = BUFFER_PARSED;
		free(search.tmp_ptr);
		return (FALSE);
	}
	else
	{
		search.tmp_ptr = *next_line;
		gnl_info->i_last_newline = gnl_info->i_last_newline
			+ search.newline_index + 1;
		*next_line = ft_str_n_join(*next_line, search.start,
				search.newline_index + 2);
		if (!*next_line)
			return (ERROR);
		free(search.tmp_ptr);
		if (search.newline_index == search.chars_left - 1)
			reset_gnl_static(gnl_info);
		return (TRUE);
	}
}

char	*reset_gnl_static_null(t_get_next *gnl_info, char **next_line)
{
	reset_gnl_static(gnl_info);
	if (*next_line)
		free(*next_line);
	return (NULL);
}

void	reset_gnl_static(t_get_next *gnl_info)
{
	gnl_info->i_last_newline = -2;
	gnl_info->total_chars_read = 0;
}

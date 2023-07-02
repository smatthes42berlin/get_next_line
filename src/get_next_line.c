/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 16:40:06 by smatthes          #+#    #+#             */
/*   Updated: 2023/07/02 20:12:47 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// read one character at a time?
// BUFFER_SIZE is buffer size for read
// realloc

// check if there is still stuff in static variable
// make static variable bigger if needed
// read one full buffer
// check if result smaller than buffer_size -> eof reached
// check if newline is contained
// yes, get everything up to newline
// save rest in static variable
// check whether

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*res;
	static char	*last_buffer_read[BUFFER_SIZE];
	static int	index_stop_last_read;

	if (fd < 0)
		return (NULL);
	fd++;
	res = malloc(sizeof(*res) * 2);
	res[0] = 'a';
	res[1] = '\0';
	return (res);
}

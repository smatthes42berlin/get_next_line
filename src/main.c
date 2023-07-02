/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:27:57 by smatthes          #+#    #+#             */
/*   Updated: 2023/07/02 19:30:05 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./get_next_line.c"
#include "./get_next_line_utils.c"
#include "test_get_next_line.h"


int	main(void)
{
	char	*file_name;
	char	*next_line;
	int		fd;

	file_name = "../srctest/test_files/empty_file.txt";
	fd = open(file_name, O_RDONLY);
	printf("fd is $%d$\n", fd);
	if (fd == -1)
		return (1);
	next_line = get_next_line(fd);
	printf("res = $%s$\n", next_line);
	fd = close(fd);
	if (fd == -1)
		return (1);
	return (0);
}

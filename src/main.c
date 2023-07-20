/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:27:57 by smatthes          #+#    #+#             */
/*   Updated: 2023/07/20 15:01:22 by smatthes         ###   ########.fr       */
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
	int		i;

	i = 0;
	file_name = "../srctest/test_files/manual_test_file.txt";
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (1);
	while (i < 16)
	{
		printf(WHITE);
		next_line = get_next_line(fd);
		if (next_line)
		{
			printf(GREEN "Call Number = $%d$\n", i + 1);
			printf("RESULT IS $%s$\n\n" WHITE, next_line);
		}
		free(next_line);
		i++;
	}
	fd = close(fd);
	if (fd == -1)
		return (1);
	return (0);
}

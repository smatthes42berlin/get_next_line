/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 19:27:57 by smatthes          #+#    #+#             */
/*   Updated: 2023/07/26 15:06:31 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.c"
#include "get_next_line_utils.c"
#include "test_get_next_line.h"

int	open_read_number_close(char *file_path, int n, char *message)
{
	char	*next_line;
	int		fd;
	int		i;

	printf(RED);
	printf("%s\n", message);
	i = 0;
	fd = open(file_path, O_RDONLY);
	if (fd == -1)
		return (0);
	while (i < n)
	{
		printf(WHITE);
		next_line = get_next_line(fd);
		if (TRUE)
		{
			printf(GREEN "Call Number = $%d$\n", i + 1);
			printf("RESULT IS $%s$\n\n" WHITE, next_line);
		}
		free(next_line);
		i++;
	}
	fd = close(fd);
	if (fd == -1)
		return (0);
	return (1);
}

int	main(void)
{
	char	*file_name;

	file_name = "../srctest/test_files/manual_test_file.txt";
	open_read_number_close(file_name, 10, "first call");
	return (0);
}

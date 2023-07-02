/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_multiple_newline_at_eof.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/02 18:13:33 by smatthes          #+#    #+#             */
/*   Updated: 2023/07/02 20:04:14 by smatthes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test_get_next_line.h"

void		setUp(void){};
void		tearDown(void){};

static int	fd_glob;

void	test(void)
{
	char	*gnl_res;

	gnl_res = get_next_line(fd_glob);
	TEST_ASSERT_EQUAL_STRING("1 line\n", gnl_res);
	gnl_res = get_next_line(fd_glob);
	TEST_ASSERT_EQUAL_STRING("2 line\n", gnl_res);
	gnl_res = get_next_line(fd_glob);
	TEST_ASSERT_EQUAL_STRING("\n", gnl_res);
	gnl_res = get_next_line(fd_glob);
	TEST_ASSERT_EQUAL_STRING("\n", gnl_res);
	gnl_res = get_next_line(fd_glob);
	TEST_ASSERT_NULL(gnl_res);
}

int	main(void)
{
	char	*file_name;
	int		fd;

	file_name = "./srctest/test_files/multiple_newline_at_eof.txt";
	fd = open(file_name, O_RDONLY);
	if (fd == -1)
		return (1);
	fd_glob = fd;
	RUN_TEST(test);
	fd = close(fd);
	if (fd == -1)
		return (1);
	return (0);
}

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    compile.sh                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/07/13 15:27:39 by smatthes          #+#    #+#              #
#    Updated: 2023/07/21 10:33:19 by smatthes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

DEF_BUFFER_SIZE=1;

if [[ $# -lt 1 ]];
then BUFFER_SIZE=$DEF_BUFFER_SIZE;
else BUFFER_SIZE=$1;
fi

clear

cc -Wall -Wextra -Werror -D BUFFER_SIZE=$BUFFER_SIZE -I./ -I../include/ -I../unity/src/ main.c && ./a.out 
# cc -Wall -Wextra -Werror -D BUFFER_SIZE=$BUFFER_SIZE -I./ -I../include/ -I../unity/src/ main.c 
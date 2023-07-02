# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: smatthes <smatthes@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/10 14:58:39 by smatthes          #+#    #+#              #
#    Updated: 2023/07/02 20:02:48 by smatthes         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# $^ -> all prerequisites with spaces in between
# $@ -> filename of the target of the rule
# $< ->  name of the first prerequisite
# $(info $(ADDHEADERLOC))


# -I Flag adds path where header files are searched during preprocessing
SHELL:=/bin/bash
BUFFERSIZE1 =1
BUFFERSIZE9999 =9999
BUFFERSIZE10MILL =10000000
CFLAGS = -Wall -Wextra -Werror -I$(PATHHEADER) -I$(PATHUNITY)

PATHUNITY = ./unity/src/
PATHSRC = ./src/
PATHTEST = ./srctest/
PATHHEADER = ./include/
PATHOBJ = ./build/obj/
PATHTESTEXE = ./build/exe/
PATHRES = ./build/results/

VPATH = $(PATHSRC) $(PATHTEST) $(PATHUNITY)

SRC = 	get_next_line.c \
	 	get_next_line_utils.c 

SRCTEST = 	test_empty_file.c \
			test_multiple_newline_at_eof.c \
			test_multiple_newline.c \
			test_newline_at_eof.c \
			test_no_newline_at_eof.c \
			test_normal_file.c
# test_very_long_line.c

OBJFNAME = $(SRC:.c=.o)
OBJ = $(patsubst %,$(PATHOBJ)%,$(OBJFNAME))

OBJTESTFNAME = $(SRCTEST:.c=.o)
OBJTEST = $(patsubst %,$(PATHOBJ)%,$(OBJTESTFNAME))

TESTRESULTFNAME = $(patsubst %.c, %.txt,$(SRCTEST))
TESTRESULT = $(patsubst %, $(PATHRES)%,$(TESTRESULTFNAME))

TESTEXEFNAME = $(patsubst %.c, %.out,$(SRCTEST))
TESTEXE = $(patsubst %, $(PATHTESTEXE)%,$(TESTEXEFNAME))

PASS = `grep -s PASS $(PATHRES)*.txt`
PASSNUM = `grep -s -c PASS $(PATHRES)*.txt`
FAIL = `grep -s FAIL $(PATHRES)*.txt`
FAILNUM = `grep -s -c FAIL $(PATHRES)*.txt`
IGNORE = `grep -s IGNORE $(PATHRES)*.txt`
IGNORENUM = `grep -s -c IGNORE $(PATHRES)*.txt`

.PHONY: all clean fclean re bonus test testunit print testwrite

# grab results from results files
test: clean cls $(TESTRESULT)
	$(call color_print_heading,$(YELLOW),IGNORES,$(IGNORENUM))
	@echo "$(IGNORE)"
	$(call color_print_heading,$(RED),FAILURES,$(FAILNUM))
	@echo "$(FAIL)"
	$(call color_print_heading,$(GREEN),PASSED,$(PASSNUM))
	@echo "$(PASS)"
	@printf "\nDONE\n"

cls:
	clear

$(PATHRES)%.txt : $(PATHTESTEXE)%.out
	-./$< > $@ 2>&1

$(PATHTESTEXE)%.out : $(PATHOBJ)%.o $(OBJ) $(PATHOBJ)unity.o
	$(CC) -o $@ $^

$(PATHOBJ)%.o: %.c
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) -c $< -o $@

clean:
	$(RM) $(OBJTEST)
	$(RM) $(TESTEXE)
	$(RM) $(TESTRESULT)
	$(RM) $(PATHOBJ)unity.o
	$(RM) $(OBJ)

# testresults: $(TESTEXE)
# 	@-printf "\n";\
# 	cd $(PATHPROJABS)$(PATHTESTEXE);\
# 	touch $(TESTRESULTUNITY); \
# 	./$(TESTEXENAME) > $(TESTRESULTUNITY) 2>&1 

# $(TESTEXE):: $(OBJTEST) $(PATHOBJ)unity.o
# 	$(LINK) -o $@ $^ -L. $(NAME)

# testunit: libft $(PATHOBJ)unity.o
# 	$(eval CFLAGS := $(CFLAGS) $(patsubst %,-I$(BASEPATHSRC)%,$(SUBFOLDERSRC)))
# 	@for unit_file in $(SRCTESTUNITPATH); do \
# 		$(CC) $(CFLAGS) $(ADDHEADERLOC) $$unit_file $(PATHOBJ)unity.o -L. $(NAME) -o test.out;\
# 		./test.out; \
# 		rm test.out; \
# 	done


# clean: testclean
# 	make -C libft clean
# 	$(RM) $(OBJ)

# testclean:
# 	$(RM) $(OBJTEST)
# 	$(RM) $(RESULTS)
# 	$(RM) $(TESTEXE)
# 	$(RM) $(TESTRESULT)
# 	$(RM) $(PATHOBJ)unity.o

# fclean: clean
# 	make -C libft fclean
# 	$(RM) $(NAME)

# re: fclean all

.PRECIOUS: $(TESTEXE)
.PRECIOUS: $(PATHOBJ)%.o
.PRECIOUS: $(PATHRES)%.txt

BLACK=0
RED=1
GREEN=2
YELLOW=3
BLUE=4
MAGENTA=5
CYAN=6
WHITE=7

define color_print_heading
    @tput setaf $1
	@printf "\n"
	@printf "%-20s%-s%-s%-20s" "************" $2 "($3)" "************"
	@printf "\n\n"
    @tput sgr0
endef

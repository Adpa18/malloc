##
## Makefile for PSU_2015_malloc
##
## Made by	Adrien WERY
## Login	wery_a
##
## Started on	Mon Feb 01 15:12:24 2016 Adrien WERY
## Last update	Mon Feb 01 15:12:24 2016 Adrien WERY
##


CC		=	gcc

RM 		=	rm -rf

NAME	=	libmy_malloc.so

SRC		= 	src/malloc.c	\
			src/calloc.c	\
			src/realloc.c	\
			src/free.c		\
			src/show.c		\

CFLAGS 	=	-W -Wall -Wextra -Werror -O2 -fPIC

LDFLAGS =	-shared

OBJ		= 	$(SRC:.c=.o)

$(NAME)	: 	$(OBJ)
	$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

all		: 	$(NAME)

clean	:
	$(RM) $(OBJ)

fclean	: 	clean
	$(RM) $(NAME)

re		: 	fclean all

.PHONY	: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msidqi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 00:08:25 by msidqi            #+#    #+#              #
#    Updated: 2018/11/25 22:04:07 by msidqi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft.a
LIBFTL = src/libft/libft.a
EXE = fractol
SRC = src/*.c
INCLUDE = Include
OBJ = *.o
GLIB = libgl.a
CC = gcc -Wall -Wextra -Werror 
FLAGS = -lmlx -framework OpenGl -framework Appkit


all : $(EXE)

$(GLIB) : 
	$(CC) -c $(SRC) -I $(INCLUDE)
	ar rc $(GLIB) $(OBJ)
	ranlib $(GLIB)
$(LIBFTL) : 
	make re -C src/libft 
$(EXE) : $(LIBFTL) $(GLIB)
	$(CC) -o $(EXE) $(SRC) $(GLIB) src/libft/libft.a -I $(INCLUDE) $(FLAGS)

clean : 
	rm -rf $(OBJ) $(GLIB) $(LIBFTL)
	make clean -C src/libft
fclean : clean
	rm -rf $(EXE)
	make fclean -C src/libft
re : fclean all

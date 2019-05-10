# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: msidqi <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/11/23 00:08:25 by msidqi            #+#    #+#              #
#    Updated: 2019/05/10 06:15:29 by msidqi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft.a
LIBMLXL = libmlx.a
LIBFTL = src/libft/libft.a
GLIB = libgl.a
LIBMLXL = src/minilibx_macos/libmlx.a
NAME = fractol
SRC_PATH = src/
SRC = ft_event_system.c ft_events_keyboard.c ft_fractal_sets.c ft_multi_thread.c main.c ft_events.c ft_fractal_func.c ft_image_setup.c
INCLUDE = Include
OBJ = $(SRC:.c=.o)
GLIB = libgl.a
CC = gcc -Wall -Wextra -Werror 
FLAGS = -framework OpenGl -framework Appkit

all : $(NAME)

$(GLIB) : 
	@$(CC) -c $(addprefix $(SRC_PATH),$(SRC)) -I $(INCLUDE)
	@ar rc $(GLIB) $(OBJ)
	@ranlib $(GLIB)
$(LIBFTL) : 
	@make re -C $(SRC_PATH)libft
	@make re -C $(SRC_PATH)minilibx_macos	
$(NAME) : $(LIBFTL) $(GLIB)
	@$(CC) -o $(NAME) $(GLIB) $(LIBFTL) $(LIBMLXL) -I $(INCLUDE) $(FLAGS)

clean : 
	@rm -rf $(OBJ) $(GLIB) $(LIBFTL)
	@make clean -C $(SRC_PATH)libft
	@make clean -C $(SRC_PATH)minilibx_macos
fclean : clean
	@rm -rf $(NAME)
	@make fclean -C $(SRC_PATH)libft
re : fclean all

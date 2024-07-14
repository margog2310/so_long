# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mganchev <mganchev@student.42london.com    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/30 20:24:28 by mganchev          #+#    #+#              #
#    Updated: 2024/07/14 23:51:24 by mganchev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

INCLUDE = ./include
LIBFT = ./libft
MLX = ./minilibx-linux

CC = cc
CFLAGS = -Wall -Werror -Wextra -g3

SRCDIR =./sources
OBJDIR =./build

SRCS = $(SRCDIR)/main.c $(SRCDIR)/game_win.c $(SRCDIR)/movement.c $(SRCDIR)/sprites.c \
$(SRCDIR)/so_long_utils.c $(SRCDIR)/get_next_line.c $(SRCDIR)/ft_printf.c $(SRCDIR)/map_file.c \
$(SRCDIR)/map_errors.c $(SRCDIR)/find_path.c $(SRCDIR)/map.c $(SRCDIR)/render.c \
$(SRCDIR)/game_loop.c $(SRCDIR)/close_game.c $(SRCDIR)/collision.c $(SRCDIR)/animation.c \
$(SRCDIR)/coins.c

BONUS_SRCS = $(SRCDIR)/main.c $(SRCDIR)/game_win.c $(SRCDIR)/movement.c $(SRCDIR)/sprites.c \
$(SRCDIR)/so_long_utils.c $(SRCDIR)/get_next_line.c $(SRCDIR)/ft_printf.c $(SRCDIR)/map_file.c \
$(SRCDIR)/map_errors_bonus.c $(SRCDIR)/find_path.c $(SRCDIR)/map.c $(SRCDIR)/render.c \
$(SRCDIR)/game_loop.c $(SRCDIR)/close_game.c $(SRCDIR)/collision.c $(SRCDIR)/animation.c \
$(SRCDIR)/enemies.c $(SRCDIR)/coins.c

OBJS = $(OBJDIR)/main.o $(OBJDIR)/game_win.o $(OBJDIR)/movement.o $(OBJDIR)/sprites.o \
$(OBJDIR)/so_long_utils.o $(OBJDIR)/get_next_line.o $(OBJDIR)/ft_printf.o $(OBJDIR)/map_file.o \
$(OBJDIR)/map_errors.o $(OBJDIR)/find_path.o $(OBJDIR)/map.o $(OBJDIR)/render.o \
$(OBJDIR)/game_loop.o $(OBJDIR)/close_game.o $(OBJDIR)/collision.o $(OBJDIR)/animation.o \
$(OBJDIR)/coins.o

BONUS_OBJS = $(OBJDIR)/main.o $(OBJDIR)/game_win.o $(OBJDIR)/movement.o $(OBJDIR)/sprites.o \
$(OBJDIR)/so_long_utils.o $(OBJDIR)/get_next_line.o $(OBJDIR)/ft_printf.o $(OBJDIR)/map_file.o \
$(OBJDIR)/map_errors_bonus.o $(OBJDIR)/find_path.o $(OBJDIR)/map.o $(OBJDIR)/render.o \
$(OBJDIR)/game_loop.o $(OBJDIR)/close_game.o $(OBJDIR)/collision.o $(OBJDIR)/animation.o \
$(OBJDIR)/enemies.o $(OBJDIR)/coins.o

all: $(OBJDIR) $(NAME)

bonus: $(OBJDIR) $(BONUS_OBJS)
	@make -C $(LIBFT)
	@make -C $(LIBFT) bonus
	@make -C $(MLX)
	$(CC) $(CFLAGS) -L$(MLX) -L$(LIBFT) $(BONUS_OBJS) -lmlx -lXext -lX11 -lm -lft -o $(NAME)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFT) -I$(MLX) -c $< -o $@

$(OBJDIR)/%.o: $(BONUS_SRCDIR)/%.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -I$(INCLUDE) -I$(LIBFT) -I$(MLX) -c $< -o $@

${NAME}: $(OBJS)
	@make -C $(LIBFT)
	@make -C $(LIBFT) bonus
	@make -C $(MLX)
	$(CC) $(CFLAGS) -L$(MLX) -L$(LIBFT) $(OBJS) -lmlx -lXext -lX11 -lm -lft -o $(NAME)

clean:
	@make clean -C $(MLX)
	@make clean -C $(LIBFT)
	@rm -rf $(OBJDIR)

fclean:
	@make clean -C $(MLX)
	@make fclean -C $(LIBFT)
	@rm -rf $(OBJDIR)
	@rm -f $(NAME)

re: fclean all

test: all
	./$(NAME)

leaks: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) map.ber

bonus_leaks: bonus
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(NAME) big_map.ber

.PHONY: all clean fclean re libft mlx bonus leaks
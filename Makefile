CC := gcc
FLAGS := -Wall -Wextra -Werror
FLAG_LINUX :=  -Iincludes/mlx_linux -Lincludes/mlx_linux -lmlx -L/usr/lib -lXext -lX11 -lm
FLAG_MACOS :=  -Lmlx -lmlx -lm -framework OpenGL -framework AppKit
RM := rm -f

# COLORS
CLR_RMV := \033[0m
RED := \033[1;31m
GREEN := \033[1;32m
YELLOW := \033[1;33m
BLUE := \033[1;34m
CYAN := \033[1;36m

# LIBFT
LIBFT = ./includes/libft/libft.a

NAME := cub3d

SRCS := srcs/main.c \
		srcs/check/check_args.c \
		srcs/check/check_map_utils.c \
		srcs/check/check_map.c \
		srcs/check/check.c \
		srcs/utils/error.c \
		srcs/game/game.c \
		srcs/utils/init.c \
		srcs/game/mlx_handle.c \
		srcs/game/move.c \
		srcs/render/render_utils.c \
		srcs/render/render.c \
		srcs/utils/utils.c \
        includes/get_next_line/get_next_line.c \
        includes/get_next_line/get_next_line_utils.c


OBJSDIR = objects
OBJS := $(addprefix $(OBJSDIR)/, $(SRCS:.c=.o))

.c.o:
	$(CC) $(FLAGS) -c $< -o $@


UNAME := $(shell uname)

#MAKE RULES

ifeq ($(UNAME), Darwin)
$(NAME): $(OBJS)
	$(MAKE) bonus -C ./includes/libft
	@echo "$(GREEN)Compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@$(MAKE) -C mlx all >/dev/null 2>&1
	@cp ./mlx/libmlx.a .
	$(CC) $(FLAGS) -g3 -Ofast -o $(NAME) -Imlx $(OBJS) $(FLAG_MACOS) $(LIBFT)
	@echo "$(GREEN)$(NAME) created [0m ✔️"
endif

ifeq ($(UNAME), Linux)
$(NAME): $(OBJS)
	$(MAKE) bonus -C ./includes/libft
	@echo "$(GREEN)Linux compilation $(CLR_RMV)of $(YELLOW)$(NAME) $(CLR_RMV)..."
	@chmod 777 includes/mlx_linux/configure
	@$(MAKE) -C includes/mlx_linux all
	$(CC) $(FLAGS) -g3 -o $(NAME) $(OBJS) $(FLAG_LINUX) $(LIBFT)
	@echo "$(GREEN)$(NAME) created [0m ✔️"
endif

all: $(NAME)

$(OBJSDIR)/%.o: %.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	@$(RM) $(OBJS)
	@rm -rf $(NAME).dSYM >/dev/null 2>&1
	$(MAKE)	clean -C ./includes/libft
	@echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)objs ✔️"

ifeq ($(UNAME), Darwin)
fclean: clean
	@$(RM) $(NAME) -rf $(OBJSDIR)
	$(MAKE) fclean -C ./includes/libft
	@rm libmlx.a
	@echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

ifeq ($(UNAME), Linux)
fclean: clean
	@$(RM) $(NAME) -rf $(OBJSDIR)
	@$(MAKE) -C ./includes/mlx_linux clean 
	$(MAKE) fclean -C ./includes/libft
	@echo "$(RED)Deleting $(CYAN)$(NAME) $(CLR_RMV)binary ✔️"
endif

re: fclean all

.PHONY: all clean fclean re

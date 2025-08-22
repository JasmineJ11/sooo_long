NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror

# Directories
LIBFT_PATH = libft
MLX_DIR = MLX42
O_DIR = objdir

# Files
SRCS = so_long.c free.c validation.c utils.c ini_game.c ini_game_helper.c engine.c engine_col_exit.c movement.c free_graphics.c
OBJS = $(addprefix $(O_DIR)/,$(SRCS:.c=.o))

# Libraries
LIBFT = $(LIBFT_PATH)/libft.a
MLX_LIB = $(MLX_DIR)/build/libmlx42.a -ldl -lglfw -pthread -lm

# Headers
HEADERS = -I. -I$(MLX_DIR)/include -I$(LIBFT_PATH) 

# Main targets
all: $(MLX_DIR) $(LIBFT)  $(NAME) 

# Clone and build MLX42
$(MLX_DIR):
	git clone https://github.com/codam-coding-college/MLX42.git $(MLX_DIR)
	cmake $(MLX_DIR) -B $(MLX_DIR)/build && make -C $(MLX_DIR)/build -j4

# Build libraries
$(LIBFT):
	$(MAKE) -C $(LIBFT_PATH)

# Create object directory
$(O_DIR):
	mkdir -p $@

# Compile object files
$(O_DIR)/%.o: %.c so_long.h | $(O_DIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)

# Link final executable
$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX_LIB) -o $(NAME)

# Clean targets
clean:
	rm -rf $(O_DIR) $(MLX_DIR)
	$(MAKE) clean -C $(LIBFT_PATH)
	

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_PATH)
	

re: fclean all

.SILENT:
.PHONY: all clean fclean re
.SECONDARY: $(OBJS)
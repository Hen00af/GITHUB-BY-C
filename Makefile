CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinclude
NAME = mygit
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
SRCS = $(wildcard $(SRC_DIR)/*.c)
OBJS = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) -o $@ $^
	@echo "🚀 Compilation successful! Launching into productivity mode!"


$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

all: $(NAME)

clean:
	@rm -rf $(OBJ_DIR)
	@echo clean is done

fclean: clean
	@rm -f $(NAME)
	@rm -rf .mygit
	@echo fclean is done

re: fclean all

.PHONY: all clean fclean re

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/09 18:41:58 by mgodawat          #+#    #+#              #
#    Updated: 2025/04/11 14:06:16 by mgodawat         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


# Color codes
RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
BLUE = \033[0;34m
PURPLE = \033[0;35m
CYAN = \033[0;36m
WHITE = \033[0;37m
NC = \033[0m # No Color

# Program name
NAME = philo

# Directory paths and header
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
HEADER = $(INC_DIR)/philo.h

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

# Source files
SRC_FILES = main.c ft_atol.c err_utils.c debug.c phils_utils.c \
			time_utils.c routine.c monitor_utils.c \

OBJ_FILES = $(SRC_FILES:.c=.o)
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Rules
all: $(NAME)

# Build the program
$(NAME): $(OBJS)
	@echo "$(YELLOW)🔨 Linking objects...$(NC)"
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Build complete! Binary created: $(WHITE)$(NAME)$(NC)"

# Compile source files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)⚡ Compiling: $(WHITE)$<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✨ Object files cleaned!$(NC)"

# Clean everything
fclean: clean
	@echo "$(PURPLE)🗑️  Removing executable...$(NC)"
	@rm -f $(NAME)
	@echo "$(GREEN)🌟 All files cleaned!$(NC)"

# Rebuild everything
re: fclean all
	@echo "$(GREEN)✅ Project rebuilt successfully!$(NC)"

.PHONY: all clean fclean re

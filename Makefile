# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 21:11:53 by mgodawat          #+#    #+#              #
#    Updated: 2025/02/22 18:48:43 by mgodawat         ###   ########.fr        #
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
CFLAGS = -Wall -Wextra -Werror -g -I$(INC_DIR)

# Source files
SRC_FILES = main.c debug.c utils.c

OBJ_FILES = $(SRC_FILES:.c=.o)
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Rules
all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(YELLOW)🔨 Linking objects...$(NC)"
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@echo "$(GREEN)✅ Build complete! Binary created: $(WHITE)$(NAME)$(NC)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADER)
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)⚡ Compiling: $(WHITE)$<$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(YELLOW)🧹 Cleaning object files...$(NC)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)✨ Object files cleaned!$(NC)"

fclean: clean
	@echo "$(PURPLE)🗑️  Removing executable...$(NC)"
	@rm -rf $(NAME)
	@echo "$(GREEN)🌟 All files cleaned!$(NC)"

re: fclean
	@echo "$(CYAN)🔄 Rebuilding project...$(NC)"
	@$(MAKE) all
	@echo "$(GREEN)✅ Project rebuilt successfully!$(NC)"

.PHONY: all clean fclean re banner

help:
	@echo "$(CYAN)📚 Available commands:$(NC)"
	@echo "$(WHITE)make all    $(BLUE)→$(NC) Build the project"
	@echo "$(WHITE)make clean  $(BLUE)→$(NC) Remove object files"
	@echo "$(WHITE)make fclean $(BLUE)→$(NC) Remove object files and executable"
	@echo "$(WHITE)make re     $(BLUE)→$(NC) Rebuild the project"
	@echo "$(WHITE)make help   $(BLUE)→$(NC) Show this help message"


# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/21 21:11:53 by mgodawat          #+#    #+#              #
#    Updated: 2025/03/28 19:01:04 by mgodawat         ###   ########.fr        #
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

# Program name and arguments for testing
NAME = philo
TEST_ARGS = 2 800 200 200

# Directory paths and header
SRC_DIR = src
OBJ_DIR = obj
INC_DIR = include
HEADER = $(INC_DIR)/philo.h

# Compiler and flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -I$(INC_DIR)

# Debug flags
DEBUG = -g -pthread
TSAN = -fsanitize=thread
ASAN = -fsanitize=address

# Valgrind flags
VALGRIND_FLAGS = --leak-check=full --show-leak-kinds=all --track-origins=yes
HELGRIND_FLAGS = --tool=helgrind
DRD_FLAGS = --tool=drd

# Source files
SRC_FILES = main.c ft_atol.c err_utils.c debug.c simul.c gs.c sync_utils.c\

OBJ_FILES = $(SRC_FILES:.c=.o)
SRCS = $(addprefix $(SRC_DIR)/, $(SRC_FILES))
OBJS = $(addprefix $(OBJ_DIR)/, $(OBJ_FILES))

# Rules
all: $(NAME)

# Debug build with symbols and DEBUG flag enabled
debug: CFLAGS += $(DEBUG) -DDEBUG
debug: clean $(NAME)
	@echo "$(GREEN)✅ Built with debug symbols and DEBUG flag enabled$(NC)"

# Thread sanitizer build with DEBUG flag
tsan: CFLAGS += $(DEBUG) $(TSAN) -DDEBUG
tsan: clean $(NAME)
	@echo "$(GREEN)✅ Built with thread sanitizer and DEBUG flag enabled$(NC)"
	@echo "$(YELLOW)🚀 Run with: ./$(NAME) $(TEST_ARGS)$(NC)"

# Address sanitizer build with DEBUG flag
asan: CFLAGS += $(DEBUG) $(ASAN) -DDEBUG
asan: clean $(NAME)
	@echo "$(GREEN)✅ Built with address sanitizer and DEBUG flag enabled$(NC)"
	@echo "$(YELLOW)🚀 Run with: ./$(NAME) $(TEST_ARGS)$(NC)"

# Valgrind memory check
valgrind: debug
	@echo "$(YELLOW)🔍 Running valgrind memory check...$(NC)"
	@valgrind $(VALGRIND_FLAGS) ./$(NAME) $(TEST_ARGS)

# Helgrind thread check
helgrind: debug
	@echo "$(YELLOW)🔍 Running helgrind thread check...$(NC)"
	@valgrind $(HELGRIND_FLAGS) ./$(NAME) $(TEST_ARGS)

# DRD thread check
drd: debug
	@echo "$(YELLOW)🔍 Running DRD thread check...$(NC)"
	@valgrind $(DRD_FLAGS) ./$(NAME) $(TEST_ARGS)

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

# Run tests with different configurations
test: all
	@echo "$(CYAN)🧪 Running basic test...$(NC)"
	./$(NAME) $(TEST_ARGS)

test_all: test tsan asan valgrind helgrind drd
	@echo "$(GREEN)✅ All tests completed!$(NC)"

# Show help
help:
	@echo "$(CYAN)📚 Available commands:$(NC)"
	@echo "$(WHITE)make        	$(BLUE)→$(NC) Build the project (no debug output)"
	@echo "$(WHITE)make debug  	$(BLUE)→$(NC) Build with debug symbols and DEBUG output"
	@echo "$(WHITE)make tsan   	$(BLUE)→$(NC) Build with thread sanitizer and DEBUG output"
	@echo "$(WHITE)make asan   	$(BLUE)→$(NC) Build with address sanitizer and DEBUG output"
	@echo "$(WHITE)make valgrind	$(BLUE)→$(NC) Run with valgrind memory checker"
	@echo "$(WHITE)make helgrind	$(BLUE)→$(NC) Run with helgrind thread checker"
	@echo "$(WHITE)make drd    	$(BLUE)→$(NC) Run with DRD thread checker"
	@echo "$(WHITE)make test   	$(BLUE)→$(NC) Run basic test"
	@echo "$(WHITE)make test_all	$(BLUE)→$(NC) Run all tests"
	@echo "$(WHITE)make clean  	$(BLUE)→$(NC) Remove object files"
	@echo "$(WHITE)make fclean 	$(BLUE)→$(NC) Remove object files and executable"
	@echo "$(WHITE)make re     	$(BLUE)→$(NC) Rebuild the project"
	@echo "$(WHITE)make help    	$(BLUE)→$(NC) Show this help message"

.PHONY: all debug tsan asan valgrind helgrind drd clean fclean re \
		test test_all help

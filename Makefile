# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 10:23:52 by cdomet-d          #+#    #+#              #
#    Updated: 2024/03/27 09:34:28 by cdomet-d         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := minishell
LIB := libft.a
BUILD_DIR := .dir_build
LIBFT_DIR := libft

CC := cc
CFLAGS := -Werror -Wextra -Wall -g3
CPPFLAGS = -MMD -MP
MAKEFLAGS += --no-print-directory

INCLUDES := -lft 
#-L/usr/local/lib -I/usr/local/include -lreadline

SRCS := display.c \
		env_lst_utils.c \
		error_handling.c \
		exec.c \
		exec_utils.c \
		input_lst_utils.c \
		local_functions.c \
		test_main.c \
		builtins.c \

OBJS := $(addprefix $(BUILD_DIR)/, $(SRCS:%.c=%.o))
DEPS := $(OBJS:%.o=%.d)

RM := rm -rf

all: $(NAME)
bonus : $(BONUS)

$(NAME): $(LIBFT_DIR)/$(LIB) $(OBJS)
	@echo
	@echo "$(PURPLE)|========== \t\t Making minishell \t\t ===========|$(RESET)"
	@echo
	$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT_DIR) -o $(NAME) $(INCLUDES)
	@echo
	@echo "$(GREEN)|=========== \t\t minishell done ! \t\t ===========|$(RESET)"
	@echo
	
$(BUILD_DIR)/%.o:%.c minishell.h $(LIBFT_DIR)/libft.h Makefile
	@mkdir -p $(BUILD_DIR)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(LIBFT_DIR)/$(LIB): FORCE
	@echo "$(FAINT)"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(RESET)"

 -include $(DEPS)

clean:
	@echo
	@echo "$(CYAN)|========== \t\t Running clean... \t ===========|$(RESET)"
	@echo "$(FAINT)"
	$(RM) $(BUILD_DIR)
	make -C $(LIBFT_DIR) $@
	@echo "$(RESET)"
	@echo "$(CYAN)|=========== \t\t Done ! \t\t ===========|$(RESET)"
	@echo
	
fclean: clean
	@echo "$(CYAN)|========== \t\t Running fclean... \t ===========|$(RESET)"
	@echo "$(FAINT)"
	make -C $(LIBFT_DIR) $@
	$(RM) $(NAME) $(BONUS) out
	@echo "$(RESET)"
	@echo "$(CYAN)|========== \t\t Bye <3 \t\t ===========|$(RESET)"
	@echo

re: fclean all

help:
	@echo "make \t\t $(FAINT)creates the executable$(RESET)"
	@echo "make bonus \t $(FAINT)creates the bonus executable$(RESET)"
	@echo "make clean \t $(FAINT)deletes object files & dependencies$(RESET)"
	@echo "make fclean \t $(FAINT)deletes everything the makefile created$(RESET)"
	@echo "make kitty \t $(FAINT)prints a lil kitty on the terminal$(RESET)"
	@echo "make re \t $(FAINT)deletes all objects & dependencies and recompiles the executable$(RESET)"
	@echo "make re_bonus \t $(FAINT)deletes all objects & dependencies and recompiles the bonus$(RESET)"

kitty:
	@echo "   |\__/,|   ( \  "
	@echo " _.|o o  |_   ) ) "
	@echo "-(((---(((--------"

# Colors
BLUE=\033[0;34m
CYAN=\033[0;36m
GREEN=\033[32m
PURPLE=\033[35m
BG_CYAN=\033[46m

# Text
RESET=\033[0m
FAINT=\033[2m
UNDERLINE=\033[4m

FORCE : 
.PHONY : clean fclean all re help kitty display force
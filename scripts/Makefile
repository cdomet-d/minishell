# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cdomet-d <cdomet-d@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 10:23:52 by cdomet-d          #+#    #+#              #
#    Updated: 2024/03/28 17:30:13 by cdomet-d         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME := minishell
LIB := libft.a
BUILD_DIR := .dir_build
LIBFT_DIR := ../libft
MS_H := minishell.h
EX_H := exec.h
PATHS := ../lst_utils/ ../test_units/ ../builtins/ ../error_management/

CC := cc
CFLAGS := -Werror -Wextra -Wall -g3
CPPFLAGS = -MMD -MP
MAKEFLAGS += --no-print-directory

INCLUDES := -L $(LIBFT_DIR) -lft 
#-L/usr/local/lib -I/usr/local/include -lreadline

SRCS := env_lst_utils.c \
		input_lst_utils.c \
		display.c \
		init_input.c \
		export.c \
		unset.c \
		error_handling.c \
		exec_main.c \
		export_main.c \
		unset_main.c \

SRCS := $(foreach path,$(PATHS),$((path %.c))
OBJS := $(addprefix $(BUILD_DIR)/,$(SRCS:%.c=%.o))
DEPS := $(OBJS:%.o=%.d)

RM := rm -rf

all: $(NAME)
bonus : $(BONUS)

$(NAME): $(LIBFT_DIR)/$(LIB) $(OBJS)
	@echo
	@echo "$(PURPLE)|========== \t\t Making minishell \t\t ===========|$(RESET)"
	@echo
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES)
	@echo
	@echo "$(GREEN)|=========== \t\t minishell done ! \t\t ===========|$(RESET)"
	@echo
	
$(BUILD_DIR)/%.o: %.c $(LIBFT_DIR)/libft.h $(MS_H) $(EX_H) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(LIBFT_DIR)/$(LIB): FORCE
	@echo "$(FAINT)"
	$(MAKE) -C $(LIBFT_DIR)
	@echo "$(RESET)"

unset: $(LIBFT_DIR)/$(LIB) $(OBJS)
	@echo
	@echo "$(PURPLE)|========== \t\t Making main1 \t\t ===========|$(RESET)"
	@echo
	$(CC) $(CFLAGS) $(BUILD_DIR)/test_units/unset_main.o -o unset_main $(INCLUDES)
	@echo
	@echo "$(GREEN)|=========== \t\t main1 done ! \t\t ===========|$(RESET)"
	@echo

main2: $(LIBFT_DIR)/$(LIB) $(OBJS)
	@echo
	@echo "$(PURPLE)|========== \t\t Making main2 \t\t ===========|$(RESET)"
	@echo
	$(CC) $(CFLAGS) $(BUILD_DIR)/main2.o -o main2 $(INCLUDES)
	@echo
	@echo "$(GREEN)|=========== \t\t main2 done ! \t\t ===========|$(RESET)"
	@echo

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
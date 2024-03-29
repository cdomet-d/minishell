# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/07 10:23:52 by cdomet-d          #+#    #+#              #
#    Updated: 2024/03/29 17:19:11 by csweetin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME := minishell
LIB := libft.a
BUILD_DIR := .dir_build/
LIBFT_DIR := includes/libft/
MS_H := includes/minishell.h
EX_H := includes/exec.h
PA_H := includes/parsing.h
HEADERS:= -I includes/ -I includes/libft/

SCR_DIR := src/

CC := cc
CFLAGS := -Werror -Wextra -Wall -g3 $(HEADERS)
CPPFLAGS = -MMD -MP
MAKEFLAGS += --no-print-directory

INCLUDES := -L $(LIBFT_DIR) -lft -lreadline

SRC += main.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ PARSING ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
PARSE += $(addprefix $(DIR_TOKE), $(SRC_TOKE))
DIR_TOKE:= parsing/tokenization/
SRC_TOKE:=		create_data.c \
				tokenization.c \
				tokenization_utils.c \
				toke_op.c \

PARSE += $(addprefix $(DIR_EXPAND), $(SRC_EXPAND))
DIR_EXPAND:= parsing/expansion/
SRC_EXPAND:=	expansion.c \
				expansion_utils.c \

SRC += $(PARSE)

SRC +=  $(addprefix $(DIR_PARSE), $(SRC_PARSE))
DIR_PARSE:= parsing/
SRC_PARSE:=		create_lst.c \
				parsing.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ LISTS ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC +=  $(addprefix $(DIR_LST), $(SRC_LST))
DIR_LST:= lst_utils/
SRC_LST:=		env_lst_utils.c \
				input_lst_utils.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ BUILTINS ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC +=  $(addprefix $(DIR_BUILTIN), $(SRC_BUILTIN))
DIR_BUILTIN:= builtins/
SRC_BUILTIN:=	export.c \
				unset.c \
				exit.c \
				builtin_utils.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ UTILS ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC +=  $(addprefix $(DIR_UTILS), $(SRC_UTILS))
DIR_UTILS:= utils/
SRC_UTILS:=		display_data.c \
				display_structs.c \
				init_input.c \
				error_handling.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ EXEC ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC +=  $(addprefix $(DIR_EXEC), $(SRC_EXEC))
DIR_EXEC:= exec/
SRC_EXEC:=		exec.c \
				exec_utils.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ RULES ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #

OBJS:= $(addprefix $(BUILD_DIR),$(SRC:%.c=%.o))
DEPS:= $(OBJS:%.o=%.d)

RM := rm -rf

all: $(NAME)
bonus : $(BONUS)

$(NAME): $(LIBFT_DIR)$(LIB) $(OBJS)
	@echo
	@echo "$(PINK)$(BOLD) \t • • ┈┈┈┈ ๑ ⋅ ⋯ ୨ \t making minishell \t ୧ ⋯ ⋅ ๑ ┈┈┈┈ • •$(RESET)"
	@echo
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES)
	@echo
	@echo "$(PINK)$(BOLD) \t• • ┈┈┈┈ ๑ ⋅ ⋯ ୨ \t minishell done ! \t ୧ ⋯ ⋅ ๑ ┈┈┈┈ • •$(RESET)"
	@echo
	
$(BUILD_DIR)%.o: $(SCR_DIR)%.c $(LIBFT_DIR)libft.h $(MS_H) $(EX_H) $(PA_H) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(LIBFT_DIR)$(LIB): FORCE
	@echo "$(FAINT)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(RESET)"

 -include $(DEPS)

clean:
	@echo
	@echo "$(PINK)$(BOLD)\t • • ┈┈┈┈ ๑ ⋅ ⋯ ୨ \t cleaning \t ୧ ⋯ ⋅ ๑ ┈┈┈┈ • •$(RESET)"
	@echo
	@echo "$(FAINT)"
	$(RM) $(BUILD_DIR)
	make -C $(LIBFT_DIR) $@

	
fclean: clean
	make -C $(LIBFT_DIR) $@
	$(RM) $(NAME)
	@echo
	@echo "$(PINK)$(BOLD)\t • • ┈┈┈┈ ๑ ⋅ ⋯ ୨ \t done ! \t ୧ ⋯ ⋅ ๑ ┈┈┈┈ • •$(RESET)"
	@echo

	
re: fclean all

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #

V_PARAMS:= valgrind --leak-check=full --suppressions=supp.supp --show-leak-kinds=all
suprun: all
	$(V_PARAMS) ./$(NAME)

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

FORCE : 
print% :
	@echo $(patsubst print%,%,$@)=
	@echo $($(patsubst print%,%,$@))

.PHONY : clean fclean all re help kitty display force print%

# Text
RESET=\033[0m
FAINT=\033[2m
UNDERLINE=\033[4m
BOLD=\033[1m

# Codes d'échappement ANSI pour les couleurs
RED=\033[0;31m
GREEN=\033[0;32m
YELLOW=\033[0;33m
BLUE=\033[0;34m
MAGENTA=\033[0;35m
CYAN=\033[0;36m
WHITE=\033[0;37m
PINK=\033[38;5;206m.

# Codes d'échappement ANSI pour le texte en gras
BOLD=\033[1m

# Codes d'échappement ANSI pour les fonds colorés
BG_RED=\033[41m
BG_GREEN=\033[42m
BG_YELLOW=\033[43m
BG_BLUE=\033[44m
BG_MAGENTA=\033[45m
BG_CYAN=\033[46m
BG_WHITE=\033[47m
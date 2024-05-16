# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: csweetin <csweetin@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: Invalid date        by                   #+#    #+#              #
#    Updated: 2024/05/16 17:52:37 by csweetin         ###   ########.fr        #
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

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ PARSING ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC += $(addprefix $(DIR_TOKE), $(SRC_TOKE))
DIR_TOKE:= parsing/tokenization/
SRC_TOKE:=		tokenization.c \
				tokenization_utils.c \
				toke_type.c \
				cmd_opt.c \
				create_data.c \

SRC += $(addprefix $(DIR_EXPAND), $(SRC_EXPAND))
DIR_EXPAND:= parsing/expansion/
SRC_EXPAND:=	expand_split.c \
				expand_split_utils.c \
				expand.c \
				expand_utils.c \

SRC +=  $(addprefix $(DIR_PARSE), $(SRC_PARSE))
DIR_PARSE:= parsing/
SRC_PARSE:=		create_lst.c \
				parsing.c \
				cmd_path.c \
				cmd_path_utils.c \
				rm_quotes.c \
				toke_builtin.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ LISTS ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC +=  $(addprefix $(DIR_LST), $(SRC_LST))
DIR_LST:= lst_utils/
SRC_LST:=		env_lst_utils.c \
				input_lst_utils.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ BUILTINS ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC +=  $(addprefix $(DIR_BUILTIN), $(SRC_BUILTIN))
DIR_BUILTIN:= builtins/
SRC_BUILTIN:=	exec_builtins.c \
				exec_builtins_utils.c \

SRC +=  $(addprefix $(DIR_BT_FUNC), $(SRC_BT_FUNC))
DIR_BT_FUNC:= builtins/bt_functs/
SRC_BT_FUNC:=	export.c \
				unset.c \
				exit.c \
				echo.c \
				env.c \
				pwd.c \
				cd.c \
				cd_utils.c \
				cd_canon_form.c \
				export_utils.c \
				builtin_utils.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ HEREDOC ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC +=  $(addprefix $(DIR_HEREDOC), $(SRC_HEREDOC))
DIR_HEREDOC:= heredoc/
SRC_HEREDOC:=	heredoc.c \
				heredoc_expand.c \
				heredoc_utils.c \
				heredoc_errors.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ UTILS ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #
SRC +=  $(addprefix $(DIR_UTILS), $(SRC_UTILS))
DIR_UTILS:= utils/
SRC_UTILS:=		display_data.c \
				display_structs_q.c \
				display_structs_v.c \
				error_handling.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ EXEC ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #

SRC +=  $(addprefix $(DIR_EXEC), $(SRC_EXEC))
DIR_EXEC:= exec/
SRC_EXEC:=		exec.c \
				redirections.c \
				exec_errors.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ SIGNALS ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #

SRC +=  $(addprefix $(DIR_SIGNAL), $(SRC_SIGNAL))
DIR_SIGNAL:= signals/
SRC_SIGNAL:=		sighandler.c \
					sig_set_stat.c \

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ UTILS ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #

SRC +=  $(addprefix $(DIR_EXEC)$(UTILS_SUBDIR), $(SRC_SUBUTILS))
UTILS_SUBDIR:=utils/
SRC_SUBUTILS:=	arenvlst.c \
				exec_utils.c \
				fd_handling.c \
				operators_utils.c \
				redirection_utils.c \

SRC +=  $(addprefix $(DIR_EXEC)$(ERR_SUBDIR), $(SRC_SUBERR))
ERR_SUBDIR:= error_handling/
SRC_SUBERR:=	

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ RULES ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #

OBJS:= $(addprefix $(BUILD_DIR),$(SRC:%.c=%.o))
DEPS:= $(OBJS:%.o=%.d)

RM := rm -rf

all: $(NAME)
bonus : $(BONUS)

$(NAME): $(LIBFT_DIR)$(LIB) $(OBJS)
	@echo
	@echo "$(PB) \t • • ┈┈┈┈ ๑ ⋅ ⋯ ୨ \t making $(NAME) \t ୧ ⋯ ⋅ ๑ ┈┈┈┈ • •$(R)"
	@echo
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) $(INCLUDES)
	@echo
	@echo "$(PB) \t• • ┈┈┈┈ ๑ ⋅ ⋯ ୨ \t $(NAME) done ! \t ୧ ⋯ ⋅ ๑ ┈┈┈┈ • •$(R)"
	@echo
	
$(BUILD_DIR)%.o: $(SCR_DIR)%.c $(LIBFT_DIR)libft.h $(MS_H) $(EX_H) $(PA_H) Makefile
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

$(LIBFT_DIR)$(LIB): FORCE
	@echo "$(FAINT)"
	@$(MAKE) -C $(LIBFT_DIR)
	@echo "$(R)"

 -include $(DEPS)

clean:
	@echo
	@echo "$(PB)\t • • ┈┈┈┈ ๑ ⋅ ⋯ ୨ \t cleaning \t ୧ ⋯ ⋅ ๑ ┈┈┈┈ • •$(R)"
	@echo
	@echo "$(FAINT)"
	$(RM) $(BUILD_DIR)
	make -C $(LIBFT_DIR) $@
	@echo "$(R)"

fclean: clean
	@echo -n "$(FAINT)"
	make -C $(LIBFT_DIR) $@
	$(RM) $(NAME)
	@echo "$(R)"
	@echo "$(PB)\t • • ┈┈┈┈ ๑ ⋅ ⋯ ୨ \t done ! \t ୧ ⋯ ⋅ ๑ ┈┈┈┈ • •$(R)"
	@echo

	
re: fclean all

CHEMIN:= $(shell pwd)
M_SUP:=$(CHEMIN)/misc/supp.supp
LOG:=$(CHEMIN)
V_PARAMS:= valgrind --trace-children=yes --track-fds=yes --leak-check=full --suppressions=$(M_SUP) --show-leak-kinds=all -s
run: all
	$(V_PARAMS) ./$(NAME) 

# ⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒⌒ #

help:
	@echo "make \t\t $(FAINT)creates the executable$(R)"
	@echo "make bonus \t $(FAINT)creates the bonus executable$(R)"
	@echo "make clean \t $(FAINT)deletes object files & dependencies$(R)"
	@echo "make fclean \t $(FAINT)deletes everything the makefile created$(R)"
	@echo "make kitty \t $(FAINT)prints a lil kitty on the terminal$(R)"
	@echo "make re \t $(FAINT)deletes all objects & dependencies and recompiles the executable$(R)"
	@echo "make re_bonus \t $(FAINT)deletes all objects & dependencies and recompiles the bonus$(R)"

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
R=\033[0m
FAINT=\033[2m
UNDERLINE=\033[4m
BOLD=\033[1m

# Codes d'échappement ANSI pour les couleurs
PB=$(PINK)$(BOLD)

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

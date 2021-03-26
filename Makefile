# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amamy <amamy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/18 19:23:29 by nivergne          #+#    #+#              #
#    Updated: 2020/08/04 21:00:40 by amamy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

ASM	= asm
VM	= corewar

include mk/include.mk
include mk/src.mk
include mk/obj.mk
include mk/colors.mk

CC = clang
CFLAGS = -Wall -Wextra -Werror
CPPFLAGS += -MMD -MP
LIB = libft/libft.a
DEPS = $(subst .o,.d,$(OBJ))

all: makelib $(ASM) $(VM)

$(ASM): $(OBJ_ASM) | makelib
	@echo "$(BOLD)$(GREEN)ASM			$(BLUE)compile$(GREEN)		[OK]$(END)"
	@$(CC) $(INC_PATH) $(OBJ_ASM) -L libft -lft -o $(ASM)

$(VM): $(OBJ_VM) | makelib
	@echo "$(BOLD)$(GREEN)VM			$(BLUE)compile$(GREEN)		[OK]$(END)"
	@$(CC) $(INC_PATH) $(OBJ_VM) -L libft -lft -o $(VM) 

makelib:
	@$(MAKE) --no-print-directory -C libft

$(OBJ_PATH)%.o: $(SRC_PATH)%.c $(INC_FILES)
	@mkdir -p obj
	@mkdir -p $(dir $@)
	@if [ "$(findstring asm,$(basename $@))" = "asm" ]; then\
		echo "$(BOLD)$(CYAN)asm		$(BLUE)$(patsubst obj/%, %, $(basename $@))		$(GREEN)[OK]$(END)";\
		printf "$(UP_LINE)";\
		printf "$(ERASE_LINE)";\
    fi;
	@if [ "$(findstring vm,$(basename $@))" = "vm" ]; then\
		echo "$(BOLD)$(CYAN)vm		$(BLUE)$(patsubst obj/%, %, $(basename $@))		$(GREEN)[OK]$(END)";\
		printf "$(UP_LINE)";\
		printf "$(ERASE_LINE)";\
    fi;
	@echo "$(BOLD)$(CYAN)corewar		$(BLUE)$(patsubst obj/%, %, $(basename $@))	$(GREEN)[OK]$(END)"	
	@printf "$(UP_LINE)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) $(INC_PATH) -o $@ -c $<
	@printf "$(ERASE_LINE)"

include mk/bitcoin.mk
include mk/debug.mk
include mk/clean.mk

re: fclean all

.PHONY: all clean fclean re makelib g3 fsanitize bitcoin minotaure bitcoin_autore

-include $(DEPS)

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    debug.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicolasv <nicolasv@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/22 23:50:50 by nivergne          #+#    #+#              #
#    Updated: 2019/11/27 03:40:34 by nicolasv         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

g3: makelib obj $(LIB) $(OBJ)
	@echo "$(BOL)$(GRN)COREWAR			$(BLU)debug$(GRN)		[OK]$(END)"
	@$(CC) $(CFLAGS) $(INC_PATH) -g3 $(OBJ) -L libft -lft -o $(NAME)_debug

fsanitize: makelib obj $(LIB) $(OBJ)
	@echo "$(BOL)$(GRN)COREWAR			$(BLU)fsanitize$(GRN)	[OK]$(END)"
	@$(CC) $(CFLAGS) $(INC_PATH) -g3 -fsanitize=address $(OBJ) $(MLX) -L libft -lft -o $(NAME)_fsanitize

debug:
	@echo "$(GREEN)SRC_ASM:$(END)"
	@echo "$(SRC_ASM)\n"
	@echo "$(GREEN)OBJ_ASM:$(END)"
	@echo "$(OBJ_ASM)\n"
	@echo "$(GREEN)SRC_VM:$(END)"
	@echo "$(SRC_VM)\n"
	@echo "$(GREEN)OBJ_VM:$(END)"
	@echo "$(OBJ_VM)\n"
	@echo "\n"
	@echo "$(GREEN)SRC_ASM:$(END)"
	@echo "$($(SRC_ASM))"
	@echo "$(GREEN)OBJ_ASM_PATH:$(END)"
	@echo "$(OBJ_ASM_PATH)"
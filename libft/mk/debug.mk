# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    debug.mk                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nivergne <nivergne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/21 01:57:13 by nicolasv          #+#    #+#              #
#    Updated: 2019/09/22 21:52:49 by nivergne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

debug:
	@echo "$(GREEN)SRC_LIBFT$(END)"
	@echo "$(SRC_LIBFT)"
	@echo "\n\n\n"
	@echo "$(GREEN)OBJ_LIBFT$(END)"
	@echo "$(OBJ_LIBFT)"
	@echo "\n\n\n"
	@echo "$(GREEN)OBJ_DIR_LIBFT$(END)"
	@echo "$(OBJ_DIR_LIBFT)"


#set_verbose:
#	UP_LINE = 0
#
#unset_verbose:
#	@$(UP_LINE) = "\x1b[A"

#INC = $(shell find include -type f | grep -e \.h$$)
#SRC = $(shell find src -type f | grep -e \.c$$)
#patsubst: remplace le deuxieme arg par le troisieme
#basename: remplace le nom en .c par le non sans le .c

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    colors.mk                                          :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amamy <amamy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/16 21:59:53 by nicolasv          #+#    #+#              #
#    Updated: 2020/07/02 15:30:38 by amamy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#special capacities
UP_LINE					=					\033[A
ERASE_LINE				=				 	\033[2K
END						=					\033[0m
BOLD					=					\033[1m
UNDER					=					\033[4m
REV						=					\033[7m

#colors
RED						=					\033[31m
GREEN					=					\033[32m
BLUE					=					\033[34m
YELLOW					=					\033[33m
CYAN					=					\033[36m
GREY					=					\033[40m
WHITE					=					\033[37m
PINK					=					\033[38;2;152;0;255m
PURPLE					=					\033[38;2;114;0;255m
DARK_PURPLE				=					\033[38;2;65;0;255m
DARK_PINK				=					\033[38;2;86;0;255m

#background colors
BACK_RED				=					\033[41m
BACK_GREEN				=					\033[42m
BACK_BLUE				=					\033[44m
BACK_YELLOW				=					\033[43m
BACK_CYAN				=					\033[46m
BACK_PURPLE				=					\033[45m
BACK_GREY				=					\033[40m
BACK_WHITE				=					\033[47m

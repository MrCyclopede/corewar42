# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    include.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amamy <amamy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/22 23:55:10 by nivergne          #+#    #+#              #
#    Updated: 2020/07/24 19:44:03 by amamy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC = include/
INC_PATH = -Iinclude/ -Ilibft/include


INC_FILES =			op.h\
					vm.h\
					asm.h\
					tokens.h\
					../libft/include/libft.h\
					../libft/include/ft_printf.h\
					../libft/include/get_next_line.h\

INC_FILES := $(addprefix $(INC), $(INC_FILES))

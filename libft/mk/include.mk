# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    include.mk                                         :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amamy <amamy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/22 23:55:10 by nivergne          #+#    #+#              #
#    Updated: 2020/07/24 19:26:03 by amamy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

INC = include/
INC_PATH = -Iinclude/ -Ilibft/include


INC_FILES =			libft.h\
					get_next_line.h\
					ft_printf.h\

INC_FILES := $(addprefix $(INC), $(INC_FILES))

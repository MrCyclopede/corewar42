# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amamy <amamy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/17 04:34:13 by nicolasv          #+#    #+#              #
#    Updated: 2020/07/23 22:59:29 by amamy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_STRING =				ft_atoi.c\
							ft_isalnum.c\
							ft_isalpha.c\
							ft_isascii.c\
							ft_isdigit.c\
							ft_isprint.c\
							ft_isspace.c\
							ft_itoa.c\
							ft_strcat.c\
							ft_strchr.c\
							ft_strclen.c\
							ft_strclr.c\
							ft_strcmp.c\
							ft_strcpy.c\
							ft_strdel.c\
							ft_strdup.c\
							ft_strequ.c\
							ft_striter.c\
							ft_striteri.c\
							ft_strjoin2.c\
							ft_strjoin.c\
							ft_strjoin_f.c\
							ft_strjoinf_nico.c\
							ft_strjoinfree.c\
							ft_strlcat.c\
							ft_strlen.c\
							ft_strmap.c\
							ft_strmapi.c\
							ft_strncat.c\
							ft_strncmp.c\
							ft_strncpy.c\
							ft_strnequ.c\
							ft_strnew.c\
							ft_strnstr.c\
							ft_strrchr.c\
							ft_strretri.c\
							ft_strrev.c\
							ft_strsplit.c\
							ft_strstr.c\
							ft_strsub.c\
							ft_strswap.c\
							ft_strtrim.c\
							ft_tolower.c\
							ft_toupper.c\


SRC_STRING := $(addprefix string/, $(SRC_STRING))
OBJ_STRING := $(addprefix string/, $(addsuffix .o, $(basename $(notdir $(SRC_STRING)))))

SRC_MEMORY =				ft_bzero.c\
							ft_memalloc.c\
							ft_memccpy.c\
							ft_memchr.c\
							ft_memcmp.c\
							ft_memcpy.c\
							ft_memdel.c\
							ft_memmove.c\
							ft_memset.c\

		
SRC_MEMORY := $(addprefix memory/, $(SRC_MEMORY))
OBJ_MEMORY := $(addprefix memory/, $(addsuffix .o, $(basename $(notdir $(SRC_MEMORY)))))

SRC_LIST =					ft_lstadd.c\
							ft_lstdel.c\
							ft_lstdelone.c\
							ft_lstiter.c\
							ft_lstmap.c\
							ft_lstnew.c\

SRC_LIST := $(addprefix list/, $(SRC_LIST))
OBJ_LIST := $(addprefix list/, $(addsuffix .o, $(basename $(notdir $(SRC_LIST)))))

SRC_WRITE = 				ft_putchar.c\
							ft_putchar_fd.c\
							ft_putendl.c\
							ft_putendl_fd.c\
							ft_putnbr.c\
							ft_putnbr_fd.c\
							ft_putstr.c\
							ft_putstr_fd.c\
							ft_puttab.c\


SRC_WRITE := $(addprefix write/, $(SRC_WRITE))
OBJ_WRITE := $(addprefix write/, $(addsuffix .o, $(basename $(notdir $(SRC_WRITE)))))

SRC_MISC =					get_next_line.c\
							ft_tabsort.c\

SRC_MISC := $(addprefix misc/, $(SRC_MISC))
OBJ_MISC := $(addprefix misc/, $(addsuffix .o, $(basename $(notdir $(SRC_MISC)))))

SRC_PRINTF =				ft_printf.c\
							args.c\
							buffer.c\
							colors.c\
							fill_conv.c\
							flags.c\
							fun_array.c\
							invalid_conv.c\
							print_ftoa.c\
							print_itoa_base.c\
							t_bis_bis.c\
							t_bis.c\
							b.c\
							c.c\
							d.c\
							f.c\
							o.c\
							p.c\
							s.c\
							t.c\
							u.c\
							x.c\


SRC_PRINTF := $(addprefix ft_printf/, $(SRC_PRINTF))
OBJ_PRINTF := $(addprefix ft_printf/, $(addsuffix .o, $(basename $(notdir $(SRC_PRINTF)))))

SRC_LIBFT += $(addprefix $(SRC_PATH), $(SRC_STRING))
SRC_LIBFT += $(addprefix $(SRC_PATH), $(SRC_MEMORY))
SRC_LIBFT += $(addprefix $(SRC_PATH), $(SRC_LIST))
SRC_LIBFT += $(addprefix $(SRC_PATH), $(SRC_WRITE))
SRC_LIBFT += $(addprefix $(SRC_PATH), $(SRC_MISC))
SRC_LIBFT += $(addprefix $(SRC_PATH), $(SRC_PRINTF))

OBJ_LIBFT := $(addprefix $(OBJ_PATH), $(OBJ_MATH))
OBJ_LIBFT += $(addprefix $(OBJ_PATH), $(OBJ_STRING))
OBJ_LIBFT += $(addprefix $(OBJ_PATH), $(OBJ_MEMORY))
OBJ_LIBFT += $(addprefix $(OBJ_PATH), $(OBJ_LIST))
OBJ_LIBFT += $(addprefix $(OBJ_PATH), $(OBJ_WRITE))
OBJ_LIBFT += $(addprefix $(OBJ_PATH), $(OBJ_MISC))
OBJ_LIBFT += $(addprefix $(OBJ_PATH), $(OBJ_PRINTF))

# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    src.mk                                             :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amamy <amamy@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/09/22 23:46:29 by nivergne          #+#    #+#              #
#    Updated: 2020/07/26 08:59:07 by amamy            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC_PATH		:=	src/
SRC_ASM_PATH	:=	asm/
SRC_VM_PATH		:=	vm/

SRC_ASM =			main.c\
					lexer.c\
					header.c\
					parser.c\
					translator.c\
					error_mode.c\
					helper_lib.c\
					helper_free.c\
					header_tools.c\
					write_header.c\
					helper_error.c\
					label_functions.c\
					parse_parameters.c\
					parse_instruction.c\
					create_output_file.c\
					parse_token_label_call.c\
					parse_label_declarations.c\
					helper_free_token_values.c\
					check_instruction_validity.c\
					check_instruction_validity_2\
					write_instruction_section_1.c\
					write_instruction_section_2.c\
					check_for_additional_errors.c\
					get_tokens_from_current_line.c\
					determine_token_type_and_length.c\
					token_type_determination_function_one.c\
					token_type_determination_function_two.c\
					token_type_determination_function_three.c

SRC_VM =			main.c\
					arena_read_write.c\
					do_cycle.c\
					encoding_byte2.c\
					encoding_byte.c\
					game_loop.c\
					instructions1.c\
					instructions2.c\
					instructions3.c\
					instructions4.c\
					parse_arguments.c\
					parsing2.c\
					parsing.c\
					print3.c\
					print2.c\
					print.c\
					process.c\
					reg_check.c\
					scheduler.c


SRC_ASM := $(addprefix $(SRC_ASM_PATH), $(SRC_ASM))
SRC_ASM := $(addprefix $(SRC_PATH), $(SRC_ASM))

SRC_VM := $(addprefix $(SRC_VM_PATH), $(SRC_VM))
SRC_VM := $(addprefix $(SRC_PATH), $(SRC_VM))
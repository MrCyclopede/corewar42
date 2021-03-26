/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instruction_section_1.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:55:58 by amamy             #+#    #+#             */
/*   Updated: 2020/07/21 21:09:41 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "tokens.h"
#include "libft.h"

static void		write_label_call(t_data *data, t_token *token, int fd)
{
	if (token->type != TOKEN_TYPE_LABEL_CALL)
		return ;
	if (token->values->label_call->type == LABEL_CALL_TYPE_DIRECT)
	{
		if (data->op_tab[token->code_line->op_code].direct_size)
			write_big_endian(fd, token->values->label_call->value, 2);
		else
			write_big_endian(fd, token->values->label_call->value, 4);\
	}
	else if (token->values->label_call->type == LABEL_CALL_TYPE_INDIRECT)
		write_big_endian(fd, token->values->label_call->value, 2);
}

static void		write_opcode(t_data *data, t_token *token, int fd)
{
	char	binary[1];
	int		op_code;

	if (token->type != TOKEN_TYPE_INSTRUCTION)
		return ;
	op_code = (token->values->instruction->type);
	binary[0] = (char)op_code;
	write(fd, binary, 1);
	(void)data;
}

void (*g_instruction_translation_func_array[TRANSLATE_STATES_NUMBER])
(t_data *, t_token *, int) = {
	[TRANSLATE_OPCODE] = write_opcode,
	[TRANSLATE_ENCODING_BYTE] = write_encoding_byte,
	[TRANSLATE_DIRECT] = write_direct,
	[TRANSLATE_INDIRECT] = write_indirect,
	[TRANSLATE_LABEL_CALL] = write_label_call,
	[TRANSLATE_REGISTER] = write_register,
};

static t_token	*skip_label_declaration(t_token *token)
{
	if (token->type == TOKEN_TYPE_LABEL)
		return (token->next);
	else
		return (token);
}

void			write_instruction(t_data *data, t_code_line *code_line, int fd)
{
	int		current_state;
	t_token	*current_token;

	current_state = TRANSLATE_OPCODE;
	current_token = skip_label_declaration(code_line->token);
	while (current_token)
	{
		while (current_state <= TRANSLATE_REGISTER)
		{
			g_instruction_translation_func_array[current_state]
(data, current_token, fd);
			current_state++;
		}
		current_state = TRANSLATE_OPCODE;
		current_token = current_token->next;
	}
}

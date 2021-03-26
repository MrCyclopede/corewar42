/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_instruction_section_2.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:55:58 by amamy             #+#    #+#             */
/*   Updated: 2020/07/21 21:10:05 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "tokens.h"
#include "libft.h"

static char	compute_binary(t_token *token)
{
	int		i;
	int		byte;
	char	binary;

	i = 0;
	byte = 6;
	binary = 0;
	while (i < 3 && token->values->instruction->args[i])
	{
		if (token->values->instruction->args[i]->type == TOKEN_TYPE_DIRECT \
		|| check_label_call_type
(token->values->instruction->args[i], LABEL_CALL_TYPE_DIRECT))
			binary = binary + (char)((DIR_CODE << byte));
		else if (token->values->instruction->args[i]->type
		== TOKEN_TYPE_INDIRECT || check_label_call_type
(token->values->instruction->args[i], LABEL_CALL_TYPE_INDIRECT))
			binary = binary + (char)((IND_CODE << byte));
		else if (token->values->instruction->args[i]->type
		== TOKEN_TYPE_REGISTER)
			binary = binary + (char)((REG_CODE << byte));
		byte = byte - 2;
		i++;
	}
	return (binary);
}

void		write_encoding_byte(t_data *data, t_token *token, int fd)
{
	char	binary[1];

	binary[0] = 0;
	if (token->type != TOKEN_TYPE_INSTRUCTION \
	|| !data->op_tab[token->values->instruction->type].encoding_byte)
		return ;
	else
	{
		binary[0] = compute_binary(token);
	}
	write(fd, binary, 1);
}

void		write_direct(t_data *data, t_token *token, int fd)
{
	if (token->type != TOKEN_TYPE_DIRECT)
		return ;
	if (data->op_tab[token->code_line->op_code].direct_size)
		write_big_endian(fd, token->values->direct->value, 2);
	else
		write_big_endian(fd, token->values->direct->value, 4);
}

void		write_indirect(t_data *data, t_token *token, int fd)
{
	if (token->type != TOKEN_TYPE_INDIRECT)
		return ;
	write_big_endian(fd, token->values->indirect->value, 2);
	(void)data;
}

void		write_register(t_data *data, t_token *token, int fd)
{
	if (token->type != TOKEN_TYPE_REGISTER)
		return ;
	write(fd, &token->values->registr->reg_nb, 1);
	(void)data;
}

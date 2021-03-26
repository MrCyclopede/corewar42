/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 02:56:10 by amamy             #+#    #+#             */
/*   Updated: 2020/08/04 20:37:50 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "tokens.h"
#include "ft_printf.h"

static void			labels_calls_computing(t_data *data, int current_byte)
{
	t_label_call	*current;
	int				line_mem_address;

	current = data->label_calls;
	if (!current)
		return ;
	while (current)
	{
		if (!(current->target->mem_address) && current->target->next == NULL)
		{
			current->target->mem_address = current_byte;
		}
		line_mem_address = current->token->code_line->mem_address;
		if (current->target)
			current->value = current->target->mem_address - line_mem_address;
		else
			current->value = 0;
		current = current->next;
	}
}

/*
** ==================== update_instruction_size_and_address ====================
** Used in parse_line() to keep memory count : to assign the adress of the
** instruction and the size of this instruction.
*/

static void			update_instruction_size
	(t_data *data, t_code_line *code_line)
{
	if (data->op_tab[code_line->op_code].encoding_byte)
		code_line->instruction_size = (code_line->instruction_size + 2);
	else
		code_line->instruction_size++;
}

/*
** ==================== parse_line ====================
** This functions parses a line containing an instruction.
** For this, it will verify that the syntax is valid, keep the count
** of the codes size and check for additional error if error.
*/

static int			parse_line(t_data *data, t_code_line *code_line,
int inst_position, int current_byte[1])
{
	if (!check_instruction_validity(data, code_line, inst_position))
		return (0);
	update_instruction_size(data, code_line);
	if (!code_line->errors)
	{
		if (!parse_instruction(data, code_line, inst_position))
			return (0);
	}
	check_for_additional_errors(data, code_line);
	*current_byte = *current_byte + code_line->instruction_size;
	if (code_line->errors)
		data->errors = 1;
	return (1);
}

/*
** ==================== skip_label_only_lines ====================
** Used in parser to skip lines containing only label declaration
** in it as we only parse instructions.
*/

static t_code_line	*skip_label_only_lines(t_code_line *code_line)
{
	while (code_line && is_only_label(code_line))
		code_line = code_line->next;
	return (code_line);
}

/*
** ==================== parser ====================
** The role of the parser is to retrieve the informations
** related to the lexemes detected by lexer previously
** To achieve this we send lines with instruction in parse_line()
*/

int					parser(t_data **data, t_code_line **code_line)
{
	int			current_byte;
	int			inst_tok_pos;
	t_code_line	*cur_line;

	current_byte = 0;
	inst_tok_pos = 0;
	cur_line = (*code_line);
	if (cur_line == NULL)
		return (error_msg("Empty instruction section", 0));
	if (!(parse_label_declarations(*data, *code_line)))
		return (0);
	while (((cur_line = skip_label_only_lines(cur_line))))
	{
		inst_tok_pos = (cur_line->token->type == TOKEN_TYPE_LABEL) ? (1) : (0);
		cur_line->mem_address = current_byte;
		if (!(parse_line(*data, cur_line, inst_tok_pos, &current_byte)))
			return (0);
		if (cur_line)
			cur_line = cur_line->next;
	}
	labels_calls_computing(*data, current_byte);
	(*data)->instruction_section_size = current_byte;
	return (1);
}

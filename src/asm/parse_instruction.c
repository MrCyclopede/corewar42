/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_instruction.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:18:15 by amamy             #+#    #+#             */
/*   Updated: 2020/08/04 19:34:13 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "tokens.h"
#include "ft_printf.h"

static int	allocation_instruction
	(t_code_line *code_line, t_instruction **inst, t_token **inst_token)
{
	if (!((*inst) = ft_memalloc(sizeof(t_instruction))))
		return (error_code_line(code_line, MEMORY_ALLOCATION_ERROR, 0));
	if (!((*inst_token)->values = ft_memalloc(sizeof(t_type))))
		return (error_code_line(code_line, MEMORY_ALLOCATION_ERROR, 0));
	(*inst_token)->values->instruction = (*inst);
	if (!((*inst_token)->values->instruction->lexeme = ft_strndup
(&code_line->line[(*inst_token)->position], (*inst_token)->length)))
		return (error_code_line(code_line, MEMORY_ALLOCATION_ERROR, 0));
	(*inst_token)->values->instruction->type = code_line->op_code;
	return (1);
}

/*
** ==================== is_param_parsed_or_error ====================
** If an error has been raised or if the current is parsed, this function
** will inidicate it.
*/

static int	is_param_parsed_or_error(t_token *token, int current_param)
{
	if (token->code_line->errors || token->error)
	{
		if (token->code_line->errors != MEMORY_ALLOCATION_ERROR)
			token->code_line->errors = LINE_ERROR_SYNTAX;
		return (1);
	}
	if (token->values->instruction->args[current_param] == NULL)
		return (0);
	return (1);
}

static t_token	*(*g_parse_parameters_func_array[PARSE_TOKEN_STATES_NUMBER])
	(t_data *, t_code_line *, t_token *) = {
	[PARSE_TOKEN_REGISTER] = parse_token_register,
	[PARSE_TOKEN_INDIRECT] = parse_token_indirect,
	[PARSE_TOKEN_DIRECT] = parse_token_direct,
	[PARSE_TOKEN_LABEL_CALL] = parse_token_label_call,
};

/*
** ==================== parse_instruction ====================
** Receives a t_code_line (a line of code) and organizes the
** memory allocation and the parsing of parameter.
*/

int			parse_instruction
	(t_data *data, t_code_line *code_line, int inst_position)
{
	t_instruction	*inst;
	t_token			*inst_token;
	int				current_param;
	int				token_parse_state;

	inst = NULL;
	current_param = 0;
	inst_token = code_line->tokens[inst_position];
	if (!(allocation_instruction(code_line, &inst, &inst_token)))
		return (error_msg(ERR_MEMORY_ALLOCATION, 0));
	while (current_param < data->op_tab[code_line->op_code].param_nb \
	&& !(code_line->errors == MEMORY_ALLOCATION_ERROR))
	{
		token_parse_state = PARSE_TOKEN_REGISTER;
		while (!is_param_parsed_or_error(inst_token, current_param) \
		&& token_parse_state < PARSE_TOKEN_STATES_NUMBER)
		{
			inst_token->values->instruction->args[current_param] =
			g_parse_parameters_func_array[token_parse_state](data, code_line,
			code_line->tokens[inst_position + (1 + current_param * 2)]);
			token_parse_state++;
		}
		current_param++;
	}
	return ((code_line->errors == MEMORY_ALLOCATION_ERROR) ? (0) : (1));
}

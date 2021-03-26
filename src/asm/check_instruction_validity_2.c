/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction_validity_2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/26 08:57:53 by amamy             #+#    #+#             */
/*   Updated: 2020/07/26 09:06:34 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "tokens.h"

static int	set_error_and_ret(t_code_line *line,
int inst_index)
{
	error_syntax_token(line->tokens[inst_index], BAD_OP_CODE, 1);
	return (error_code_line(line, LINE_ERROR_SYNTAX, 1));
}

static int	is_valid_param_nb(t_data *data, t_token *lst_token)
{
	int		count;
	t_token	*current_token;

	count = 0;
	current_token = lst_token;
	while (current_token && count < 5)
	{
		if (current_token->type >= TOKEN_TYPE_DIRECT \
		&& current_token->type <= TOKEN_TYPE_LABEL_CALL)
			count++;
		current_token = current_token->next;
	}
	if (data->op_tab[lst_token->code_line->op_code].param_nb != count)
		return (0);
	return (1);
}

int			pre_check(t_data *data, t_code_line *line, int inst_index)
{
	if (line->errors)
		return (1);
	if (line->tokens[inst_index]->type != TOKEN_TYPE_INSTRUCTION)
		return (set_error_and_ret(line, inst_index));
	if (!is_valid_param_nb(data, line->token))
		return (error_syntax_token(line->tokens[inst_index],
		WRONG_PARAMETER_NUMBER, 1));
		return (0);
}

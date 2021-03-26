/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_for_additional_errors.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 15:02:04 by amamy             #+#    #+#             */
/*   Updated: 2020/07/07 00:45:28 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "tokens.h"

static void	check_if_crap_after_op(t_data *data, t_code_line *code_line)
{
	int		i;
	int		size;
	t_token	*token;

	i = 0;
	token = code_line->token;
	size = 1 + data->op_tab[code_line->op_code].param_nb;
	if (token->type == TOKEN_TYPE_LABEL)
		size++;
	while (i < size)
	{
		if (token->type == TOKEN_TYPE_SEPARATOR)
			token = token->next;
		i++;
		token = token->next;
	}
	if (token)
	{
		error_syntax_token(token, TOKEN_AFTER_OP, 1);
		error_code_line(code_line, LINE_ERROR_SYNTAX, 1);
	}
}

void		check_for_additional_errors(t_data *data, t_code_line *code_line)
{
	if (!code_line->errors)
		check_if_crap_after_op(data, code_line);
}

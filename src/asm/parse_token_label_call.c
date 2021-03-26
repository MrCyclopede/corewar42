/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token_label_call.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:20:38 by amamy             #+#    #+#             */
/*   Updated: 2020/08/04 19:34:36 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"
#include "tokens.h"
#include "ft_printf.h"

static void	add_label_call_to_queue(t_data *data, t_label_call *current)
{
	t_label_call *tmp;

	if (!data->label_calls)
		data->label_calls = current;
	else
	{
		tmp = data->label_calls;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = current;
	}
}

/*
** ==================== set_label_call_target ====================
** Handles the assignment of values part and the allocation.
*/

static void	set_label_call_target(t_data *data, t_token *label_call)
{
	t_label *declarations;

	declarations = data->label_list;
	while (declarations)
	{
		if (!ft_strcmp
(declarations->lexeme, label_call->values->label_call->lexeme))
		{
			label_call->values->label_call->target = declarations->target;
			label_call->values->label_call->token = label_call;
			add_label_call_to_queue(data, label_call->values->label_call);
		}
		declarations = declarations->next;
	}
	if (!label_call->values->label_call->target)
	{
		label_call->error = UNDECLARED_LABEL_CALL;
		label_call->code_line->errors = LINE_ERROR_SYNTAX;
	}
}

static char	*set_lexeme(t_token *param)
{
	char	*lexeme;

	if (check_label_call_type(param, LABEL_CALL_TYPE_INDIRECT))
	{
		if (!(lexeme = ft_strndup
(&param->code_line->line[param->position + 1], param->length - 1)))
			return (NULL);
	}
	else
	{
		if (!(lexeme = ft_strndup
(&param->code_line->line[param->position + 2], param->length - 2)))
			return (NULL);
	}
	return (lexeme);
}

/*
** ==================== parse_token_label_call ====================
** If the type of the lexeme Received is LABEL_CALL, give its values.
*/

t_token		*parse_token_label_call
	(t_data *data, t_code_line *codeline, t_token *param)
{
	t_label_call *label_call;

	if (param->type == TOKEN_TYPE_LABEL_CALL)
	{
		label_call = param->values->label_call;
		if (!(label_call->lexeme = set_lexeme(param)))
		{
			ft_putendl(ERR_MEMORY_ALLOCATION);
			codeline->errors = MEMORY_ALLOCATION_ERROR;
			return (NULL);
		}
		if (check_label_call_type(param, LABEL_CALL_TYPE_INDIRECT) \
		|| data->op_tab[codeline->op_code].direct_size)
			codeline->instruction_size = codeline->instruction_size + 2;
		else
			codeline->instruction_size = codeline->instruction_size + 4;
		set_label_call_target(data, param);
		return (param);
	}
	return (NULL);
}

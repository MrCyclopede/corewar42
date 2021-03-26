/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_determination_function_three.c          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/08 04:21:46 by amamy             #+#    #+#             */
/*   Updated: 2020/08/04 19:35:02 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "tokens.h"
#include "libft.h"
#include "ft_printf.h"

int			is_separator(t_token *token)
{
	if (token->code_line->line[token->position] == ',')
	{
		token->length = 1;
		token->type = TOKEN_TYPE_SEPARATOR;
		return (1);
	}
	return (99);
}

static int	is_valid_label_call
	(t_token *token, int index, char *str)
{
	if (!is_label_char(str[index]))
		return (0);
	while (str[index] && is_label_char(str[index]))
		index++;
	token->length = index - token->position;
	return (1);
}

static int	is_direct_label_call(t_token *token)
{
	int		index;
	char	*str;

	index = token->position;
	str = token->code_line->line;
	if (str[index] && str[index + 1] \
		&& str[index] == '%' && str[index + 1] == ':')
	{
		index += 2;
		if (is_valid_label_call(token, index, str))
			return (1);
	}
	return (0);
}

static int	is_indirect_label_call(t_token *token)
{
	int		index;
	char	*str;

	index = token->position;
	str = token->code_line->line;
	if (str[index] && str[index] == ':')
	{
		index++;
		if (is_valid_label_call(token, index, str))
			return (1);
	}
	return (0);
}

int			is_label_call(t_token *token)
{
	t_label_call	*label;

	if (is_direct_label_call(token))
	{
		if (!(token->values = ft_memalloc(sizeof(t_type*))))
			return (0);
		if (!(label = ft_memalloc(sizeof(t_label_call))))
			return (0);
		token->type = TOKEN_TYPE_LABEL_CALL;
		token->values->label_call = label;
		token->values->label_call->type = LABEL_CALL_TYPE_DIRECT;
	}
	else if (is_indirect_label_call(token))
	{
		if (!(token->values = ft_memalloc(sizeof(t_type*))))
			return (0);
		if (!(label = ft_memalloc(sizeof(t_label_call))))
			return (0);
		token->type = TOKEN_TYPE_LABEL_CALL;
		token->values->label_call = label;
		token->values->label_call->type = LABEL_CALL_TYPE_INDIRECT;
	}
	return (1);
}

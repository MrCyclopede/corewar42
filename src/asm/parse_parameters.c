/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_parameters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 18:21:24 by amamy             #+#    #+#             */
/*   Updated: 2020/08/04 20:41:04 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "asm.h"
#include "tokens.h"
#include "ft_printf.h"

/*
** ==================== parse_token_register ====================
** If the type of the lexeme Received is INDIRECT, give it values
*/

t_token	*parse_token_register
	(t_data *data, t_code_line *codeline, t_token *param)
{
	t_registr *registr;

	if (param->type == TOKEN_TYPE_REGISTER)
	{
		if (!(registr = ft_memalloc(sizeof(t_registr))) \
		|| !(param->values = ft_memalloc(sizeof(t_type*))))
		{
			codeline->errors = MEMORY_ALLOCATION_ERROR;
			ft_putendl(ERR_MEMORY_ALLOCATION);
			return (NULL);
		}
		registr->reg_nb = ft_atoi(&codeline->line[param->position + 1]);
		if (registr->reg_nb < 1 || registr->reg_nb > 16)
			error_syntax_token(param, INVALID_REGISTER, 1);
		codeline->instruction_size = codeline->instruction_size + 1;
		param->values->registr = registr;
		return (param);
	}
	return (NULL);
	(void)data;
}

/*
** ==================== parse_token_indirect ====================
** If the type of the lexeme Received is INDIRECT, give it values
*/

t_token	*parse_token_indirect
	(t_data *data, t_code_line *codeline, t_token *param)
{
	t_indirect *indirect;

	if (param->type == TOKEN_TYPE_INDIRECT)
	{
		if (!(indirect = ft_memalloc(sizeof(t_indirect))) \
		|| !(param->values = ft_memalloc(sizeof(t_type*))))
		{
			ft_putendl(ERR_MEMORY_ALLOCATION);
			codeline->errors = MEMORY_ALLOCATION_ERROR;
			return (NULL);
		}
		indirect->value = ft_atoi(&codeline->line[param->position]);
		codeline->instruction_size = codeline->instruction_size + 2;
		param->values->indirect = indirect;
		return (param);
	}
	return (NULL);
	(void)data;
}

/*
** ==================== parse_token_direct ====================
** If the type of the lexeme Received is DIRECT, give it values
*/

t_token	*parse_token_direct(t_data *data, t_code_line *codeline, t_token *param)
{
	t_direct *direct;

	if (param->type == TOKEN_TYPE_DIRECT)
	{
		if (!(direct = ft_memalloc(sizeof(t_direct))) \
		|| !(param->values = ft_memalloc(sizeof(t_type*))))
		{
			ft_putendl(ERR_MEMORY_ALLOCATION);
			codeline->errors = MEMORY_ALLOCATION_ERROR;
			return (NULL);
		}
		direct->value = ft_atoi(&codeline->line[param->position + 1]);
		if (data->op_tab[codeline->op_code].direct_size)
			codeline->instruction_size = codeline->instruction_size + 2;
		else
			codeline->instruction_size = codeline->instruction_size + 4;
		param->values->direct = direct;
		return (param);
	}
	return (NULL);
}

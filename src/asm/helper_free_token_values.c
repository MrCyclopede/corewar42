/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_free_token_values.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/21 09:09:43 by amamy             #+#    #+#             */
/*   Updated: 2020/08/04 19:24:07 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "tokens.h"
#include "libft.h"

static void	free_label(t_token *token)
{
	if (token->values)
		ft_memdel((void*)&token->values->label->lexeme);
	ft_memdel((void*)&token->values->label);
}

static void	free_instruction(t_token *token)
{
	if (token->values)
		ft_memdel((void*)&token->values->instruction->lexeme);
	ft_memdel((void*)&token->values->instruction);
}

static void	free_unknown(t_token *token)
{
	if (token->values)
		ft_memdel((void*)&token->values->unknown->lexeme);
	ft_memdel((void*)&token->values->unknown);
}

static void	free_parameter(t_token *param)
{
	if (param->type == TOKEN_TYPE_DIRECT)
		ft_memdel((void*)&param->values->direct);
	if (param->type == TOKEN_TYPE_INDIRECT)
		ft_memdel((void*)&param->values->indirect);
	if (param->type == TOKEN_TYPE_REGISTER)
		ft_memdel((void*)&param->values->registr);
	if (param->type == TOKEN_TYPE_LABEL_CALL && param->values)
		ft_memdel((void*)&param->values->label_call->lexeme);
	ft_memdel((void*)&param->values->label_call);
}

void		free_token(t_token *token)
{
	int	type;

	type = token->type;
	if (!(type == TOKEN_TYPE_SEPARATOR))
	{
		if (type == TOKEN_TYPE_LABEL)
			free_label(token);
		else if (type == TOKEN_TYPE_INSTRUCTION)
			free_instruction(token);
		else if (type == TOKEN_TYPE_UNKNOWN)
			free_unknown(token);
		else if (type >= TOKEN_TYPE_DIRECT && type <= TOKEN_TYPE_LABEL_CALL)
			free_parameter(token);
	}
	ft_memdel((void*)&token->token_name);
	ft_memdel((void*)&token->values);
	ft_memdel((void*)&token);
}

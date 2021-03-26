/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_determination_function_one.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 05:57:28 by amamy             #+#    #+#             */
/*   Updated: 2020/07/30 21:42:39 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "libft.h"
#include "ft_printf.h"

int	is_label_char(char c)
{
	int	i;
	int	label_char_nb;

	i = 0;
	label_char_nb = 37;
	while (i < label_char_nb)
	{
		if (c == LABEL_CHARS[i])
			return (1);
		i++;
	}
	return (0);
}

int	is_label(t_token *token)
{
	int		i;
	char	*str;

	i = token->position;
	str = token->code_line->line;
	if (!is_label_char(str[i]))
		return (1);
	while (is_label_char(str[i]))
		i++;
	if (str[i] != ':')
		return (1);
	token->length = (i + 1) - token->position;
	token->type = TOKEN_TYPE_LABEL;
	return (1);
}

int	is_direct(t_token *token)
{
	int		i;
	char	*str;

	i = token->position;
	str = token->code_line->line;
	if (str[i] && str[i] == '%' && i++)
	{
		if ((ft_isdigit(str[i]) || str[i] == '+' || str[i] == '-') && i++)
		{
			while (str[i] && ft_isdigit(str[i]))
				i++;
			token->length = i - token->position;
			token->type = TOKEN_TYPE_DIRECT;
		}
	}
	return (1);
}

int	is_indirect(t_token *token)
{
	int		i;
	char	*str;

	i = token->position;
	str = token->code_line->line;
	if (str[i] && (str[i] == '-' || str[i] == '+'))
		i++;
	if (ft_isdigit(str[i]) && i++)
	{
		while (str[i] && ft_isdigit(str[i]))
			i++;
		token->length = i - token->position;
		token->type = TOKEN_TYPE_INDIRECT;
	}
	return (1);
}

int	is_register(t_token *token)
{
	int		i;
	char	*str;

	i = token->position;
	str = token->code_line->line;
	if (str[i] == 'r' && i++)
	{
		while (str[i] && ft_isdigit(str[i]))
			i++;
		token->length = i - token->position;
		token->type = TOKEN_TYPE_REGISTER;
	}
	return (1);
}

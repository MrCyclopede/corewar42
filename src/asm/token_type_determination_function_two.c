/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_type_determination_function_two.c            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/26 05:57:28 by amamy             #+#    #+#             */
/*   Updated: 2020/08/04 19:35:10 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "tokens.h"
#include "libft.h"
#include "ft_printf.h"

static int (*g_token_type_determination_func_array[NB_TOKEN_TYPE])
	(t_token *) = {
	[TOKEN_TYPE_SEPARATOR] = is_separator,
	[TOKEN_TYPE_LABEL] = is_label,
	[TOKEN_TYPE_INSTRUCTION] = is_instructions,
	[TOKEN_TYPE_DIRECT] = is_direct,
	[TOKEN_TYPE_REGISTER] = is_register,
	[TOKEN_TYPE_INDIRECT] = is_indirect,
	[TOKEN_TYPE_LABEL_CALL] = is_label_call,
	[TOKEN_TYPE_UNKNOWN] = is_unknown,
};

int						is_instructions(t_token *token)
{
	int		i;
	int		length;
	char	*str;

	length = 0;
	i = token->position;
	str = token->code_line->line;
	if (!ft_strncmp(&str[i], "lfork", 5))
		length = 5;
	else if (!ft_strncmp(&str[i], "live", 4) \
		|| !ft_strncmp(&str[i], "zjmp", 4) \
		|| (!ft_strncmp(&str[i], "fork", 4)) || !ft_strncmp(&str[i], "lldi", 4))
		length = 4;
	else if (!ft_strncmp(&str[i], "lld", 3) || !ft_strncmp(&str[i], "add", 3) \
		|| !ft_strncmp(&str[i], "sub", 3) || !ft_strncmp(&str[i], "aff", 3) \
		|| !ft_strncmp(&str[i], "xor", 3) || !ft_strncmp(&str[i], "sti", 3) \
		|| !ft_strncmp(&str[i], "ldi", 3) || !ft_strncmp(&str[i], "and", 3))
		length = 3;
	else if (!ft_strncmp(&str[i], "ld", 2) || !ft_strncmp(&str[i], "or", 2) \
		|| (!ft_strncmp(&str[i], "st", 2)))
		length = 2;
	if (length != 0 && (token->length = length))
		token->type = TOKEN_TYPE_INSTRUCTION;
	return (1);
}

static int				detect_unknown_length(t_token *token)
{
	t_token_type	current_token_type;

	token->type = TOKEN_TYPE_UNDEFINED;
	current_token_type = TOKEN_TYPE_SEPARATOR;
	while (current_token_type < TOKEN_TYPE_UNKNOWN \
		&& token->type == TOKEN_TYPE_UNDEFINED)
	{
		if (!(g_token_type_determination_func_array[current_token_type](token)))
			return (0);
		current_token_type++;
	}
	return (1);
}

static void				tag_unknown(t_token *token, int length)
{
	token->error = UNKNOWN_TOKEN;
	token->type = TOKEN_TYPE_UNKNOWN;
	token->length = length;
	token->code_line->errors = LINE_ERROR_LEXICAL;
}

int						is_unknown(t_token *token)
{
	int			i;
	int			length;
	char		*str;
	t_token		*tmp;

	if (!(tmp = ft_memalloc(sizeof(t_token))))
		return (0);
	length = 0;
	i = token->position;
	str = token->code_line->line;
	tmp->code_line = token->code_line;
	while (tmp->type == TOKEN_TYPE_UNDEFINED \
		&& (str[i] && (!is_comment_char(str[i]) && !is_whitespace(str[i++]))))
	{
		tmp->position = i;
		if (!(detect_unknown_length(tmp)))
		{
			free_token(tmp);
			return (0);
		}
		length++;
	}
	tag_unknown(token, length);
	free_token(tmp);
	return (1);
}

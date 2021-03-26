/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 23:58:28 by amamy             #+#    #+#             */
/*   Updated: 2020/07/07 00:55:14 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "tokens.h"
#include "ft_printf.h"

/*
** ==================== check_label_call_type ====================
** As Label_call are the only token to have a subtype, this function allows
** to check this tyoe easily.
*/

int		check_label_call_type(t_token *label_call, int is_this_type)
{
	if (label_call->type == TOKEN_TYPE_LABEL_CALL)
		if (label_call && label_call->values && label_call->values->label_call)
		{
			if (label_call->values->label_call->type == is_this_type)
				return (1);
		}
	return (0);
}

/*
** ==================== is_label_declaration ====================
** Check if the t_code_line received is has a label token as first token
** and that there is nothing else n the line.
*/

int		is_only_label(t_code_line *code_line)
{
	if (!code_line)
		return (0);
	if (code_line->token && code_line->token->type == TOKEN_TYPE_LABEL \
	&& code_line->nb_token == 1)
		return (1);
	return (0);
}

/*
** ==================== is_label_declaration ====================
** Check if the t_code_line received is has a label token as first token.
*/

int		is_label_declaration(t_code_line *code_line)
{
	if (code_line->token->type == TOKEN_TYPE_LABEL)
		return (1);
	return (0);
}

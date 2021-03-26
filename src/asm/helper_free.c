/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   helper_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 05:36:34 by nicolasv          #+#    #+#             */
/*   Updated: 2020/07/30 20:36:56 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "tokens.h"
#include "libft.h"

int		return_msg_free(char *msg, int code, void **ap)
{
	ft_memdel(ap);
	return (error_msg(msg, code));
}

int		free_data(t_data **data)
{
	if (*data)
		ft_strdel(&(*data)->file_name);
	free((*data));
	return (1);
}

int		free_token_list(t_token *token)
{
	t_token *current_token_address;

	while (token)
	{
		current_token_address = (token);
		(token) = (token)->next;
		if (current_token_address != NULL)
			free_token(current_token_address);
	}
	return (1);
}

int		free_code_line(t_code_line **code_line)
{
	t_code_line *current_code_line_address;

	while (*code_line)
	{
		current_code_line_address = (*code_line);
		(*code_line) = (*code_line)->next;
		free_token_list(current_code_line_address->token);
		ft_strdel(&current_code_line_address->line);
		ft_memdel((void*)&current_code_line_address->tokens);
		ft_memdel((void*)&current_code_line_address);
	}
	free(*code_line);
	return (1);
}

int		free_all(t_data **data, t_code_line **code_line)
{
	if (code_line)
		free_code_line(code_line);
	if (data)
		free_data(data);
	return (1);
}

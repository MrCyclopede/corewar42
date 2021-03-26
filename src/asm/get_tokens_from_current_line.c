/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_from_current_line.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 04:42:59 by nivergne          #+#    #+#             */
/*   Updated: 2020/08/04 20:47:41 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"

/*
** ==================== create_tokens ====================
** Allocates memory for new token, git it its position,
** token_nb and the line it is contained by.
** Send it to tokens identification and return it.
*/

static t_token	*create_token
	(t_code_line **current_line, int position, int token_nb)
{
	t_token		*new;

	if (!(new = (t_token *)ft_memalloc(sizeof(t_token))))
	{
		ft_putendl(ERR_MEMORY_ALLOCATION);
		return (0);
	}
	new->position = position;
	new->token_nb = token_nb;
	new->code_line = (*current_line);
	if (!(determine_token_type_and_length(new)))
	{
		ft_putendl(ERR_MEMORY_ALLOCATION);
		return (0);
	}
	if (!(new->token_name = ft_strndup
(&((*current_line)->line)[position], new->length)))
	{
		ft_putendl(ERR_MEMORY_ALLOCATION);
		return (0);
	}
	new->next = NULL;
	return (new);
}

/*
** ==================== chain_token ====================
** Receives 2 t_token, setting the token->next address of the
** first one to point on the second.
** In case of first token, set the pointer himself.
*/

static void		chain_token(t_token **current_token, t_token *new)
{
	if ((*current_token))
	{
		(*current_token)->next = new;
		(*current_token) = new;
	}
	else
		(*current_token) = new;
}

/*
** ==================== build_token_array ====================
** This function build an array which will store pointer toward
** tokens of the line, in order.
*/

static int		build_token_array(t_code_line *code_line)
{
	int		i;
	t_token	*current_token;

	i = 0;
	current_token = code_line->token;
	if (!(code_line->tokens =
ft_memalloc(sizeof(t_token*) * code_line->nb_token)))
		return (0);
	while (current_token)
	{
		code_line->tokens[i] = current_token;
		current_token = current_token->next;
		i++;
	}
	return (1);
}

/*
** ==================== get_tokens_from_current_line ====================
** Goes through line token by token to identify them.
*/

int				get_tokens_from_current_line
	(t_code_line **current_c_line, char *line)
{
	int			i;
	int			token_nb;
	t_token		*new_token;
	t_token		*current_token;

	i = 0;
	token_nb = 0;
	current_token = NULL;
	while (line[i] && !is_str_whitespace_or_comment(&line[i]))
	{
		while (line[i] && is_whitespace(line[i]))
			i++;
		if (!(new_token = create_token(current_c_line, i, token_nb++)))
			return (error_msg("error in tokeniser", 0));
		chain_token(&current_token, new_token);
		if (!(*current_c_line)->token)
			(*current_c_line)->token = new_token;
		(new_token->length > 0) ? (i += new_token->length) : (i++);
	}
	(*current_c_line)->nb_token = token_nb;
	if (!(build_token_array(*current_c_line)))
		error_msg(ERR_MEMORY_ALLOCATION, 0);
	return (1);
}

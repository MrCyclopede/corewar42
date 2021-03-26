/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_label_declarations.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 11:44:02 by amamy             #+#    #+#             */
/*   Updated: 2020/08/04 20:46:28 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "tokens.h"
#include "ft_printf.h"

static char			*get_label_text(t_code_line *code_line)
{
	char *label;

	if (!(label = ft_strndup
(&code_line->line[code_line->token->position],
	code_line->token->length - 1)))
	{
		ft_putendl(ERR_MEMORY_ALLOCATION);
		return (NULL);
	}
	return (label);
}

/*
** ==================== fetch_label_target ====================
** Fetch the next line containing an instruction.
*/

static t_code_line	*fetch_label_target(t_code_line *code_line)
{
	t_code_line *tmp;

	tmp = code_line;
	if (is_only_label(code_line))
	{
		if (code_line->next && code_line->next->nb_token > 1)
			return (code_line->next);
		while (is_only_label(tmp) && tmp->next)
			tmp = tmp->next;
		return (tmp);
	}
	else
		return (code_line);
}

/*
** ==================== create_and_add_label ====================
** Initiate label declaration :
** memory allocation + lexeme assignment + target line.
*/

static int			create_and_add_label
	(t_data *data, t_code_line *code_line, char *label)
{
	t_label *new_label;
	t_label *current_label;

	if (!(new_label = ft_memalloc(sizeof(t_label))))
		return (error_msg(ERR_MEMORY_ALLOCATION, 0));
	if (!(code_line->token->values = ft_memalloc(sizeof(t_type))))
		return (error_msg(ERR_MEMORY_ALLOCATION, 0));
	new_label->lexeme = label;
	new_label->target = fetch_label_target(code_line);
	code_line->token->values->label = new_label;
	if (!data->label_list)
		data->label_list = new_label;
	else
	{
		current_label = data->label_list;
		while (current_label->next)
			current_label = current_label->next;
		current_label->next = new_label;
	}
	return (1);
}

/*
** ==================== check_redefinition ====================
** Used to check if the label declaration passed in argument does
** not have the same lexeme as one used before.
*/

static int			check_redefinition
	(t_code_line *line, t_label *label_list, char *label)
{
	while (label_list)
	{
		if (!ft_strcmp(label_list->lexeme, label))
			return (error_syntax_token(line->token, LABEL_REDEFINITION, 1));
		label_list = label_list->next;
	}
	return (1);
}

/*
** ==================== parse_label_declarations ====================
** Goes through all the lines get the label declarations to initiate and
** list them.
** Initiate means memory allocation + lexeme assignment + target line.
*/

int					parse_label_declarations
	(t_data *data, t_code_line *code_line)
{
	char		*label_text;
	t_code_line	*current_line;

	current_line = code_line;
	while (current_line)
	{
		if (is_label_declaration(current_line))
		{
			if (!(label_text = get_label_text(current_line)))
				return (0);
			check_redefinition(current_line, data->label_list, label_text);
			if (!current_line->errors)
			{
				if (!(create_and_add_label(data, current_line, label_text)))
				{
					current_line->errors = MEMORY_ALLOCATION_ERROR;
					return (0);
				}
			}
			else
				ft_strdel(&label_text);
		}
		current_line = current_line->next;
	}
	return (1);
}

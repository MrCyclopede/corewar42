/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_instruction_validity.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/01 18:48:46 by amamy             #+#    #+#             */
/*   Updated: 2020/08/04 19:30:45 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "tokens.h"

static int	get_op_code(t_data *data, t_token *op)
{
	int		i;
	char	*line;

	i = 1;
	line = op->code_line->line;
	while (ft_strncmp(data->op_tab[i].name, &line[op->position], op->length) \
	&& i < 16)
		i++;
	if (i > 16)
		return (error_syntax_token(op, BAD_OP_CODE, 1));
	return (i);
}

static int	chk_param_validity(t_data *data, t_token *prm, int param_nb)
{
	int		param_allowed;
	char	*tmp;

	if (!(tmp = (ft_itoa(data->op_tab[prm->code_line->op_code].param_types))))
		return (error_code_line(prm->code_line, MEMORY_ALLOCATION_ERROR, 0));
	param_allowed = (int)tmp[param_nb] - '0';
	if (prm->type == TOKEN_TYPE_REGISTER)
		if (param_allowed != 1 && param_allowed != 3 && param_allowed != 5 \
		&& param_allowed != 7)
			error_syntax_token(prm, WRONG_ARGUMENT_TYPE, 0);
	if (prm->type == TOKEN_TYPE_INDIRECT \
	|| check_label_call_type(prm, LABEL_CALL_TYPE_INDIRECT))
		if (param_allowed != 2 && param_allowed != 3 && param_allowed != 6 \
		&& param_allowed != 7)
			error_syntax_token(prm, WRONG_ARGUMENT_TYPE, 0);
	if (prm->type == TOKEN_TYPE_DIRECT \
	|| check_label_call_type(prm, LABEL_CALL_TYPE_DIRECT))
		if (param_allowed < 4)
			error_syntax_token(prm, WRONG_ARGUMENT_TYPE, 0);
	if (prm->type != TOKEN_TYPE_REGISTER && prm->type != TOKEN_TYPE_INDIRECT \
	&& prm->type != TOKEN_TYPE_DIRECT && prm->type != TOKEN_TYPE_LABEL_CALL \
	&& prm->type != TOKEN_TYPE_UNKNOWN)
		error_syntax_token(prm, NOT_ARGUMENT_TYPE, 0);
	ft_strdel(&tmp);
	return (1);
}

/*
** ==================== check_instruction_validity ====================
** Save the op code of the instruction in the code_line and check
** taht we have an op code and that the params sent to it are
** compatible with this instruction.
*/

int			check_instruction_validity(t_data *data, t_code_line *line,
int inst_position)
{
	int	i;
	int	params;
	int	inst_index;

	i = 1;
	params = 0;
	inst_index = inst_position;
	line->op_code = get_op_code(data, line->tokens[inst_index]);
	if (pre_check(data, line, inst_index))
		return (1);
	while (params < data->op_tab[line->op_code].param_nb)
	{
		if (!(chk_param_validity(data, line->tokens[inst_index + i], params)))
			return (error_msg(ERR_MEMORY_ALLOCATION, 0));
		if (++params < data->op_tab[line->op_code].param_nb \
		&& (line->tokens[inst_index + i + 1] \
		&& (is_separator(line->tokens[inst_index + i + 1]) == 99)))
		{
			return (error_syntax_token
(line->tokens[inst_index + i + 1], MISSING_SEPARATOR, 1));
		}
		i = i + 2;
	}
	return (1);
}

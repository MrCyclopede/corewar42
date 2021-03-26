/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_arguments.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 04:12:51 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 04:34:31 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	prepare_arguments(t_process *process, t_props *props)
{
	int i;

	i = 0;
	ft_memcpy(process->event.og_args, process->event.args, sizeof(int) * 3);
	while (i < props->nb_args)
	{
		if (get_encoding_type(process->event.encoding_byte, i) == T_REG)
		{
			process->event.args[i] = process->reg[process->event.args[i]];
		}
		i++;
	}
}

void	handle_encoding(t_vm *vm, t_process *process, t_props *props, int *size)
{
	(void)vm;
	if (!props->has_encoding_byte)
		sanitize_encoding_byte(&process->event.encoding_byte, props);
	else
		(*size)++;
}

void	norm_death(t_vm *vm, int i, t_process *process, int *size)
{
	process->event.args[i] = get_from_arena(vm, process->pc + (*size), 4);
	*size += 4;
}

void	read_arguments(t_vm *vm, t_process *process, t_props *props)
{
	int i;
	int type;
	int size;

	i = -1;
	size = 1;
	handle_encoding(vm, process, props, &size);
	while (++i < props->nb_args)
	{
		type = get_encoding_type(process->event.encoding_byte, i);
		if (type == T_REG)
		{
			process->event.args[i] = get_from_arena(vm, process->pc + size, 1);
			size += 1;
		}
		else if (type == T_IND || props->direct_size == 2)
		{
			process->event.args[i] = get_from_arena(vm, process->pc + size, 2);
			size += 2;
		}
		else
			norm_death(vm, i, process, &size);
	}
}

int		parse_arguments(t_vm *vm, t_process *process)
{
	t_props *props;

	props = instructions_properties(process->event.op_code);
	read_encoding_byte(vm, process, props);
	if (!encoding_byte_valid(process, props))
	{
		return (get_encoded_size(process, props));
	}
	read_arguments(vm, process, props);
	if (!registers_valid(process, props))
		return (get_encoded_size(process, props));
	prepare_arguments(process, props);
	process->event.instruction_size = get_encoded_size(process, props) + 1;
	if (vm->verbose && process->event.op_code)
		print_instruction(vm, process);
	return (0);
}

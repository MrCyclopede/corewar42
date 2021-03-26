/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions3.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:54:32 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 04:32:03 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	inst_ldi(t_vm *vm, t_process *process)
{
	int *args;

	args = (int *)process->event.args;
	if (get_encoding_type(process->event.encoding_byte, 0) == T_IND)
	{
		args[0] = get_from_arena(vm, args[0] % IDX_MOD + process->pc, 4);
	}
	process->reg[process->event.og_args[2]] =
		get_from_arena(vm, (args[0] + args[1]) % IDX_MOD + process->pc, 4);
}

void	inst_sti(t_vm *vm, t_process *process)
{
	int *args;

	args = (int *)process->event.args;
	if (get_encoding_type(process->event.encoding_byte, 1) == T_IND)
		args[1] = get_from_arena(vm, args[1] % IDX_MOD + process->pc, 4);
	set_to_arena(vm, (args[1] + args[2])
		% IDX_MOD + process->pc, args[0], vm->color_arena[process->pc]);
}

void	inst_fork(t_vm *vm, t_process *process)
{
	create_process(vm, process->parent - 4,
		(process->event.args[0] % IDX_MOD + process->pc) % MEM_SIZE, process);
}

void	inst_lld(t_vm *vm, t_process *process)
{
	int *args;

	args = (int *)process->event.args;
	if (get_encoding_type(process->event.encoding_byte, 0) == T_IND)
	{
		args[0] = get_from_arena(vm, args[0] + process->pc, 4);
	}
	process->reg[process->event.og_args[1]] = args[0];
	process->carry = (process->reg[process->event.og_args[1]] == 0);
}

void	inst_lldi(t_vm *vm, t_process *process)
{
	int *args;

	args = (int *)process->event.args;
	if (get_encoding_type(process->event.encoding_byte, 0) == T_IND)
	{
		args[0] = get_from_arena(vm, args[0] % IDX_MOD + process->pc, 4);
	}
	process->reg[process->event.og_args[2]] =
		get_from_arena(vm, (args[0] + args[1]) + process->pc, 4);
	process->carry = (process->reg[process->event.og_args[2]] == 0);
}

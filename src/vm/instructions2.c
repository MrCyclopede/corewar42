/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:54:32 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 04:32:41 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	inst_sub(t_vm *vm, t_process *process)
{
	int *args;

	(void)vm;
	args = (int *)process->event.args;
	process->reg[process->event.og_args[2]] = args[0] - args[1];
	process->carry = (process->reg[process->event.og_args[2]] == 0);
}

void	inst_and(t_vm *vm, t_process *process)
{
	int *args;

	args = (int *)process->event.args;
	if (get_encoding_type(process->event.encoding_byte, 0) == T_IND)
		args[0] = get_from_arena(vm, args[0] % IDX_MOD + process->pc, 4);
	if (get_encoding_type(process->event.encoding_byte, 1) == T_IND)
		args[1] = get_from_arena(vm, args[1] % IDX_MOD + process->pc, 4);
	process->reg[process->event.og_args[2]] = args[0] & args[1];
	process->carry = (process->reg[process->event.og_args[2]] == 0);
}

void	inst_or(t_vm *vm, t_process *process)
{
	int *args;

	args = (int *)process->event.args;
	if (get_encoding_type(process->event.encoding_byte, 0) == T_IND)
		args[0] = get_from_arena(vm, args[0] % IDX_MOD + process->pc, 4);
	if (get_encoding_type(process->event.encoding_byte, 1) == T_IND)
		args[1] = get_from_arena(vm, args[1] % IDX_MOD + process->pc, 4);
	process->reg[process->event.og_args[2]] = args[0] | args[1];
	process->carry = (process->reg[process->event.og_args[2]] == 0);
}

void	inst_xor(t_vm *vm, t_process *process)
{
	int *args;

	args = (int *)process->event.args;
	if (get_encoding_type(process->event.encoding_byte, 0) == T_IND)
		args[0] = get_from_arena(vm, args[0] % IDX_MOD + process->pc, 4);
	if (get_encoding_type(process->event.encoding_byte, 1) == T_IND)
		args[1] = get_from_arena(vm, args[1] % IDX_MOD + process->pc, 4);
	process->reg[process->event.og_args[2]] = args[0] ^ args[1];
	process->carry = (process->reg[process->event.og_args[2]] == 0);
}

void	inst_zjmp(t_vm *vm, t_process *process)
{
	(void)vm;
	if (process->carry)
	{
		process->pc = (process->event.args[0]
			% IDX_MOD + process->pc) % MEM_SIZE;
		if (process->pc < 0)
			process->pc = MEM_SIZE + process->pc;
		process->event.instruction_size = 0;
	}
}

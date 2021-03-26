/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scheduler.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:55:41 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/25 07:54:55 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	set_no_op(t_process *process, int size)
{
	process->event.op_code = 0;
	process->event.instruction_size = size;
}

t_props	*instructions_properties(int instruction)
{
	static t_props	props[17] = {
		{"no_op", 1, 0, 0, {0, 0, 0}, 0},
		{"live", 10, 0, 4, {T_DIR, 0, 0}, 1},
		{"ld", 5, 1, 4, {T_IND | T_DIR, T_REG, 0}, 2},
		{"st", 5, 1, 4, {T_REG, T_IND | T_REG, 0}, 2 },
		{"add", 10, 1, 4, {T_REG, T_REG, T_REG}, 3},
		{"sub", 10, 1, 4, {T_REG, T_REG, T_REG}, 3},
	{"and", 6, 1, 4, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3},
	{"or", 6, 1, 4, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3},
	{"xor", 6, 1, 4, {T_REG | T_IND | T_DIR, T_REG | T_IND | T_DIR, T_REG}, 3},
		{"zjmp", 20, 0, 2, {T_DIR}, 1},
		{"ldi", 25, 1, 2, {T_REG | T_IND | T_DIR, T_DIR | T_REG, T_REG}, 3},
		{"sti", 25, 1, 2, {T_REG, T_REG | T_DIR | T_IND, T_DIR | T_REG}, 3},
		{"fork", 800, 0, 2, {T_DIR}, 1},
		{"lld", 10, 1, 4, {T_DIR | T_IND, T_REG}, 2},
		{"lldi", 50, 1, 2, {T_REG | T_IND | T_DIR, T_DIR | T_REG, T_REG}, 3},
		{"lfork", 1000, 0, 2, {T_DIR}, 1},
		{"aff", 2, 1, 4, {T_REG}, 1}
	};

	return (&props[instruction]);
}

void	get_op_code(t_vm *vm, t_process *process)
{
	process->event.op_code = get_from_arena(vm, process->pc, 1);
	if (process->event.op_code < 1 || process->event.op_code > 16)
		return (set_no_op(process, 1));
}

void	set_execute_in(t_vm *vm, t_process *process)
{
	t_props		*props;

	(void)vm;
	props = instructions_properties(process->event.op_code);
	process->execute_in = props->cost - 1;
}

void	schedule_next_instruction(t_vm *vm, t_process *process)
{
	int old_pc;

	old_pc = process->pc;
	process->pc = (process->pc + process->event.instruction_size) % MEM_SIZE;
	get_op_code(vm, process);
	set_execute_in(vm, process);
	if (vm->verbose)
		print_process_move(vm, process, old_pc);
}

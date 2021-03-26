/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cycle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:54:19 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 06:20:51 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	execute_instruction(t_vm *vm, t_process *process)
{
	int					ret_value;
	static t_inst_func	instructions[17] = {
		no_op,
		inst_live,
		inst_ld,
		inst_st,
		inst_add,
		inst_sub,
		inst_and,
		inst_or,
		inst_xor,
		inst_zjmp,
		inst_ldi,
		inst_sti,
		inst_fork,
		inst_lld,
		inst_lldi,
		inst_lfork,
		inst_aff,
	};

	if (!(ret_value = parse_arguments(vm, process)))
		instructions[(int)process->event.op_code](vm, process);
	else
		set_no_op(process, ret_value + 1);
}

void	do_cycle(t_vm *vm)
{
	t_process *process;

	if (vm->verbose && vm->nb_cycle)
		ft_printf("It is now cycle %d\n", vm->nb_cycle);
	process = vm->process_list;
	while (process)
	{
		if (!process->execute_in)
		{
			execute_instruction(vm, process);
			schedule_next_instruction(vm, process);
		}
		else
			process->execute_in--;
		process = process->next_process;
	}
}

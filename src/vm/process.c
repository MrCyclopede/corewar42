/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:55:28 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/25 07:49:42 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		add_process_to_vm(t_vm *vm, t_process *process)
{
	t_process	*prev;

	prev = vm->process_list;
	vm->process_list = process;
	process->next_process = prev;
}

void		create_process(t_vm *vm, int player_number, int pc, t_process *src)
{
	t_process	*process;

	if (!(process = (t_process*)ft_memalloc(sizeof(t_process))))
		free_and_exit(vm, 42, "malloc exploded");
	process->reg[1] = player_number;
	if (src)
		ft_memcpy(process, src, sizeof(t_process));
	process->id = vm->process_max_id++;
	process->pc = pc;
	process->pc %= MEM_SIZE;
	if (process->pc < 0)
		process->pc = MEM_SIZE + process->pc;
	process->event.instruction_size = 0;
	process->next_process = 0;
	process->next_event = 0;
	add_process_to_vm(vm, process);
	schedule_next_instruction(vm, process);
	process->parent = player_number + 4;
}

void		init_processes(t_vm *vm)
{
	int	i;
	int k;

	i = 0;
	k = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->players[i].in_use)
		{
			create_process(vm, vm->players[i].player_code,
					(MEM_SIZE / vm->nb_players) * k, 0);
			k++;
		}
		i++;
	}
}

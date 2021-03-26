/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions1.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:54:32 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 04:26:01 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	no_op(t_vm *vm, t_process *process)
{
	(void)vm;
	(void)process;
}

void	inst_live(t_vm *vm, t_process *process)
{
	int	i;

	process->last_alive = vm->nb_cycle;
	vm->lives_this_round++;
	i = 0;
	while (i < MAX_PLAYERS)
	{
		if (vm->players[i].in_use
				&& vm->players[i].player_code == process->event.args[0])
		{
			if (vm->verbose)
				ft_printf("Player %d (%s) is said to be alive\n",
						i + 1, vm->players[i].name);
			else
				ft_printf("A process shows that player %d (%s) is alive\n",
						i + 1, vm->players[i].name);
			vm->last_alive = i;
			break ;
		}
		i++;
	}
}

void	inst_ld(t_vm *vm, t_process *process)
{
	int *args;

	(void)vm;
	args = (int *)process->event.args;
	if (get_encoding_type(process->event.encoding_byte, 0) == T_DIR)
		process->reg[process->event.og_args[1]] = args[0];
	else
		process->reg[process->event.og_args[1]] =
			get_from_arena(vm, args[0] % IDX_MOD + process->pc, 4);
	process->carry = (process->reg[process->event.og_args[1]] == 0);
}

void	inst_st(t_vm *vm, t_process *process)
{
	int *args;

	(void)vm;
	args = (int *)process->event.args;
	if (get_encoding_type(process->event.encoding_byte, 1) == T_REG)
		process->reg[process->event.og_args[1]] = args[0];
	else
		set_to_arena(vm, args[1] % IDX_MOD
			+ process->pc, args[0], vm->color_arena[process->pc]);
}

void	inst_add(t_vm *vm, t_process *process)
{
	int *args;

	(void)vm;
	args = (int *)process->event.args;
	process->reg[process->event.og_args[2]] = args[0] + args[1];
	process->carry = (process->reg[process->event.og_args[2]] == 0);
}

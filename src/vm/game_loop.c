/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:52:30 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/25 08:11:37 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		kill_process(t_vm *vm, t_process *process, t_process **p_next)
{
	if (vm->verbose)
		ft_printf("Process %d hasn't lived for %d cycles (CTD %d)\n",
				process->id, vm->nb_cycle - 1 - process->last_alive,
				vm->round_size);
	*p_next = process->next_process;
	free(process);
}

void		round_check(t_vm *vm)
{
	t_process **p_next;
	t_process *process;

	p_next = &vm->process_list;
	while (*p_next)
	{
		process = *p_next;
		if (process->last_alive < vm->nb_cycle - vm->round_size)
			kill_process(vm, process, p_next);
		else
			p_next = &((*p_next)->next_process);
	}
	vm->checks_since_decrementation++;
	if (vm->checks_since_decrementation >= MAX_CHECKS
			|| vm->lives_this_round >= NBR_LIVE)
	{
		vm->round_size -= CYCLE_DELTA;
		if (vm->round_size <= 0)
			vm->round_size = 1;
		vm->checks_since_decrementation = 0;
		if (vm->verbose)
			ft_printf("Cycle to die is now %d\n", vm->round_size);
	}
}

int			ask_step(t_vm *vm)
{
	static int	nb_steps = 1;
	static int	rd_steps = 1;
	int			ret;
	char		buf[11];

	if (!--nb_steps)
	{
		dump_arena(vm);
		ft_bzero(&buf, 11);
		ret = read(0, buf, 10);
		buf[ret] = 0;
		if (ft_atoi(buf))
			rd_steps = ft_atoi(buf);
		nb_steps = rd_steps;
	}
	return (0);
}

void		do_round(t_vm *vm)
{
	int i;

	i = 0;
	vm->lives_this_round = 0;
	while (i < vm->round_size)
	{
		if (vm->nb_cycle == vm->dump_cycle)
		{
			dump_arena(vm);
			free_and_exit(vm, 0, 0);
		}
		if (vm->nb_cycle)
			do_cycle(vm);
		vm->nb_cycle++;
		if (vm->step_by_step)
			ask_step(vm);
		if (vm->nb_cycle != 1)
			i++;
	}
	round_check(vm);
}

void		game_loop(t_vm *vm)
{
	while (vm->process_list)
		do_round(vm);
	if (vm->last_alive >= 0)
		ft_printf("Contestant %d, \"%s\", has won !\n",
				vm->last_alive + 1,
				vm->players[vm->last_alive].name);
	else
		ft_printf("Nobody won cause nobody said \"alive\". Boo !\n");
}

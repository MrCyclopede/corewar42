/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:54:44 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/25 05:14:38 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void		free_and_exit(t_vm *vm, int ret, const char *message)
{
	t_process *lst;
	t_process *to_free;

	lst = vm->process_list;
	while (lst)
	{
		to_free = lst;
		lst = lst->next_process;
		free(to_free);
	}
	if (message)
	{
		ft_putstr("ERROR ");
		ft_putendl(message);
	}
	exit(ret);
}

void		attribute_player_codes(t_vm *vm)
{
	int i;

	i = 0;
	while (i < MAX_PLAYERS)
	{
		vm->players[i].player_code = (i + 1) * -1;
		i++;
	}
}

void		init_vm(t_vm *vm, int argc, char **argv)
{
	ft_bzero(vm, sizeof(t_vm));
	vm->dump_cycle = -1;
	vm->round_size = CYCLE_TO_DIE;
	vm->process_max_id = 1;
	vm->last_alive = -1;
	attribute_player_codes(vm);
	parsing(vm, argc, argv);
	attribute_player_codes(vm);
	if (!vm->nb_players)
		free_and_exit(vm, 7, "no player specified");
	load_bin_to_arena(vm);
	vm->nb_cycle = 0;
	init_processes(vm);
}

int			main(int argc, char **argv)
{
	t_vm	vm;

	init_vm(&vm, argc, argv);
	game_loop(&vm);
	free_and_exit(&vm, 0, NULL);
	return (0);
}

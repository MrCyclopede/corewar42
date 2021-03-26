/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 07:56:29 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/25 08:15:19 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_process_move(t_vm *vm, t_process *process, int old_pc)
{
	int move;
	int i;

	i = 0;
	if (old_pc == process->pc || old_pc + 1 == process->pc
			|| (old_pc == (MEM_SIZE - 1) && !process->pc))
		return ;
	if (old_pc > process->pc)
		move = MEM_SIZE - old_pc + process->pc;
	else
		move = process->pc - old_pc;
	ft_printf("ADV %d (0x%.4x -> 0x%.4x)", move, old_pc, process->pc);
	while (i < move)
	{
		ft_printf(" %.2x", get_from_arena(vm, old_pc + i, 1));
		i++;
	}
	ft_printf(" \n");
}

void	print_index_access_arena(char *str, int pos, int i, t_process *process)
{
	ft_printf("\n       | -> %s %d + %d = %d (with pc and mod %d)",
			str, pos, i,
			pos + i, (((pos + i) % IDX_MOD + process->pc)) % MEM_SIZE);
}

void	print_instruction(t_vm *vm, t_process *process)
{
	t_props	*props;

	(void)vm;
	if (process->event.op_code == 16)
		return ;
	props = instructions_properties(process->event.op_code);
	ft_printf("P%5d | %s", process->id, props->name);
	print_args(vm, process, props);
	ft_printf("\n");
}

int		process_highlight_print(t_vm *vm, int arena_index, char c)
{
	t_process *lst;

	lst = vm->process_list;
	while (lst)
	{
		if (lst->pc == arena_index)
			return (highlight_print(c, lst->parent + 1));
		lst = lst->next_process;
	}
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 02:35:03 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 04:36:10 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	print_args_2(t_vm *vm, t_process *process, t_props *props)
{
	(void)vm;
	(void)props;
	if (process->event.op_code == 9)
	{
		if (process->carry)
			ft_printf(" OK");
		else
			ft_printf(" FAILED");
	}
	if (process->event.op_code == 10)
		print_index_access_arena("load from",
				process->event.args[0], process->event.args[1], process);
	if (process->event.op_code == 11)
		print_index_access_arena("store to",
				process->event.args[1], process->event.args[2], process);
	if (process->event.op_code == 12)
		if ((((process->event.args[0]) % IDX_MOD + process->pc)) % MEM_SIZE)
			ft_printf(" (%d)", (((process->event.args[0])
							% IDX_MOD + process->pc)) % MEM_SIZE);
	if (process->event.op_code == 15)
		if (process->event.args[0] + process->pc)
			ft_printf(" (%d)", (process->event.args[0] + process->pc));
}

void	print_args(t_vm *vm, t_process *process, t_props *props)
{
	int i;

	i = 0;
	while (i < props->nb_args)
	{
		ft_printf(" ");
		if (process->event.op_code == 11 && i == 2
				&& get_encoding_type(process->event.encoding_byte, i) == T_REG)
			ft_printf("%d", process->reg[process->event.og_args[i]]);
		else
		{
			if (get_encoding_type(process->event.encoding_byte, i) == T_REG)
				ft_printf("r");
			ft_printf("%d", process->event.og_args[i]);
		}
		i++;
	}
	print_args_2(vm, process, props);
}

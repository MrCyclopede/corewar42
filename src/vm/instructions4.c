/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   instructions4.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:54:32 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 04:34:02 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

void	inst_lfork(t_vm *vm, t_process *process)
{
	create_process(vm, process->parent - 4,
		(process->event.args[0] + process->pc) % MEM_SIZE, process);
}

void	inst_aff(t_vm *vm, t_process *process)
{
	char val;

	(void)vm;
	val = process->event.args[0] % 256;
	if (val < 0)
		val += 256;
	ft_printf("aff : %c\n", val);
}

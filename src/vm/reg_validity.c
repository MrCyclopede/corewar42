/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reg_validity.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 05:32:43 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/25 05:33:05 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		reg_is_valid(int reg)
{
	return (reg > 0 && reg < 17);
}

int		registers_valid(t_process *process, t_props *props)
{
	int i;
	int type;

	i = 0;
	while (i < props->nb_args)
	{
		type = get_encoding_type(process->event.encoding_byte, i);
		if (type == T_REG)
		{
			if (process->event.args[i] < 1 || process->event.args[i] > 16)
				return (0);
		}
		i++;
	}
	return (1);
}

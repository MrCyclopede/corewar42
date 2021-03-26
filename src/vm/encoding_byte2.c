/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding_byte2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 05:20:47 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/25 05:26:12 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		encoding_byte_valid(t_process *process, t_props *props)
{
	int i;
	int type;

	i = 0;
	if (!props->has_encoding_byte)
		return (1);
	while (i < props->nb_args)
	{
		type = get_encoding_type(process->event.encoding_byte, i);
		if (!(type & props->args_type[i]))
			return (0);
		i++;
	}
	return (1);
}

void	sanitize_encoding_byte(char *byte, t_props *props)
{
	int	i;

	i = 0;
	while (i < props->nb_args)
	{
		if (props->args_type[i] == T_REG ||
				props->args_type[i] == T_IND ||
				props->args_type[i] == T_DIR)
		{
			set_encoding_type(byte, i, props->args_type[i]);
		}
		i++;
	}
	while (i < 3)
	{
		set_encoding_type(byte, i, 0);
		i++;
	}
}

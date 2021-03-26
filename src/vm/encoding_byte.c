/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   encoding_byte.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 06:21:36 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/25 05:23:58 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

t_arg_type	get_encoding_type(unsigned char encoding_byte, int i)
{
	int j;

	j = 0;
	while (j < i)
	{
		encoding_byte <<= 2;
		j++;
	}
	encoding_byte >>= 6;
	if (encoding_byte == 1)
		return (T_REG);
	if (encoding_byte == 2)
		return (T_DIR);
	if (encoding_byte == 3)
		return (T_IND);
	return (0);
}

void		set_encoding_type(char *encoding_byte, int i, t_arg_type type)
{
	unsigned char	mask;
	int				j;

	mask = 192;
	j = 0;
	while (j < i)
	{
		mask >>= 2;
		j++;
	}
	*encoding_byte &= ~mask;
	if (type == T_REG)
		mask = 64;
	else if (type == T_DIR)
		mask = 128;
	else if (type == T_IND)
		mask = 192;
	j = 0;
	while (j < i)
	{
		mask >>= 2;
		j++;
	}
	*encoding_byte |= mask;
}

int			get_encoded_size(t_process *process, t_props *props)
{
	int			i;
	int			size;
	t_arg_type	type;

	i = 0;
	size = 0;
	if (props->has_encoding_byte)
		size++;
	while (i < props->nb_args)
	{
		type = get_encoding_type(process->event.encoding_byte, i);
		if (!type)
			;
		else if (type == T_REG)
			size += 1;
		else if (type == T_IND || props->direct_size == 2)
			size += 2;
		else
			size += 4;
		i++;
	}
	return (size);
}

void		read_encoding_byte(t_vm *vm, t_process *process, t_props *props)
{
	if (props->has_encoding_byte)
		process->event.encoding_byte = get_from_arena(vm, process->pc + 1, 1);
	else
		process->event.encoding_byte = 0;
}

int			encoding_byte_null(t_process *process, t_props *props)
{
	int i;
	int type;

	i = 0;
	if (!props->has_encoding_byte)
		return (0);
	while (i < props->nb_args)
	{
		type = get_encoding_type(process->event.encoding_byte, i);
		if (!type)
			return (1);
		i++;
	}
	return (0);
}

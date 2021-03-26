/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arena_read_write.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/29 23:37:57 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 07:07:07 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		get_from_arena(t_vm *vm, int index, int size_of)
{
	index %= MEM_SIZE;
	if (index < 0)
		index = MEM_SIZE + index;
	if (size_of == 1)
		return ((int)vm->arena[index]);
	else if (size_of == 2)
		return ((int16_t)((uint32_t)vm->arena[index] << 8)
			+ (uint32_t)vm->arena[(index + 1) % MEM_SIZE]);
	else if (size_of == 4)
		return (((uint32_t)vm->arena[index % MEM_SIZE] << 24)
				+ ((uint32_t)vm->arena[(index + 1) % MEM_SIZE] << 16)
				+ ((uint32_t)vm->arena[(index + 2) % MEM_SIZE] << 8)
				+ ((uint32_t)vm->arena[(index + 3) % MEM_SIZE]));
		return (0);
}

void	set_to_arena(t_vm *vm, int index, int value, int color)
{
	index %= MEM_SIZE;
	if (index < 0)
		index = MEM_SIZE + index;
	if (vm->colored)
	{
		vm->color_arena[index % MEM_SIZE] = color;
		vm->color_arena[(index + 1) % MEM_SIZE] = color;
		vm->color_arena[(index + 2) % MEM_SIZE] = color;
		vm->color_arena[(index + 3) % MEM_SIZE] = color;
	}
	vm->arena[index % MEM_SIZE] = value >> 24;
	vm->arena[(index + 1) % MEM_SIZE] = value << 8 >> 24;
	vm->arena[(index + 2) % MEM_SIZE] = value << 16 >> 24;
	vm->arena[(index + 3) % MEM_SIZE] = value << 24 >> 24;
}

int		norme_made_me_do_horible_things(t_vm *vm)
{
	ft_printf("Introducing contestants...\n");
	return (MEM_SIZE / vm->nb_players);
}

void	norme_made_me_do_horible_things_twice(t_vm *vm, int k)
{
	ft_printf("* Player %d, weighing %d bytes, \"%s\" (\"%s\") !\n",
		k + 1, vm->players[k].champion_size,
		vm->players[k].name, vm->players[k].comment);
}

void	load_bin_to_arena(t_vm *vm)
{
	int	i;
	int	j;
	int k;
	int	offset;

	i = 0;
	k = -1;
	offset = norme_made_me_do_horible_things(vm);
	while (++k < MAX_PLAYERS)
	{
		if (vm->players[k].in_use)
		{
			norme_made_me_do_horible_things_twice(vm, k);
			j = 0;
			while (j < (int)vm->players[k].champion_size)
			{
				if (vm->colored)
					vm->color_arena[offset * i + j] = k + 1;
				vm->arena[offset * i + j] = vm->players[k].champion[j];
				j++;
			}
			i++;
		}
	}
}

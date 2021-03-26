/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/26 02:35:03 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 04:37:38 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		highlight_print(char c, int color)
{
	if (color == 1)
		ft_putstr("\033[30;106m");
	else if (color == 2)
		ft_putstr("\033[30;43m");
	else if (color == 3)
		ft_putstr("\033[30;42m");
	else if (color == 4)
		ft_putstr("\033[0;41m");
	else
		ft_putstr("\033[0;45m");
	ft_printf("%2.2x ", (unsigned char)c);
	return (color);
}

void	color_print(char c, int color)
{
	if (color == 1)
	{
		ft_putstr("\033[0;31m");
	}
	else if (color == 2)
	{
		ft_putstr("\033[0;32m");
	}
	else if (color == 3)
	{
		ft_putstr("\033[0;33m");
	}
	else if (color == 4)
	{
		ft_putstr("\033[0;96m");
	}
	ft_printf("%2.2x ", (unsigned char)c);
}

void	dump_arena_colored(t_vm *vm)
{
	int	line;
	int	i;
	int size;

	size = 64;
	line = 0;
	while (line < MEM_SIZE / size)
	{
		i = 0;
		while (i < size)
		{
			if (process_highlight_print(vm, line * size + i,
						(unsigned char)vm->arena[line * size + i]))
				;
			else if (vm->color_arena[line * size + i])
				color_print((unsigned char)vm->arena[line * size + i],
						vm->color_arena[line * size + i]);
			else
				ft_printf("%2.2x ", (unsigned char)vm->arena[line * size + i]);
			ft_putstr("\033[0;0m");
			i++;
		}
		ft_printf("\n");
		line++;
	}
}

void	dump_arena(t_vm *vm)
{
	int	line;
	int	i;
	int size;

	size = 32;
	if (vm->colored)
		return (dump_arena_colored(vm));
	line = 0;
	while (line < MEM_SIZE / size)
	{
		i = 0;
		while (i < size)
		{
			ft_printf("%2.2x ", (unsigned char)vm->arena[line * size + i]);
			i++;
		}
		ft_printf("\n");
		line++;
	}
}

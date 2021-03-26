/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/25 05:36:37 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 06:33:39 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"
#include <fcntl.h>

void			relocate_player(t_vm *vm, int player)
{
	int		new_slot;
	int		save_pcode;

	new_slot = find_available_player_slot(vm, -1);
	save_pcode = vm->players[new_slot].player_code;
	ft_memcpy(&vm->players[new_slot], &vm->players[player], sizeof(t_player));
	vm->players[new_slot].in_use = 1;
	vm->players[new_slot].player_code = save_pcode;
}

int				read_file(const char *path, char (*buffer)[16
				+ PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 1])
{
	int fd;

	if ((fd = open(path, O_RDONLY)) < 0)
		return (0);
	if (read(fd, *buffer, 16
				+ PROG_NAME_LENGTH
				+ COMMENT_LENGTH
				+ CHAMP_MAX_SIZE) < 0)
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int				paddings_are_zero(char *buffer)
{
	int pos1;
	int pos2;

	pos1 = 4 + PROG_NAME_LENGTH;
	pos2 = pos1 + 8 + COMMENT_LENGTH;
	if (*(int *)(&buffer[pos1]) || *(int *)(&buffer[pos2]))
		return (0);
	return (1);
}

int				magic_number_is_valid(char *buffer)
{
	return (buffer[0] == 0
			&& buffer[1] == -22
			&& buffer[2] == -125
			&& buffer[3] == -13);
}

unsigned int	get_champion_size(char *buffer)
{
	unsigned int size;

	size = 0;
	size = (unsigned char)buffer[139];
	size += (unsigned char)buffer[138] * 256;
	size += (unsigned char)buffer[137] * 65536;
	size += (unsigned char)buffer[136] * 16777216;
	return (size);
}

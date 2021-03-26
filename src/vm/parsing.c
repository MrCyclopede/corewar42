/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/25 01:55:17 by rcourtoi          #+#    #+#             */
/*   Updated: 2020/07/26 07:24:37 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vm.h"

int		find_available_player_slot(t_vm *vm, int wished)
{
	int i;

	i = 0;
	if (wished >= 0)
	{
		if (vm->players[wished].in_use == 2)
			free_and_exit(vm, 10, "player number collision");
		else if (vm->players[wished].in_use == 1)
			relocate_player(vm, wished);
		return (wished);
	}
	while (i < 4)
	{
		if (!vm->players[i].in_use)
			return (i);
		i++;
	}
	free_and_exit(vm, 12, "player number unsolvable");
	return (1);
}

void	get_champion(t_vm *vm, const char *path, int player_number)
{
	char	buffer[16 + PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 1];
	int		i;

	i = find_available_player_slot(vm, player_number - 1);
	ft_bzero(buffer, 16 +
			PROG_NAME_LENGTH + COMMENT_LENGTH + CHAMP_MAX_SIZE + 1);
	if (!read_file(path, &buffer))
		free_and_exit(vm, 2, "cannot open or read the file");
	if (!magic_number_is_valid(buffer))
		free_and_exit(vm, 3, "invalid magic number");
	ft_memcpy(vm->players[i].name, buffer + 4, PROG_NAME_LENGTH);
	if (!vm->players[i].name[0])
		free_and_exit(vm, 4, "champion has no or invalid name");
	ft_memcpy(vm->players[i].comment,
			buffer + PROG_NAME_LENGTH + 12, COMMENT_LENGTH);
	vm->players[i].champion_size = get_champion_size(buffer);
	if (vm->players[i].champion_size > CHAMP_MAX_SIZE
			|| vm->players[i].champion_size <= 0)
		free_and_exit(vm, 5, "champion size invalid");
	ft_memcpy(vm->players[i].champion,
			buffer + (16 + PROG_NAME_LENGTH + COMMENT_LENGTH),
			vm->players[i].champion_size);
	if (!paddings_are_zero(buffer))
		free_and_exit(vm, 6, "paddings are not zero");
	vm->players[i].in_use = player_number ? 2 : 1;
}

int		parse_options_bis(t_vm *vm, int argc, char **argv, int *i)
{
	if (argc > *i && !ft_strcmp(argv[*i], "-c"))
	{
		vm->colored = 1;
		(*i)++;
	}
	else if (argc > *i && !ft_strcmp(argv[*i], "-s"))
	{
		vm->step_by_step = 1;
		(*i)++;
	}
	else if (argc > *i && !ft_strcmp(argv[*i], "-v"))
	{
		vm->verbose = 1;
		(*i)++;
	}
	else
		return (0);
	return (1);
}

void	parse_options(t_vm *vm, int argc, char **argv, int *i)
{
	(*i) = 1;
	if (argc == 1)
		free_and_exit(vm, 6, "use: ./corewar {-c/s/v} [(-n) champion1.cor]");
	while (argc > *i && argv[*i][0] == '-' && argv[*i][1] != 'n')
	{
		if (argc > 1 && !ft_strcmp(argv[*i], "-dump"))
		{
			(*i)++;
			if (!(argc > 2) || (vm->dump_cycle = ft_atoi(argv[*i])) <= 0)
				free_and_exit(vm, 1, "dump cycle invalid");
			(*i)++;
		}
		else if (!parse_options_bis(vm, argc, argv, i))
			free_and_exit(vm, 91, "wrong arguments");
	}
}

void	parsing(t_vm *vm, int argc, char **argv)
{
	int i;
	int	n;
	int	champion_nb;

	champion_nb = 0;
	parse_options(vm, argc, argv, &i);
	while (i < argc)
	{
		if (champion_nb == 4)
			free_and_exit(vm, 4, "too many arguments");
		n = 0;
		if (!ft_strcmp(argv[i], "-n"))
		{
			if (++i < argc)
				n = ft_atoi(argv[i]);
			if (n < 1 || n > 4)
				free_and_exit(vm, 1, "invalid player number");
			i++;
		}
		if (!(argc > i))
			free_and_exit(vm, 1, "missing champion file");
		get_champion(vm, argv[i++], n);
		champion_nb++;
	}
	vm->nb_players = champion_nb;
}

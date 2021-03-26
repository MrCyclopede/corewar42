/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 14:21:47 by qgirard           #+#    #+#             */
/*   Updated: 2020/08/04 19:33:40 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "asm.h"
#include "op.h"
#include "libft.h"
#include "ft_printf.h"

static t_op	g_op_tab[17] =
{
	{"PADDING", 0, 0, 0, "PADDING", 0, 0},
	{"live", 1, 400, 10, "alive", 0, 0},
	{"ld", 2, 610, 5, "load", 1, 0},
	{"st", 2, 130, 5, "store", 1, 0},
	{"add", 3, 111, 10, "addition", 1, 0},
	{"sub", 3, 111, 10, "soustraction", 1, 0},
	{"and", 3, 771, 6,
		"et (and  r1, r2, r3   r1&r2 -> r3", 1, 0},
	{"or", 3, 771, 6,
		"ou  (or   r1, r2, r3   r1 | r2 -> r3", 1, 0},
	{"xor", 3, 771, 6,
		"ou (xor  r1, r2, r3   r1^r2 -> r3", 1, 0},
	{"zjmp", 1, 400, 20, "jump if zero", 0, 1},
	{"ldi", 3, 751, 25,
		"load index", 1, 1},
	{"sti", 3, 175, 25,
		"store index", 1, 1},
	{"fork", 1, 400, 800, "fork", 0, 1},
	{"lld", 2, 610, 10, "long load", 1, 0},
	{"lldi", 3, 761, 50,
		"long load index", 1, 1},
	{"lfork", 1, 400, 1000, "long fork", 0, 1},
	{"aff", 1, 100, 2, "aff", 1, 0},
};

static void		display_code(t_code_line *code_line)
{
	t_token *token;

	ft_printf("\nLine:\tSize in Binairy:\tToken stream:\n\n");
	while (code_line)
	{
		token = code_line->token;
		ft_printf("%d:\t", code_line->nb_line);
		ft_printf("[%d]\t\t\t", code_line->instruction_size);
		while (token)
		{
			if (token->type != TOKEN_TYPE_SEPARATOR)
			{
				ft_putstr("<");
				print_token(token->length, &code_line->line[token->position]);
				ft_putstr("> ");
			}
			token = token->next;
		}
		ft_putstr("\n");
		code_line = code_line->next;
	}
	ft_printf("\n<===============>\nWriting out .cor file.\n");
}

static int		is_invalid_filename(char *filename)
{
	int		dif;
	int		index;

	index = ft_strlen(filename) - 2;
	dif = ft_strcmp(&filename[index], ".s");
	if (dif)
		return (1);
	return (0);
}

static int		check_args_and_open_files(int argc, char **argv, t_data **data)
{
	int			fd;

	fd = 0;
	if (!(*data = (t_data*)ft_memalloc(sizeof(t_data))))
		return (error_msg(ERR_MEMORY_ALLOCATION, 0));
	if (argc != 2)
		return (error_msg(ERR_MAIN_NB_PARAMETERS, 0));
	if (argv[1] && is_invalid_filename(argv[1]))
		return (error_msg(ERR_MAIN_FILE_TYPE, 0));
	else if (!(argv[1] && (fd = open(argv[1], O_RDONLY)) == -1))
	{
		if (!((*data)->file_name = ft_strdup(argv[1])))
			return (error_msg(ERR_MEMORY_ALLOCATION, 0));
	}
	else
		return (error_msg(ERR_MAIN_OPEN_FILE, 0));
	return (fd);
}

/*
** ==================== main ====================
** check args number
** check file name format
** open champ .s file
** call lexer
** call parser
** call translater (or error mode if errors)
*/

int				main(int argc, char **argv)
{
	int			fd;
	t_data		*data;
	t_code_line	*code_line;

	data = NULL;
	code_line = NULL;
	if (!(fd = check_args_and_open_files(argc, argv, &data)))
		return (free_data(&data));
	if (!header(fd, &data))
		return (free_data(&data));
	data->op_tab = g_op_tab;
	if (!lexer(fd, &data, &code_line))
		return (free_all(&data, &code_line));
	if (!parser(&data, &code_line))
		return (free_all(&data, &code_line));
	if (data->errors)
		error_mode(&code_line);
	else
	{
		if (!translator(&data, &code_line))
			return (free_all(&data, &code_line));
		display_code(code_line);
	}
	free_all(&data, &code_line);
	return (0);
}

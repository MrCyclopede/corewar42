/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_header.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 13:08:47 by amamy             #+#    #+#             */
/*   Updated: 2020/07/19 22:08:50 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "libft.h"
#include "ft_printf.h"

static void	write_magic_number(int fd)
{
	int				magic_number;
	unsigned char	magic_number_binary[4];

	magic_number = COREWAR_EXEC_MAGIC;
	magic_number_binary[0] = magic_number >> 24;
	magic_number_binary[1] = magic_number >> 16;
	magic_number_binary[2] = magic_number >> 8;
	magic_number_binary[3] = magic_number >> 0;
	write(fd, magic_number_binary, 4);
}

static void	write_comment(t_data *data, int fd)
{
	char comment_binary[2048];
	char padding_binary[4];

	ft_bzero(&comment_binary, 2048);
	ft_strcpy(comment_binary, data->comment);
	write(fd, comment_binary, 2048);
	ft_bzero(&padding_binary, 4);
	write(fd, padding_binary, 4);
}

static void	write_name(t_data *data, int fd)
{
	char name_binary[128];
	char padding_binary[4];

	ft_bzero(&name_binary, 128);
	ft_strcpy(name_binary, data->name);
	write(fd, name_binary, 128);
	ft_bzero(&padding_binary, 4);
	write(fd, padding_binary, 4);
}

static void	write_instruction_section_size(t_data *data, int fd)
{
	unsigned char instruction_size_binary[4];

	instruction_size_binary[0] = data->instruction_section_size >> 24;
	instruction_size_binary[1] = data->instruction_section_size >> 16;
	instruction_size_binary[2] = data->instruction_section_size >> 8;
	instruction_size_binary[3] = data->instruction_section_size >> 0;
	write(fd, instruction_size_binary, 4);
}

void		write_header(t_data *data, int fd)
{
	write_magic_number(fd);
	write_name(data, fd);
	write_instruction_section_size(data, fd);
	write_comment(data, fd);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 00:36:04 by amamy             #+#    #+#             */
/*   Updated: 2020/08/04 19:32:05 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "op.h"
#include "asm.h"
#include "libft.h"

#include "ft_printf.h"

static int	get_to_str(char *buff, char *cmd)
{
	int		i;

	i = 0;
	if (!buff)
		return (0);
	while (buff[i] && is_whitespace(buff[i]))
		i++;
	if (ft_strncmp(cmd, &buff[i], ft_strlen(cmd)))
		return (0);
	else
		i += ft_strlen(cmd);
	while (buff[i] && is_whitespace(buff[i]))
		i++;
	if (buff[i] == '\"')
		return (i + 1);
	return (0);
}

static int	check_end(t_data *data, char *buff, int max_size, int j)
{
	if (buff[j] == '\"')
	{
		if (is_significant(&buff[j + 1]))
		{
			ft_memdel((void*)&buff);
			return (error_msg("Syntax Error after command", 0));
		}
		data->name_ok = max_size == PROG_NAME_LENGTH ? 1 : data->name_ok;
		data->comment_ok = max_size == COMMENT_LENGTH ? 1 : data->comment_ok;
		ft_memdel((void*)&buff);
		return (1);
	}
	ft_memdel((void*)&buff);
	return (error_msg(ERR_HEADER_TOO_LONG, 0));
}

static int	concat_and_memdel(t_data *data, char *dst, char *buff)
{
	int		i;
	int		j;
	int		max_size;

	i = 0;
	j = 0;
	max_size = set_max_size(data, dst);
	while (i < max_size && buff[j] != '\"')
	{
		while (!buff[j])
		{
			data->index_line++;
			if (i++ < max_size)
				ft_strcat(dst, "\n");
			else
				return (return_msg_free(ERR_HEADER_TOO_LONG, 0, (void*)&buff));
			ft_memdel((void*)&buff);
			if ((!(get_next_line(data->fd, &buff) > 0 && ++data->index_line)))
				return (return_msg_free(ERR_HEADER, 0, (void*)&buff));
			j = 0;
		}
		if (buff[j] != '\"')
			dst[i++] = buff[j++];
	}
	return (check_end(data, buff, max_size, j));
}

/*
** ==================== get_cmd ====================
** Looks for the lines where the commands .name and
** ".comment" are and send call parse functions.
*/

static int	get_cmd(int fd, t_data *data)
{
	char	*buf;
	char	*cmd_string;
	char	*writting_buffer;
	int		idx;

	buf = NULL;
	writting_buffer = NULL;
	if (!(cmd_string = ft_memalloc(sizeof(char) * 2100)))
		return (error_msg(ERR_MEMORY_ALLOCATION, 0));
	while (get_next_line(fd, &buf) > 0 \
	&& ++data->index_line && !is_significant(buf))
		ft_memdel((void*)&buf);
	if ((idx = get_to_str(buf, ".name")))
		writting_buffer = data->name;
	else if ((idx = get_to_str(buf, ".comment")))
		writting_buffer = data->comment;
	else if (free_buff((void*)&cmd_string))
		return (return_msg_free("Wrong syntax in header", 0, (void*)&buf));
	ft_strncat(cmd_string, &buf[idx], 2075);
	ft_memdel((void*)&buf);
	if (!concat_and_memdel(data, writting_buffer, cmd_string))
		return (0);
	return (1);
}

int			header(int fd, t_data **data)
{
	ft_bzero(&(*data)->name, 129);
	ft_bzero(&(*data)->comment, 2049);
	(*data)->index_line = 1;
	(*data)->fd = fd;
	if (!get_cmd(fd, *data))
		return (0);
	if (!get_cmd(fd, *data))
		return (0);
	if ((*data)->name_ok && (*data)->comment_ok)
		return (1);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/23 23:11:31 by amamy             #+#    #+#             */
/*   Updated: 2020/07/23 23:11:44 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

static int	get_return(char **line)
{
	if ((**line))
		return (1);
	else
	{
		ft_strdel(line);
		return (0);
	}
}

int			get_next_line(const int fd, char **line)
{
	static char	fdstock[FOPEN_MAX][BUFF_SIZE + 1];
	char		*tmp;
	int			ret;

	tmp = fdstock[fd];
	if (!line || fd < 0 || BUFF_SIZE < 1 || read(fd, NULL, 0) < 0)
		return (-1);
	if (!((*line) = ft_strnew(0)))
		return (-1);
	while (1)
	{
		if (ft_strchr(tmp, '\n'))
		{
			(*line) = ft_strnjoinf((*line), tmp, 1,
				(ft_strchr(tmp, '\n') - tmp));
			ft_strncpy(tmp, &tmp[ft_strchr(tmp, '\n') - tmp + 1],
				BUFF_SIZE - (ft_strchr(tmp, '\n') - tmp));
			return (1);
		}
		(*line) = ft_strnjoinf((*line), tmp, 1, BUFF_SIZE);
		ret = read(fd, fdstock[fd], BUFF_SIZE);
		tmp[ret] = '\0';
		if (ret == 0)
			return (get_return(line) == 1 ? 1 : 0);
	}
}

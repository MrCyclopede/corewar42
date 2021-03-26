/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_output_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 12:58:02 by amamy             #+#    #+#             */
/*   Updated: 2020/08/03 23:06:36 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/stat.h>
#include <fcntl.h>
#include "asm.h"
#include "libft.h"

static char	*edit_ext_to_cor(char *file_name)
{
	int		i;
	char	*cor_file;

	if (!(cor_file = ft_memalloc(sizeof(char) * (ft_strlen(file_name) + 3))))
	{
		ft_putendl(ERR_MEMORY_ALLOCATION);
		return (0);
	}
	ft_strcpy(cor_file, file_name);
	i = ft_strlen(file_name) + 1;
	cor_file[i--] = 'r';
	cor_file[i--] = 'o';
	cor_file[i--] = 'c';
	return (cor_file);
}

int			create_output_file(t_data *data)
{
	int		fd;
	char	*file_name;

	fd = 0;
	if (!(file_name = edit_ext_to_cor(data->file_name)))
		return (-1);
	if (((fd = open(file_name, O_RDWR | O_CREAT | O_TRUNC, 0644)) == -1))
	{
		ft_putendl("Error while opening .cor file for writing");
		return (-1);
	}
	ft_memdel((void*)&file_name);
	return (fd);
}

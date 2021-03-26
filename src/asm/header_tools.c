/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   header_tools.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amamy <amamy@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 18:05:29 by amamy             #+#    #+#             */
/*   Updated: 2020/07/25 22:19:36 by amamy            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "asm.h"
#include "tokens.h"
#include "libft.h"

/*
** ==================== is_significant ====================
** This function check if the string passed in argument contain other things
** than whitespaces or comments. If yes, return an false, else return true
*/

int	is_significant(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		while (str[i] && is_whitespace(str[i]))
			i++;
		if (is_comment_char(str[i]) || !str[i])
			return (0);
		else
			return (1);
		i++;
	}
	return (0);
}

int	free_buff(char *buff)
{
	ft_memdel((void*)buff);
	return (1);
}

int	set_max_size(t_data *data, char *dst)
{
	if (dst == data->name)
		return (PROG_NAME_LENGTH);
	else if (dst == data->comment)
		return (COMMENT_LENGTH);
	return (0);
}

int	print_token(int length, char *str)
{
	int i;

	i = 0;
	while (str[i] && i < length)
	{
		ft_putchar(str[i]);
		i++;
	}
	return (1);
}

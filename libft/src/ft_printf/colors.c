/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atyrode <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 11:13:59 by atyrode           #+#    #+#             */
/*   Updated: 2019/09/10 05:50:57 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	define_color(t_conv *conv)
{
	int i;

	i = conv->width;
	if (i == 1)
		ft_strcpy(conv->str, WHITE);
	else if (i == 2)
		ft_strcpy(conv->str, RED);
	else if (i == 3)
		ft_strcpy(conv->str, GREEN);
	else if (i == 4)
		ft_strcpy(conv->str, BLUE);
	else if (i == 5)
		ft_strcpy(conv->str, YELLOW);
	else if (i == 6)
		ft_strcpy(conv->str, MAGENTA);
	else if (i == 7)
		ft_strcpy(conv->str, CYAN);
	else
		ft_strcpy(conv->str, RESET);
	conv->len = ft_strlen(conv->str);
	return (0);
}

int			colors(t_conv *conv, t_buff *buff)
{
	int j;

	j = buff->flushed + buff->index;
	define_color(conv);
	buff_insert_str(buff, conv);
	return ((buff->flushed + buff->index) - j);
}

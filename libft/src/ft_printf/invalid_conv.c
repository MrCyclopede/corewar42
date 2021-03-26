/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   invalid_conv.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/07 07:23:52 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/10 05:51:54 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	padding(t_conv *conv, t_buff *buff)
{
	int i;

	i = conv->width - (conv->len + conv->acc);
	while (i-- > 0)
	{
		if (conv->zero)
			buff_insert_char(buff, '0');
		else
			buff_insert_char(buff, ' ');
	}
	return (0);
}

int			invalid_conv(t_conv *conv, t_buff *buff)
{
	conv->str[0] = '\0';
	padding(conv, buff);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c.c                                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/01 13:24:45 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/10 05:50:41 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	padding(t_conv *conv, t_buff *buff)
{
	int i;

	i = conv->width - conv->len;
	while (i-- > 0)
		if (conv->zero && !conv->minus)
			buff_insert_char(buff, '0');
		else
			buff_insert_char(buff, ' ');
	return (0);
}

static void	adapt_conv(t_conv *conv)
{
	conv->len = 1;
}

int			c(t_conv *conv, t_buff *buff)
{
	dispatch_cast(conv);
	adapt_conv(conv);
	if (!conv->minus)
		padding(conv, buff);
	buff_insert_char(buff, conv->str[0]);
	if (conv->minus)
		padding(conv, buff);
	return (0);
}

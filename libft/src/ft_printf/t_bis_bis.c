/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   t_bis.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 03:33:31 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/21 02:33:24 by atyrode          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	conversion_manager_bis(t_conv *conv, t_buff *buff, int y)
{
	if (conv->conv == HEX)
	{
		print_itoa_base(conv->str, y, 16, 1);
		x(conv, buff);
	}
	else if (conv->conv == MAJ_HEX)
	{
		print_itoa_base(conv->str, y, 16, 2);
		x(conv, buff);
	}
	else if (conv->conv == PTR)
	{
		print_itoa_base(conv->str, y, 16, 1);
		p(conv, buff);
	}
	return ;
}

void	conversion_manager(t_conv *conv, t_buff *buff, int y)
{
	if (conv->conv == BINARY)
	{
		print_itoa_base(conv->str, y, 2, 1);
		b(conv, buff);
	}
	else if (conv->conv == OCTAL)
	{
		print_itoa_base(conv->str, y, 8, 1);
		o(conv, buff);
	}
	else if (conv->conv == UNS_INT)
	{
		print_itoa_base(conv->str, y, 10, 1);
		u(conv, buff);
	}
	else
		conversion_manager_bis(conv, buff, y);
	return ;
}

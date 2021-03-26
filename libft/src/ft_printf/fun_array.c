/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fun_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/23 06:11:24 by rcourtoi          #+#    #+#             */
/*   Updated: 2019/09/13 06:38:09 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fill_f_array(t_farray *farray)
{
	farray[CHAR] = c;
	farray[STR] = s;
	farray[PTR] = p;
	farray[INT] = d;
	farray[ALSO_INT] = d;
	farray[OCTAL] = o;
	farray[UNS_INT] = u;
	farray[HEX] = x;
	farray[MAJ_HEX] = x;
	farray[FLOAT] = f;
	farray[PERCENT] = c;
	farray[CAP_FLOAT] = f;
	farray[BINARY] = b;
	farray[COLORS] = colors;
	farray[INV_CONV] = invalid_conv;
}

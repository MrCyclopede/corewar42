/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 08:04:23 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/12 08:41:06 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	long int	res;
	int			x;
	int			neg;

	res = 0;
	x = 0;
	neg = 1;
	while (ft_isspace(str[x]))
		x++;
	if (str[x] == '+' || str[x] == '-')
	{
		if (str[x] == '-')
			neg = -1;
		x++;
	}
	while (ft_isdigit(str[x]))
	{
		res = res * 10;
		res = res + (str[x] - '0');
		x++;
	}
	return (res * neg);
}

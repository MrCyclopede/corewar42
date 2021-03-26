/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 08:58:44 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/20 21:26:59 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	getlen(int n)
{
	long int	t;
	long int	x;
	int			c;

	x = n;
	t = 10;
	c = 1;
	if (n < 0)
	{
		x = -x;
		c++;
	}
	while (x >= t)
	{
		t *= 10;
		c++;
	}
	return (c);
}

char		*ft_itoa(int n)
{
	char		*dest;
	long int	nbr;
	int			x;
	int			temp;

	temp = (n < 0) ? 1 : 0;
	nbr = n;
	x = getlen(n);
	if (!(dest = ft_memalloc(x + 1)))
		return (NULL);
	dest[x--] = '\0';
	if (nbr < 0)
	{
		nbr = -nbr;
		dest[0] = '-';
	}
	while (x >= temp)
	{
		dest[x] = (nbr % 10) + '0';
		nbr = nbr / 10;
		x--;
	}
	return (dest);
}

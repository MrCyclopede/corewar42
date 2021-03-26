/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tabsort.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 15:10:19 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/21 18:29:59 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_tabsort(int **tab, size_t len)
{
	size_t	x;
	int		swap;
	int		temp;
	int		*tt;

	tt = *tab;
	swap = 1;
	while (swap)
	{
		swap = 0;
		x = 0;
		while (x < len - 1)
		{
			if (tt[x] > tt[x + 1])
			{
				temp = tt[x];
				tt[x] = tt[x + 1];
				tt[x + 1] = temp;
				swap = 1;
			}
			x++;
		}
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 18:00:23 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/20 13:18:51 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strrev(char **str)
{
	int		x;
	int		y;
	char	*temp;
	char	t;

	if (!str)
		return ;
	x = 0;
	y = ft_strlen(*str) - 1;
	if (!(temp = ft_strdup(*str)))
	{
		free(temp);
		return ;
	}
	while (x < y)
	{
		t = temp[x];
		temp[x] = temp[y];
		temp[y] = t;
		x++;
		y--;
	}
	*str = temp;
	free(temp);
}

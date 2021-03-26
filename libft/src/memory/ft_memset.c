/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/09 16:40:35 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/18 11:44:52 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memset(void *b, int c, size_t len)
{
	size_t			x;

	x = 0;
	while (x < len)
	{
		((unsigned char *)b)[x] = (unsigned char)c;
		x++;
	}
	return (b);
}

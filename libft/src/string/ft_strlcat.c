/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 09:45:25 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/17 04:27:22 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t l1;
	size_t l2;
	size_t x;

	x = 0;
	l1 = ft_strlen(dst);
	l2 = ft_strlen(src);
	if (l1 + 1 < size)
	{
		while (x < (size - l1 - 1) && src[x])
		{
			dst[l1 + x] = src[x];
			x++;
		}
		dst[l1 + x] = '\0';
	}
	return (l1 > size ? l2 + size : l1 + l2);
}

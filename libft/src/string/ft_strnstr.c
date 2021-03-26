/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:50:23 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/20 20:33:01 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	int x;
	int y;

	x = 0;
	if (needle[0] == '\0')
		return ((char *)haystack);
	while (haystack[x] && len)
	{
		y = 0;
		while (haystack[x + y] == needle[y] && len)
		{
			y++;
			if (needle[y] == '\0')
				return ((char *)&haystack[x]);
			len--;
		}
		len += y;
		x++;
		len--;
	}
	return (NULL);
}

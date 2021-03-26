/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:22:04 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/20 13:47:19 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	int x;
	int y;

	x = 0;
	if (needle[x] == '\0')
		return ((char *)haystack);
	while (haystack[x] != '\0')
	{
		y = 0;
		while (haystack[x + y] == needle[y])
		{
			y++;
			if (needle[y] == '\0')
				return ((char *)&haystack[x]);
		}
		x++;
	}
	return (0);
}

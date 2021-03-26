/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 11:18:17 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/17 04:53:00 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int x;

	x = ft_strlen(s);
	if (!s)
		return (NULL);
	if (c == '\0')
		return ((char *)&s[x]);
	while (x >= 0)
	{
		if (s[x] == c)
			return ((char *)&s[x]);
		x--;
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 14:08:53 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/20 23:46:36 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	int		x;
	int		y;
	char	*new;

	if (!s)
		return (NULL);
	x = 0;
	y = ft_strlen(s) - 1;
	while (s[x] == ' ' || s[x] == '\n' || s[x] == '\t')
	{
		x++;
		if (s[x] == '\0')
		{
			if (!(new = ft_strdup(&s[x])))
				return (NULL);
			return (new);
		}
	}
	while (s[y] == ' ' || s[y] == '\n' || s[y] == '\t')
		y--;
	if (!(new = ft_strnew(y - x + 2)))
		return (NULL);
	new = ft_memcpy(new, &s[x], y - x + 1);
	return (new);
}

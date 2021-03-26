/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 06:24:14 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/18 12:23:11 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmap(char const *s, char (*f)(char))
{
	int		x;
	char	*new;

	x = 0;
	if (!s || !f)
		return (NULL);
	if (!(new = ft_strdup(s)))
		return (NULL);
	while (s[x] != '\0')
	{
		new[x] = f(new[x]);
		x++;
	}
	return (new);
}

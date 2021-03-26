/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 06:29:50 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/20 20:19:40 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
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
		new[x] = f(x, new[x]);
		x++;
	}
	return (new);
}

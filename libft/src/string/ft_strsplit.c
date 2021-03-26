/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rcourtoi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 15:58:41 by rcourtoi          #+#    #+#             */
/*   Updated: 2018/11/21 14:49:15 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	wordlen(const char *s, char c)
{
	int x;

	x = 0;
	while (s[x] && s[x] != c)
		x++;
	return (x);
}

static int	ct(const char *s, char c)
{
	int x;
	int cpt;

	cpt = 0;
	x = 0;
	while (s[x] == c)
		x++;
	while (s[x])
	{
		while (s[x] != c && s[x])
			x++;
		while (s[x] == c)
			x++;
		cpt++;
	}
	return (cpt);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**tab;
	int		x;
	int		y;
	int		i;

	i = 0;
	x = 0;
	if (!s || !(tab = (char **)malloc(sizeof(char *) * (ct(s, c) + 1))))
		return (NULL);
	while (s[x])
	{
		if (s[x] != c)
		{
			y = 0;
			if (!(tab[i] = ft_strnew(wordlen(&s[x], c))))
				return (NULL);
			while (s[x] != c && s[x])
				tab[i][y++] = s[x++];
			tab[i++][y] = '\0';
		}
		if (s[x] != '\0')
			x++;
	}
	tab[i] = NULL;
	return (tab);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_test.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nakorchi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/25 18:39:11 by nakorchi          #+#    #+#             */
/*   Updated: 2019/12/15 00:44:44 by rcourtoi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# define BUFF_SIZE 1000000

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <limits.h>
# include <stdlib.h>

typedef struct		s_line
{
	int				fd;
	char			*ln;
	char			*ar;
	char			*tmp;
	struct s_line	*next;
}					t_line;

char				*ft_strretri(char *s, char c, int len);
char				*ft_strjoinfree(char **s1, char **s2, int o);
char				*ft_strjoin2(char *s1, char *s2);
int					get_next_line(int fd, char **line);
t_line				*ft_fresh_link(int fd, t_line **begin_list);
t_line				*ft_search_link(int fd, t_line **begin_list);
t_line				*ft_free_link(t_line **link, t_line **begin_list);
char				*ft_strretri(char *s, char c, int len);
int					gnl(t_line *link, char **line, char *buff);

#endif

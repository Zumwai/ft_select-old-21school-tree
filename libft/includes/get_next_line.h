/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aophion <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/27 15:15:13 by aophion           #+#    #+#             */
/*   Updated: 2019/11/28 14:18:32 by aophion          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# include <stdlib.h>
# include <unistd.h>
# include "./libft/libft.h"
# define BUFF_SIZE 800

typedef struct		s_glist
{
	struct s_glist	*prev;
	struct s_glist	*next;
	size_t			size;
	int				fd;
	int				fin;
	char			*temp;
}					t_glist;

int					get_next_line(const int fd, char **line);

#endif

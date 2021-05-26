/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:26:43 by nnamor            #+#    #+#             */
/*   Updated: 2021/04/30 21:03:44 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif	/*BUFFER_SIZE*/

typedef struct s_buf
{
	struct s_buf	*next;
	char			*arr;
	size_t			len;
	int				fd;
}	t_buf;

int	get_next_line(int fd, char **line);
#endif	/*GET_NEXT_LINE_BONUS_H*/

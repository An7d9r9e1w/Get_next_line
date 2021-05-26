/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:10:34 by nnamor            #+#    #+#             */
/*   Updated: 2021/05/01 14:09:10 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str);
void	free_line(char **line);
char	*cat(char *dst, const char *src, size_t len);
int		get_buf(t_buf **root, t_buf **buf, int fd);
void	delete_buf(t_buf **root, int fd);

static int	parse_linefeed(t_buf *buf, char **line)
{
	size_t	i;
	ssize_t	j;
	ssize_t	cnt;
	char	lf;

	i = 0;
	while (i < buf->len && buf->arr[i] != '\n')
		i++;
	lf = i != buf->len && buf->arr[i] == '\n';
	*line = cat(*line, buf->arr, i);
	if (!*line)
		return (-1);
	cnt = buf->len - i - 1;
	j = -1;
	while (++j < cnt)
		buf->arr[j] = buf->arr[++i];
	buf->len = j;
	return (lf);
}

int	get_next_line(int fd, char **line)
{
	static t_buf	*root = 0;
	t_buf			*buf;
	ssize_t			cnt;
	int				lf;

	if (!line || get_buf(&root, &buf, fd))
		return (-1);
	*line = 0;
	lf = 0;
	cnt = 1;
	while (!lf && cnt)
	{
		cnt = read(fd, buf->arr + buf->len, BUFFER_SIZE - buf->len);
		if (cnt < 0)
			break ;
		buf->len += cnt;
		lf = parse_linefeed(buf, line);
	}
	if (cnt < 0)
		lf = cnt;
	if (lf < 0 || (!buf->len && !cnt))
		delete_buf(&root, fd);
	if (lf < 0 && *line)
		free_line(line);
	return (lf);
}

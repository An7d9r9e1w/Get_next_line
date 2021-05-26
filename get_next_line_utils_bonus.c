/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nnamor <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/30 20:11:53 by nnamor            #+#    #+#             */
/*   Updated: 2021/05/08 19:11:40 by nnamor           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

void	free_line(char **line)
{
	free(*line);
	*line = 0;
}

char	*cat(char *dst, const char *src, size_t len)
{
	char	*str;
	size_t	dstlen;
	size_t	i;

	if (!len && dst)
		return (dst);
	if (dst)
		dstlen = ft_strlen(dst);
	else
		dstlen = 0;
	str = (char *)malloc(sizeof(char) * (dstlen + len + 1));
	if (!str)
	{
		i = -1;
		while (++i < dstlen)
			str[i] = dst[i];
		dstlen = 0;
		while (dstlen < len)
			str[i++] = src[dstlen++];
		str[i] = 0;
	}
	if (dst)
		free(dst);
	return (str);
}

int	get_buf(t_buf **root, t_buf **buf, int fd)
{
	t_buf	*tmp;

	*buf = *root;
	while (*buf && (*buf)->fd != fd && (*buf)->next)
		*buf = (*buf)->next;
	if (*buf && (*buf)->fd == fd)
		return (0);
	tmp = (t_buf *)malloc(sizeof(t_buf));
	if (!tmp)
		return (1);
	tmp->arr = (char *)malloc(sizeof(char) * BUFFER_SIZE);
	if (!tmp->arr)
	{
		free(tmp);
		return (1);
	}
	tmp->len = 0;
	tmp->fd = fd;
	tmp->next = 0;
	if (*buf)
		(*buf)->next = tmp;
	if (!*root)
		*root = tmp;
	*buf = tmp;
	return (0);
}

void	delete_buf(t_buf **root, int fd)
{
	t_buf	*cur;
	t_buf	*tmp;

	if ((*root)->fd == fd)
	{
		cur = (*root)->next;
		free((*root)->arr);
		free(*root);
		*root = cur;
		return ;
	}
	cur = *root;
	while (cur->next && cur->next->fd != fd)
		cur = cur->next;
	if (cur->next && cur->next->fd == fd)
	{
		tmp = cur->next->next;
		free(cur->next->arr);
		free(cur->next);
		cur->next = tmp;
	}
}

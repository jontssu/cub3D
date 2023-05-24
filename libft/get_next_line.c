/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 13:07:00 by jole              #+#    #+#             */
/*   Updated: 2023/05/19 10:16:25 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char			*str;
	static t_list2	list;

	if (BUFFER_SIZE <= 0)
		return (0);
	list.surplus = get_line(fd, &list);
	if (!list.surplus)
		return (0);
	if (!*list.surplus)
	{
		free(list.surplus);
		list.surplus = NULL;
		return (0);
	}
	list.len = strlen_newline(list.surplus);
	str = malloc((list.len + 2) * sizeof(char));
	if (!str)
		return (0);
	ft2_strlcpy(str, list.surplus, (list.len + 2));
	skip_line(&list);
	list.total_len -= list.i;
	if (!*list.surplus)
		list.total_len = 0;
	return (str);
}

char	*get_line(int fd, t_list2 *list)
{
	int		read_val;
	char	*buf;

	read_val = 1;
	while (!ft2_strchr(list->surplus, '\n') && read_val)
	{
		buf = malloc((BUFFER_SIZE) * sizeof(char));
		if (!buf)
			return (0);
		read_val = read(fd, buf, BUFFER_SIZE);
		if (read_val < 0)
		{
			free(buf);
			return (0);
		}
		list->surplus = ft2_strjoin(list, buf, read_val);
		list->total_len += read_val;
		list->beginning = list->surplus;
	}
	return (list->surplus);
}

int	strlen_newline(char	*str)
{
	int	len;

	len = 0;
	while (*str != '\n')
	{
		str++;
		len++;
		if (*str == '\0')
		{
			len--;
			break ;
		}
	}
	return (len);
}

void	skip_line(t_list2 *list)
{
	list->i = list->len + 1;
	list->surplus += list->i;
	if (*list->surplus == 0)
		list->i -= 1;
}

char	*ft2_strdup(const char *s1)
{
	char	*p;
	int		i;

	i = 0;
	p = malloc((ft2_strlen(s1) + 1) * sizeof(char));
	if (!p)
		return (0);
	while (*s1 != 0)
	{
		*p = *s1;
		p++;
		s1++;
		i++;
	}
	*p = '\0';
	return (p - i);
}

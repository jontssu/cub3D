/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   disconnect_check_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/16 06:00:19 by jole              #+#    #+#             */
/*   Updated: 2023/06/16 06:12:14 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	check_newlines(char **split, char *cmp, t_parser *elements, int i)
{
	int	newlines;
	int	map_len;

	newlines = 0;
	map_len = 0;
	map_len = ft_strlen(&cmp[i]);
	while (cmp[i + --map_len] == '\n')
		newlines++;
	while (cmp[i + newlines])
	{
		if (cmp[i] == '\n' && cmp[i + 1] == '\n')
			error_elements(elements, split, 3);
		i++;
	}
}

void	compare_string_and_split(char **split, char *cmp, t_parser *elements)
{
	int	len;
	int	i;

	i = 0;
	while (cmp[i])
	{
		len = 0;
		while (cmp[i] && cmp[i] != '\n')
		{
			len++;
			i++;
		}
		if (len > 4 && !ft_strncmp(&cmp[i - len], split[7], len))
			break ;
		i++;
	}
	i -= len - 1;
	check_newlines(split, &cmp[i], elements, i);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_elements.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:39:54 by jole              #+#    #+#             */
/*   Updated: 2023/06/02 17:18:38 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	check_config_file_name(char *file)
{
	int	len;

	len = ft_strlen(file);
	if (file[len - 1] == 'b' && file[len - 2] == 'u' && \
	file[len - 3] == 'c' && file[len - 4] == '.')
	{
		len = open(file, O_RDONLY);
		if (len != -1)
			return ;
	}
	error_invalid_input(2);
}

void	check_commas(t_parser *elements, char *str, char **split)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (str[i++] == ',')
			count++;
	}
	if (count != 2)
		error_elements(elements, split, 1);
}

void	check_color_characters(t_parser *elements, char **split, char **split2)
{
	int	i;
	int	j;

	i = 0;
	if (!split2[2])
		error_colors(elements, 3, split, split2);
	while (split2[i])
	{
		j = 0;
		while (split2[i][j])
		{
			if (split2[i][j] && !ft_isdigit(split2[i][j]))
				error_colors(elements, 2, split, split2);
			j++;
		}
		i++;
	}
}

void	check_path(t_parser *elements, char *path)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\nIncorrect path for elements\n", 2);
		if (elements->north)
			free(elements->north);
		if (elements->south)
			free(elements->south);
		if (elements->west)
			free(elements->west);
		if (elements->east)
			free(elements->east);
		if (elements->door_o)
			free(elements->door_o);
		if (elements->door_c)
			free(elements->door_c);
		exit(-1);
	}
}

void	check_elements(t_parser *elements)
{
	check_path(elements, elements->north);
	check_path(elements, elements->south);
	check_path(elements, elements->west);
	check_path(elements, elements->east);
	check_path(elements, elements->door_o);
	check_path(elements, elements->door_c);
}

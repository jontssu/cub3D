/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_elements_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:33:33 by leklund           #+#    #+#             */
/*   Updated: 2023/06/14 17:21:27 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	set_int_array(char *str, int *int_arr, t_parser *elements, char **split)
{
	char	**split2;

	check_commas(elements, str, split);
	split2 = ft_split(str, ',');
	check_color_characters(elements, split, split2);
	int_arr[0] = ft_atoi(split2[0]);
	if (int_arr[0] > 255 || int_arr[0] < 0)
		error_colors(elements, 1, split, split2);
	int_arr[1] = ft_atoi(split2[1]);
	if (int_arr[1] > 255 || int_arr[1] < 0)
		error_colors(elements, 1, split, split2);
	int_arr[2] = ft_atoi(split2[2]);
	if (int_arr[2] > 255 || int_arr[2] < 0 || split2[3])
		error_colors(elements, 1, split, split2);
	int_arr[3] = 1;
	free_double_pointer(split2);
}

void	if_not_element(t_parser *elements, char **split)
{
	if (!elements->north || !elements->south || !elements->west \
	|| !elements->east || !elements->door_o || !elements->door_c \
	|| elements->ceiling[3] == -1 || elements->floor[3] == -1)
		error_elements(elements, split, 2);
}

int	set_elements(char **split, t_parser *elements)
{
	int	i;

	i = -1;
	while (split[++i])
	{
		if (ft_strncmp(split[i], "NO./", 4) == 0)
			elements->north = ft_strdup(&split[i][4]);
		else if (ft_strncmp(split[i], "SO./", 4) == 0)
			elements->south = ft_strdup(&split[i][4]);
		else if (ft_strncmp(split[i], "WE./", 4) == 0)
			elements->west = ft_strdup(&split[i][4]);
		else if (ft_strncmp(split[i], "EA./", 4) == 0)
			elements->east = ft_strdup(&split[i][4]);
		else if (ft_strncmp(split[i], "D_O./", 4) == 0)
			elements->door_o = ft_strdup(&split[i][5]);
		else if (ft_strncmp(split[i], "D_C./", 4) == 0)
			elements->door_c = ft_strdup(&split[i][5]);
		else if (split[i][0] == 'F' && ft_isdigit(split[i][1]))
			set_int_array(&split[i][1], elements->floor, elements, split);
		else if (split[i][0] == 'C' && ft_isdigit(split[i][1]))
			set_int_array(&split[i][1], elements->ceiling, elements, split);
	}
	if_not_element(elements, split);
	return (0);
}

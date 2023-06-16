/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:40:35 by jole              #+#    #+#             */
/*   Updated: 2023/06/16 06:07:18 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing.h"

void	init_elements(t_parser *elements)
{
	elements->north = NULL;
	elements->south = NULL;
	elements->west = NULL;
	elements->east = NULL;
	elements->map = NULL;
	elements->ceiling[3] = -1;
	elements->floor[3] = -1;
}

void	read_file_to_content(char *file, char **content)
{
	char	*line;
	char	*tmp;
	int		fd;

	*content = ft_strdup("");
	fd = open(file, O_RDONLY);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		tmp = *content;
		*content = ft_strjoin(tmp, line);
		free(tmp);
		free(line);
		if (!content)
			error_malloc(*content);
	}
	close(fd);
}

char	*remove_spaces(char *string)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	while (string[i])
	{
		check = 0;
		if (string[i] == ' ')
		{
			j = i;
			while (string[j])
			{
				string[j] = string[j + 1];
				j++;
			}
			check = 1;
		}
		if (check == 0)
			i++;
	}
	return (string);
}

char	**remove_spaces_from_elements(char **split)
{
	int	i;

	i = -1;
	while (split[++i] && i < 6)
		split[i] = remove_spaces(split[i]);
	return (split);
}

int	parser(char *file, t_parser *elements)
{
	char	*content;
	char	**split;
	char	*compare;

	init_elements(elements);
	check_config_file_name(file);
	read_file_to_content(file, &content);
	read_file_to_content(file, &compare);
	split = ft_split(content, '\n');
	if (!split)
		error_malloc(content);
	free(content);
	split = remove_spaces_from_elements(split);
	set_elements(split, elements);
	check_elements(elements);
	get_map(&split[6], elements);
	compare_string_and_split(split, compare, elements);
	free(compare);
	free_double_pointer(split);
	if (elements->max_heigth < 3 || elements->max_width < 3)
		error_invalid_map(elements, 8);
	map_check(elements);
	return (0);
}

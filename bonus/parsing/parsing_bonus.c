/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jon <jon@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:33:39 by leklund           #+#    #+#             */
/*   Updated: 2023/06/16 04:53:34 by jon              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	init_elements(t_parser *elements)
{
	elements->north = NULL;
	elements->south = NULL;
	elements->west = NULL;
	elements->east = NULL;
	elements->door_o = NULL;
	elements->door_c = NULL;
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
	while (split[++i] && i < 7)
		split[i] = remove_spaces(split[i]);
	return (split);
}

void	compare_string_and_split(char **split, char *cmp, t_parser *elements)
{
	int		len;
	char	*tmp;

	tmp = cmp;
	while (cmp)
	{
		len = 0;
		while (*cmp && *cmp != '\n')
			len++;
		if (len > 4 && ft_strncmp(cmp, &split[7], len + 1))
			break ;
		cmp += len + 1;
	}
	cmp += len + 1;
	while (cmp + 1)
	{
		if (cmp[0] == '\n' && cmp[1] == '\n')
		{
			free(tmp);	
			error_elements(elements, split, 3);
		}
		cmp++;
	}
}

int	parser(char *file, t_parser *elements)
{
	char	*content;
	char	**split;
	// char	*compare;

	init_elements(elements);
	check_config_file_name(file);
	read_file_to_content(file, &content);
	// read_file_to_content(file, &compare);
	split = ft_split(content, '\n');
	if (!split)
		error_malloc(content);
	free(content);
	split = remove_spaces_from_elements(split);
	set_elements(split, elements);
	check_elements(elements);
	get_map(&split[7], elements);
	// compare_string_and_split(split, compare);
	free_double_pointer(split);
	if (elements->max_heigth < 3 || elements->max_width < 3)
		error_invalid_map(elements, 8);
	map_check(elements);
	return (0);
}

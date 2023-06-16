/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jole <jole@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/25 19:39:34 by jole              #+#    #+#             */
/*   Updated: 2023/06/16 06:05:45 by jole             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H
# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>

typedef struct s_parser
{
	char	*north;
	char	*south;
	char	*west;
	char	*east;
	char	*door_o;
	char	*door_c;
	int		floor[4];
	int		ceiling[4];
	char	**map;
	char	orientation;
	int		start_x;
	int		start_y;
	int		max_width;
	int		max_heigth;
}	t_parser;

//Parser
int		parser(char *file, t_parser *elements);
void	check_config_file_name(char *file);
int		set_elements(char **split, t_parser *elements);
int		get_map(char **split, t_parser *elements);
void	fill_with_x(int max_size, t_parser *elements);

//Elements check
void	check_elements(t_parser *elements);
void	check_commas(t_parser *elements, char *str, char **split);
void	check_color_characters(t_parser *elements, char **split, char **split2);
void	set_int_array(char *str, int *int_arr, \
t_parser *elements, char **split);
void	check_path(t_parser *elements, char *path);
void	check_elements(t_parser *elements);

//Map check
void	map_check(t_parser *elements);
void	valid_chars_check(t_parser *elements);
void	flood_fill(t_parser *elements, int y, int x);
void	compare_string_and_split(char **split, char *cmp, t_parser *elements);

//Error handling
void	error_invalid_input(int error);
void	error_malloc(char *content);
void	error_elements(t_parser *elements, char **split, int error);
void	error_colors(t_parser *elements, int err, char **split, char **split2);
void	error_invalid_map(t_parser *elements, int error);

//Helpers
void	free_double_pointer(char **array);
void	free_elements(t_parser *elements);
#endif
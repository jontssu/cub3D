/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jon <jon@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/04 06:32:52 by leklund           #+#    #+#             */
/*   Updated: 2023/06/16 04:49:32 by jon              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parsing_bonus.h"

void	error_invalid_input(int error)
{
	if (error == 1)
		ft_putstr_fd("Error\nIncorrect amount of arguments\n", 2);
	else if (error == 2)
		ft_putstr_fd("Error\nInvalid config file\n", 2);
	exit(-1);
}

void	error_malloc(char *content)
{
	ft_putstr_fd("Error\nMalloc error\n", 2);
	free(content);
	exit(-1);
}

void	error_elements(t_parser *elements, char **split, int error)
{
	if (error == 1)
		ft_putstr_fd("Error\nInvalid amount of colors\n", 2);
	else if (error == 2)
		ft_putstr_fd("Error\nIncorrect amount of elements\n", 2);
	else if (error == 3)
		ft_putstr_fd("Error\nNewline inside map\n", 2);
	if (elements->north)
		free(elements->north);
	if (elements->south)
		free(elements->south);
	if (elements->west)
		free(elements->west);
	if (elements->east)
		free(elements->east);
	if (elements->door_c)
		free(elements->door_c);
	free_double_pointer(split);
	exit(-1);
}

void	error_colors(t_parser *elements, int err, char **split, char **split2)
{
	if (err == 1)
		ft_putstr_fd("Error\nInvalid colors\n", 2);
	else if (err == 2)
		ft_putstr_fd("Error\nNon-numeric color setting\n", 2);
	else if (err == 3)
		ft_putstr_fd("Error\nMissing a color setting\n", 2);
	else if (err == 4)
		ft_putstr_fd("Error\nInvalid amount of colors\n", 2);
	if (elements->north)
		free(elements->north);
	if (elements->south)
		free(elements->south);
	if (elements->west)
		free(elements->west);
	if (elements->east)
		free(elements->east);
	if (elements->door_c)
		free(elements->door_c);
	free_double_pointer(split);
	free_double_pointer(split2);
	exit(-1);
}

void	error_invalid_map(t_parser *elements, int error)
{
	if (error == 1)
		ft_putstr_fd("Error\nToo many starting positions\n", 2);
	else if (error == 2)
		ft_putstr_fd("Error\nNo starting position\n", 2);
	else if (error == 3)
		ft_putstr_fd("Error\nInvalid character found in map\n", 2);
	else if (error == 4)
		ft_putstr_fd("Error\nMap was open\n", 2);
	else if (error == 5)
		ft_putstr_fd("Error\nPart of a map was not connected\n", 2);
	else if (error == 6)
		ft_putstr_fd("Error\nInvalid map component\n", 2);
	else if (error == 7)
		ft_putstr_fd("Error\nStarting position is invalid\n", 2);
	else if (error == 8)
		ft_putstr_fd("Error\nMap is not big enough\n", 2);
	free_elements(elements);
	exit(-1);
}

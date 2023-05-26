/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leklund <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/22 09:48:56 by leklund           #+#    #+#             */
/*   Updated: 2023/05/22 09:48:57 by leklund          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "cub3D.h"


void print_map(t_player *P)
{
	int y = 0;
	int x = 0;
	while(P->cpy_map[y])
	{
		x = 0;
		while(P->cpy_map[y][x])
		{
			if(y == P->playerY && x == P->playerX)
				printf("P");
			else
				printf("%c", P->cpy_map[y][x]);

			x++;
		}
		printf("\n");
		y++;
	}

}


char** copy2DCharArray(char** arr) {
	int rows = 0;
	int cols = 0;
	while(arr[0][cols])
		cols++;
	while(arr[rows])
		rows++;
    char** copy = (char**)malloc((rows +1) * sizeof(char*));
    if (copy == NULL) {
        fprintf(stderr, "Memory allocation failed.");
        exit(1);
    }

    for (int i = 0; i < rows; i++) {
        copy[i] = (char*)malloc((cols + 1) * sizeof(char));
        if (copy[i] == NULL) {
            fprintf(stderr, "Memory allocation failed.");
            exit(1);
        }
        strcpy(copy[i], arr[i]);
    }
	copy[rows] = NULL;

    return copy;
}
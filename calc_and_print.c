/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc_and_print.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 23:05:29 by ihodge            #+#    #+#             */
/*   Updated: 2017/11/02 18:50:20 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	calculate_closest(t_avail **tmp, int *distance, int *tmp_x_y,
		t_game *game)
{
	while (game->avail)
	{
		distance[0] = game->opponent_coord[1] - game->avail->x;
		distance[1] = game->opponent_coord[0] - game->avail->y;
		distance[0] < 0 ? distance[0] *= -1 : 0;
		distance[1] < 0 ? distance[1] *= -1 : 0;
		tmp_x_y[0] = game->opponent_coord[1] - (*tmp)->x;
		tmp_x_y[1] = game->opponent_coord[0] - (*tmp)->y;
		tmp_x_y[0] < 0 ? tmp_x_y[0] *= -1 : 0;
		tmp_x_y[1] < 0 ? tmp_x_y[1] *= -1 : 0;
		if (distance[0] < tmp_x_y[0] && distance[1] < tmp_x_y[1])
			(*tmp) = game->avail;
		else if ((distance[1] < tmp_x_y[1]) && distance[1] < tmp_x_y[0])
			(*tmp) = game->avail;
		else if ((distance[0] < tmp_x_y[0]) && distance[0] < tmp_x_y[1])
			(*tmp) = game->avail;
		game->avail = game->avail->next;
	}
}

void	print_coords(t_game *game, t_avail *avail, int *opponent_coord)
{
	t_avail	*tmp;
	int		*distance;
	int		*tmp_x_y;

	tmp = avail;
	distance = (int*)ft_memalloc(sizeof(int) * 2);
	tmp_x_y = (int*)ft_memalloc(sizeof(int) * 2);
	tmp_x_y[0] = opponent_coord[1] - avail->x;
	tmp_x_y[1] = opponent_coord[0] - avail->y;
	tmp_x_y[0] < 0 ? tmp_x_y[0] *= -1 : 0;
	tmp_x_y[1] < 0 ? tmp_x_y[1] *= -1 : 0;
	calculate_closest(&tmp, distance, tmp_x_y, game);
	free(game->avail);
	game->avail = NULL;
	ft_putnbr(tmp->y - game->first_star_y);
	ft_putchar(' ');
	ft_putnbr(tmp->x - game->first_star_x);
	ft_putchar('\n');
}

void	increment_quadrant(t_game *game, int **quadrants, int i, int j)
{
	if (i > game->board_rows / 4 && i < game->board_rows * 3 / 4)
		(*quadrants)[4]++;
	if (i < game->board_rows / 2 && j < game->board_cols / 2)
		(*quadrants)[0]++;
	else if (j < game->board_cols / 2)
		(*quadrants)[2]++;
	else if (i < game->board_rows / 2)
		(*quadrants)[1]++;
	else
		(*quadrants)[3]++;
}

void	assign_target_quadrant(t_game *game)
{
	int	*quadrants;
	int i;
	int j;

	quadrants = (int*)ft_memalloc(sizeof(int) * 5);
	i = 0;
	j = 0;
	while (game->board[i])
	{
		while (game->board[i][j])
		{
			if (game->board[i][j] == game->opponent)
				increment_quadrant(game, &quadrants, i, j);
			j++;
		}
		j = 0;
		i++;
	}
	assign_opponent_coord(game, quadrants);
}

void	assign_opponent_coord(t_game *game, int *quadrants)
{
	int	i;
	int highest_quad;
	int highest;

	i = -1;
	highest_quad = 0;
	highest = quadrants[0];
	while (++i < 5)
	{
		if (quadrants[i] >= highest)
		{
			highest = quadrants[i];
			highest_quad = i;
		}
	}
	highest_quad == 0 ? game->opponent_coord[0] = 0 : 0;
	highest_quad == 0 ? game->opponent_coord[1] = 0 : 0;
	highest_quad == 1 ? game->opponent_coord[0] = 0 : 0;
	highest_quad == 1 ? game->opponent_coord[1] = game->board_cols - 1 : 0;
	highest_quad == 2 ? game->opponent_coord[0] = game->board_rows - 1 : 0;
	highest_quad == 2 ? game->opponent_coord[1] = 0 : 0;
	highest_quad == 3 ? game->opponent_coord[0] = game->board_rows - 1 : 0;
	highest_quad == 3 ? game->opponent_coord[1] = game->board_cols - 1 : 0;
	highest_quad == 4 ? game->opponent_coord[0] = game->board_rows / 2 : 0;
	highest_quad == 4 ? game->opponent_coord[1] = game->board_cols / 2 : 0;
}

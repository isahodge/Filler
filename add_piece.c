/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_piece.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/25 23:05:29 by ihodge            #+#    #+#             */
/*   Updated: 2017/11/02 16:38:59 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		add_piece_to_board(t_game *game)
{
	int i;
	int j;
	int	ret;

	i = 0;
	j = 0;
	ret = 0;
	while (game->board[i])
	{
		while (game->board[i][j])
		{
			if (!(validate_star(game, i, j)))
			{
				save_avail_spots(&game->avail, i, j);
				ret++;
			}
			j++;
		}
		j = 0;
		i++;
	}
	assign_target_quadrant(game);
	if (ret)
		print_coords(game, game->avail, game->opponent_coord);
	return (ret);
}

void	save_avail_spots(t_avail **avail, int i, int j)
{
	t_avail *head;

	head = (*avail);
	if (head)
	{
		while (head->next)
			head = head->next;
		head->next = (t_avail*)ft_memalloc(sizeof(t_avail));
		head->next->x = j;
		head->next->y = i;
		head->next->next = NULL;
	}
	else
	{
		(*avail) = (t_avail*)ft_memalloc(sizeof(t_avail));
		(*avail)->x = j;
		(*avail)->y = i;
		(*avail)->next = NULL;
	}
}

int		validate_star(t_game *game, int i, int j)
{
	int star_num;
	int	overlap;

	star_num = -1;
	overlap = 0;
	while (++star_num < game->star_amount)
	{
		if (j + game->star_coords[star_num][1] < 0 || j +
				game->star_coords[star_num][1] > game->board_cols - 1)
			return (2);
		if (i + game->star_coords[star_num][0] < 0 || i +
				game->star_coords[star_num][0] > game->board_rows - 1)
			return (3);
		if (game->board[i + game->star_coords[star_num][0]][j +
				game->star_coords[star_num][1]] != '.' && game->board[i +
				game->star_coords[star_num][0]][j +
				game->star_coords[star_num][1]] != game->player)
			return (1);
		if (game->board[i + game->star_coords[star_num][0]][j +
				game->star_coords[star_num][1]] == game->player)
			overlap++;
	}
	if (overlap != 1)
		return (4);
	return (0);
}

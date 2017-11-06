/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:32:12 by ihodge            #+#    #+#             */
/*   Updated: 2017/10/31 19:28:05 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

int		number_of_stars(char **piece)
{
	int i;
	int j;
	int stars;

	i = 0;
	j = 0;
	stars = 0;
	while (piece[i])
	{
		while (piece[i][j])
		{
			if (piece[i][j] == '*')
				stars++;
			j++;
		}
		j = 0;
		i++;
	}
	return (stars);
}

int		**star_positions(char **piece, int stars)
{
	int i;
	int	j;
	int	piece_i;
	int	**star_coords;

	i = -1;
	j = 0;
	piece_i = 0;
	star_coords = (int**)ft_memalloc(sizeof(int*) * stars);
	while (piece[++i])
	{
		while (piece[i][j])
		{
			if (piece[i][j] == '*')
			{
				star_coords[piece_i] = (int*)ft_memalloc(sizeof(int) * 2);
				star_coords[piece_i][0] = i;
				star_coords[piece_i][1] = j;
				piece_i++;
			}
			j++;
		}
		j = 0;
	}
	return (star_coords);
}

void	first_star_is_origin(int **star_coords, t_game *game)
{
	int i;

	i = 1;
	while (i < game->star_amount)
	{
		star_coords[i][0] -= star_coords[0][0];
		star_coords[i][1] -= star_coords[0][1];
		i++;
	}
	game->first_star_y = star_coords[0][0];
	game->first_star_x = star_coords[0][1];
	star_coords[0][0] = 0;
	star_coords[0][1] = 0;
}

int		**parse_piece(char *line, t_game *game)
{
	char	**piece_dim;
	int		p_rows;
	int		p_cols;

	piece_dim = ft_strsplit(line, ' ');
	p_rows = ft_atoi(piece_dim[1]);
	p_cols = ft_atoi(piece_dim[2]);
	make_piece(&game->piece, line, p_rows, p_cols);
	game->star_amount = number_of_stars(game->piece);
	game->star_coords = star_positions(game->piece, game->star_amount);
	first_star_is_origin(game->star_coords, game);
	return (game->star_coords);
}

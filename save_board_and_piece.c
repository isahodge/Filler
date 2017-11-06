/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_board_and_piece.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:11:53 by ihodge            #+#    #+#             */
/*   Updated: 2017/11/02 18:41:05 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"

void	save_board(char **board, char *line)
{
	int i;
	int b_rows;
	int	b_cols;

	i = 0;
	get_next_line(0, &line);
	while (board[i])
	{
		get_next_line(0, &line);
		line += 4;
		ft_strcpy(board[i], line);
		i++;
	}
}

int		make_board(char ***board, char *line, t_game *game)
{
	int		i;
	char	**board_dim;

	i = 0;
	board_dim = ft_strsplit(line, ' ');
	game->board_rows = ft_atoi(board_dim[1]);
	game->board_cols = ft_atoi(board_dim[2]);
	if (!((*board) = (char**)ft_memalloc(sizeof(char*) *
					(game->board_rows + 1))))
		return (0);
	while (i < game->board_rows)
	{
		if (!((*board)[i] = (char*)ft_memalloc(game->board_cols + 1)))
			return (0);
		ft_memset((*board)[i], '.', game->board_cols);
		(*board)[i][game->board_cols] = '\0';
		i++;
	}
	return (-1);
}

void	save_piece(char **piece, char *line)
{
	int i;

	i = 0;
	while (piece[i])
	{
		get_next_line(0, &line);
		ft_strcpy(piece[i], line);
		i++;
	}
}

int		make_piece(char ***piece, char *line, int p_rows, int p_cols)
{
	int	i;

	i = 0;
	if (!((*piece) = (char**)ft_memalloc(sizeof(char*) * (p_rows + 1))))
		return (0);
	while (i < p_rows)
	{
		if (!((*piece)[i] = (char*)ft_memalloc(p_cols + 1)))
			return (0);
		ft_memset((*piece)[i], '.', p_cols);
		(*piece)[i][p_cols] = '\0';
		i++;
	}
	save_piece((*piece), line);
	return (-1);
}

t_game	*create_t_game(void)
{
	t_game	*new;

	if (!(new = (t_game*)ft_memalloc(sizeof(t_game))))
		return (NULL);
	new->star_amount = 0;
	new->piece = NULL;
	new->star_coords = NULL;
	new->board = NULL;
	new->board_rows = 0;
	new->board_cols = 0;
	new->player = 0;
	new->opponent = 0;
	new->first_star_x = 0;
	new->first_star_y = 0;
	new->opponent_coord = (int*)ft_memalloc(sizeof(int) * 2);
	new->avail = NULL;
	return (new);
}

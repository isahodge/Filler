/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:11:53 by ihodge            #+#    #+#             */
/*   Updated: 2017/11/04 18:42:49 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <ncurses.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int		main(int argc, char **argv)
{
	char	*line;
	t_game	*game;

	line = NULL;
	game = create_t_game();
	if (argv[1])
		init_ncurs(argv[1]);
	while (get_next_line(0, &line))
	{
		if (ft_strstr(line, "Piece"))
			parse_and_place_piece(line, game);
		else if (ft_strstr(line, "Plateau"))
			save_and_draw_board(line, game, argv[1]);
		else if (ft_strstr(line, "./filler"))
			set_player(line, game, 0);
	}
	endwin();
	free(game->board);
	return (0);
}

void	save_and_draw_board(char *line, t_game *game, char *argv1)
{
	if (game->board == NULL)
		make_board(&game->board, line, game);
	save_board(game->board, line);
	if (argv1)
		if (ft_strcmp(argv1, "-n") == 0)
			draw_board(game->board, game);
}

/*
** add_piece_to_board will return 0 when it  is no longer able to place a piece
*/

void	parse_and_place_piece(char *line, t_game *game)
{
	if (game->star_coords)
		free(game->star_coords);
	if (game->piece)
		free(game->piece);
	game->star_coords = parse_piece(line, game);
	if (add_piece_to_board(game) == 0)
	{
		endwin();
		ft_putstr("0 0\n");
	}
}

void	set_player(char *line, t_game *game, int player)
{
	player = ft_atoi(ft_strchr(line, 'p') + 1);
	if (player == 2)
	{
		game->player = 'X';
		game->opponent = 'O';
	}
	else
	{
		game->player = 'O';
		game->opponent = 'X';
	}
}

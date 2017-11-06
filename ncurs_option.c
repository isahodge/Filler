/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ncurs_option.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/10 20:11:53 by ihodge            #+#    #+#             */
/*   Updated: 2017/11/05 21:41:21 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "filler.h"
#include <ncurses.h>

void	init_ncurs(char *argv1)
{
	if (ft_strcmp(argv1, "-n") == 0)
	{
		newterm(NULL, stderr, stdin);
		start_color();
		noecho();
		curs_set(0);
	}
}

void	clear_and_init_colors(void)
{
	clear();
	init_pair(1, COLOR_BLACK, COLOR_BLACK);
	init_pair(2, 1, 1);
	init_pair(3, 4, 4);
}

void	draw_board(char **board, t_game *game)
{
	int	x_iter;
	int	y_iter;

	x_iter = 0;
	y_iter = 0;
	clear_and_init_colors();
	while (y_iter < game->board_rows)
	{
		while (x_iter < game->board_cols)
		{
			if (board[y_iter][x_iter] == '.')
				attron(COLOR_PAIR(1));
			else if (board[y_iter][x_iter] == 'X')
				attron(COLOR_PAIR(2));
			else if (board[y_iter][x_iter] == 'O')
				attron(COLOR_PAIR(3));
			printw("%2c", board[y_iter][x_iter]);
			x_iter++;
		}
		printw("\n");
		x_iter = 0;
		y_iter++;
	}
	refresh();
	usleep(10000);
}

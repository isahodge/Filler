/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filler.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ihodge <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/23 16:02:37 by ihodge            #+#    #+#             */
/*   Updated: 2017/11/02 18:53:13 by ihodge           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FILLER_H
# define FILLER_H
# include "libft/libft.h"

typedef struct		s_avail
{
	struct s_avail	*next;
	int				x;
	int				y;
}					t_avail;

typedef	struct		s_game
{
	int				**star_coords;
	int				star_amount;
	char			**piece;
	char			**board;
	int				board_rows;
	int				board_cols;
	int				player;
	int				opponent;
	int				first_star_x;
	int				first_star_y;
	int				*opponent_coord;
	t_avail			*avail;
}					t_game;

int					add_piece_to_board(t_game *game);
void				assign_opponent_coords(int **opponent_coord, int i, int j);
void				assign_opponent_coord(t_game *game, int *quadrants);
void				assign_target_quadrant(t_game *game);
void				calculate_closest(t_avail **tmp, int *distance,
		int *tmp_x_y, t_game *game);
void				clear_and_init_colors(void);
t_game				*create_t_game(void);
void				draw_board(char **board, t_game *game);
void				init_ncurs(char *argv1);
void				first_star_is_origin(int **inner_piece, t_game *game);
int					number_of_stars(char **piece);
int					make_board(char ***board, char *line, t_game *game);
int					make_piece(char ***piece, char *line, int p_rows,
		int p_cols);
void				save_and_draw_board(char *line, t_game *game, char *argv1);
void				save_avail_spots(t_avail **avail, int i, int j);
void				save_board(char **board, char *line);
void				save_piece(char **piece, char *line);
void				set_player(char *line, t_game *game, int player);
int					**star_positions(char **piece, int stars);
void				parse_and_place_piece(char *line, t_game *game);
int					**parse_piece(char *line, t_game *game);
void				print_coords(t_game *game, t_avail *avail,
		int *opponent_coord);
int					validate_star(t_game *game, int i, int j);
#endif

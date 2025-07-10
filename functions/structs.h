/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:51:24 by hakader           #+#    #+#             */
/*   Updated: 2025/07/10 21:33:11 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# define MOVE_SPEED 0.04
# define ROTATE_SPEED 0.02
# define FOV 90
# define MINI_SIZE 40
# define MINI_MAP_RADIUS 5


typedef struct s_game
{
	int		row;
	int		column;
	int		p_count;
	char	**map;
	char	**jungle;
}	t_game;

typedef struct s_color
{
	char	**f_colors;
	char	**c_colors;
	char	*f;
	int		f_red;
	int		f_green;
	int		f_blue;
	int		f_cnt;
	char	*c;
	int		c_red;
	int		c_green;
	int		c_blue;
	int		c_cnt;
}	t_color;

typedef struct s_textures
{
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		n;
	int		s;
	int		w;
	int		e;
}	t_textures;

typedef struct s_image
{
	void	*north;
	void	*south;
	void	*east;
	void	*west;
	void	*img;
}	t_image;

typedef struct s_axis
{
	double	p_x;
	double	p_y;
	double angle;
}	t_axis;

typedef struct s_keys
{
	int		w;
	int		d;
	int		s;
	int		a;
}	t_keys;

typedef struct s_player {
	double x;
	double y;
	int move_forward;
	int move_back;
	int move_left;
	int move_right;
}	t_player;

typedef struct s_cub
{
	t_game		game;
	t_axis		axis;
	t_keys		keys;
	t_color		clr;
	t_textures	textures;
	t_image		tx;
	t_player	player;
	void		*mlx;
	void		*win;
	int			column;
	int			row;
	void		*minimap_img;
	char		*minimap_data;
	int			line_len;
	int			endian;
	int			bpp;
}	t_cub;

#endif
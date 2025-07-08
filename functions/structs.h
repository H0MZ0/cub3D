/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:51:24 by hakader           #+#    #+#             */
/*   Updated: 2025/07/08 12:39:31 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

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
	int		p_x;
	int		p_y;
}	t_axis;

typedef struct s_keys
{
	int		w;
	int		d;
	int		s;
	int		a;
}	t_keys;

typedef struct s_cub
{
	t_game		game;
	t_axis		axis;
	t_keys		keys;
	t_color		clr;
	t_textures	textures;
	t_image		tx;
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
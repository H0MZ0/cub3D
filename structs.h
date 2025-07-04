/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:51:24 by hakader           #+#    #+#             */
/*   Updated: 2025/06/29 15:15:21 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef struct s_game
{
	int		row;
	int		column;
	char	**map;
	char	**jungle;
}	t_game;

typedef struct s_color
{
	char	**f_colors;
	char	**c_colors;
	char	*F;
	int		F_red;
	int		F_green;
	int		F_blue;
	int		f_cnt;
	char	*C;
	int		C_red;
	int		C_green;
	int		C_blue;
	int		c_cnt;
}	t_color;

typedef	struct s_textures
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	int		n;
	int		s;
	int		w;
	int		e;
}	t_textures;


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
	// int			column;
}	t_cub;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 13:51:24 by hakader           #+#    #+#             */
/*   Updated: 2025/06/27 13:55:42 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H


typedef struct s_game
{
	// int		p;
	// int		e;
	// int		c;
	// int		x;
	int		row;
	int		column;
	char	**map;
	char	**copy;
}	t_game;

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
	t_game	game;
	t_axis	axis;
	t_keys	keys;
	int		column;
}	t_cub;

#endif
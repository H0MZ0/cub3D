/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:48:19 by hakader           #+#    #+#             */
/*   Updated: 2025/07/07 23:30:56 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_sizes(t_cub *cub)
{
	int	temp;

	if (!cub->game.jungle)
		return ;
	temp = 0;
	while (cub->game.jungle[cub->row])
	{
		cub->column = ft_strlen(cub->game.jungle[cub->row]);
		if (cub->column > temp)
			temp = cub->column;
		cub->row++;
	}
	cub->column = temp;
}

void	find_player(t_cub *mlx)
{
	mlx->axis.p_y = 0;
	while (mlx->game.map[mlx->axis.p_y])
	{
		mlx->axis.p_x = 0;
		while (mlx->game.jungle[mlx->axis.p_y][mlx->axis.p_x])
		{
			if (!(mlx->game.jungle[mlx->axis.p_y][mlx->axis.p_x] == '0')
				&& is_walkable(mlx->game.jungle[mlx->axis.p_y][mlx->axis.p_x]))
				return ;
			mlx->axis.p_x++;
		}
		mlx->axis.p_y++;
	}
}

int	key_hook(int keyhook, t_cub *mlx)
{
	find_player(mlx);
	count_things(mlx, 0);
	if (keyhook == KEY_ESC || keyhook == ON_DESTROY)
		exit(1);
	return (0);
}

void	draw_minimap(t_cub *cub)
{
	int (x), (y), (dy), (dx), (color), (size);
	size = 15;

	y = 0;
	while (cub->game.jungle[y])
	{
		x = 0;
		while (cub->game.jungle[y][x])
		{
			if (cub->game.jungle[y][x] == '0')
				color = 0x00FF00;
			else if (cub->game.jungle[y][x] == '1')
				color = 0xFFFFFF;
			else if (is_walkable(cub->game.jungle[y][x]))
				color = 0xFF0000;
			else
			{
				x++;
				continue;
			}
			dy = 0;
			while (dy < size)
			{
				dx = 0;
				while (dx < size)
				{
					mlx_pixel_put(cub->mlx, cub->win, x * size + dx, y * size + dy, color);
					dx++;
				}
				dy++;
			}
			x++;
		}
		y++;
	}
}

void	in_mlx(t_cub *cub, t_list *alloc)
{
	get_sizes(cub);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (put_error("MLX initialization failed", alloc));
	cub->win = mlx_new_window(cub->mlx, cub->column * 100,
			cub->row * 100, "cub3D");
	if (!cub->win)
		return (put_error("WIN initialization failed", alloc));
	find_player(cub);
	draw_minimap(cub);
	mlx_key_hook(cub->win, key_hook, cub);
	mlx_loop(cub->mlx);
}

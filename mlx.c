/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:48:19 by hakader           #+#    #+#             */
/*   Updated: 2025/07/17 11:35:47 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_sizes(t_cub *cub)
{
	int	temp;

	if (!cub->game.jungle)
		return ;
	temp = 0;
	cub->row = 0;
	while (cub->game.jungle[cub->row])
	{
		int len = ft_strlen(cub->game.jungle[cub->row]);
		if (len > temp)
			temp = len;
		cub->row++;
	}
	cub->column = temp;
}

void find_player(t_cub *mlx)
{
	mlx->axis.p_y = 0;
	while (mlx->game.jungle[(int)mlx->axis.p_y])
	{
		mlx->axis.p_x = 0;
		while (mlx->game.jungle[(int)mlx->axis.p_y][(int)mlx->axis.p_x])
		{
			if (is_walkable(mlx->game.jungle[(int)mlx->axis.p_y][(int)mlx->axis.p_x]))
			{
				mlx->game.jungle[(int)mlx->axis.p_y][(int)mlx->axis.p_x] = '0';
				return ;
			}
			mlx->axis.p_x++;
		}
		mlx->axis.p_y++;
	}
}

int	key_press(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		exit (1);
	if (keycode == KEY_W)
		cub->player.move_forward = 1;
	if (keycode == KEY_S)
		cub->player.move_back = 1;
	if (keycode == KEY_A)
		cub->player.move_left = 1;
	if (keycode == KEY_D)
		cub->player.move_right = 1;
	if (keycode == KEY_RIGHT)
		cub->player.rotate_right = 1;
	if (keycode == KEY_LEFT)
		cub->player.rotate_left = 1;
	return (0);
}

int	key_release(int keycode, t_cub *cub)
{
	if (keycode == ESC)
		exit (1);
	if (keycode == KEY_W)
		cub->player.move_forward = 0;
	if (keycode == KEY_S)
		cub->player.move_back = 0;
	if (keycode == KEY_A)
		cub->player.move_left = 0;
	if (keycode == KEY_D)
		cub->player.move_right = 0;
	if (keycode == KEY_RIGHT)
		cub->player.rotate_right = 0;
	if (keycode == KEY_LEFT)
		cub->player.rotate_left = 0;
	return (0);
}

int	game_loop(t_cub *cub)
{
	double dir_x = cos(cub->axis.angle);
	double dir_y = sin(cub->axis.angle);
	double new_x = cub->axis.p_x;
	double new_y = cub->axis.p_y;

	if (cub->player.move_forward)
	{
		new_x += dir_x * MOVE_SPEED;
		new_y += dir_y * MOVE_SPEED;
	}
	if (cub->player.move_back)
	{
		new_x -= dir_x * MOVE_SPEED;
		new_y -= dir_y * MOVE_SPEED;
	}
	if (cub->player.move_right)
	{
		new_x -= dir_y * MOVE_SPEED;
		new_y += dir_x * MOVE_SPEED;
	}
	if (cub->player.move_left)
	{
		new_x += dir_y * MOVE_SPEED;
		new_y -= dir_x * MOVE_SPEED;
	}
	if (cub->player.rotate_left)
		cub->axis.angle -= ROTATE_SPEED;
	if (cub->player.rotate_right)
		cub->axis.angle += ROTATE_SPEED;
	// Normalize angle to [0, 2π]
	// if (cub->axis.angle < 0)
	// 	cub->axis.angle += 2 * M_PI;
	// else if (cub->axis.angle > 2 * M_PI)
	// 	cub->axis.angle -= 2 * M_PI;

	// Wall collision check
	if (cub->game.jungle[(int)new_y][(int)(cub->axis.p_x)] == '0')
		cub->axis.p_y = new_y;
	if (cub->game.jungle[(int)(cub->axis.p_y)][(int)new_x] == '0')
		cub->axis.p_x = new_x;

	draw_minimap(cub);
	return (0);
}

void	in_mlx(t_cub *cub, t_list *alloc)
{
	get_sizes(cub);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (put_error("MLX initialization failed", alloc));
	mlx_get_screen_size(cub->mlx, &cub->height, &cub->width);
	cub->win = mlx_new_window(cub->mlx, cub->height,
			cub->width, "cub3D");
	if (!cub->win)
		return (put_error("WIN initialization failed", alloc));
	mlx_hook(cub->win, 2, 1L<<0, key_press, cub);
	mlx_hook(cub->win, 3, 1L<<1, key_release, cub);
	find_player(cub);
	mlx_loop_hook(cub->mlx, game_loop, cub);
	mlx_loop(cub->mlx);
}

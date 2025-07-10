/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:48:19 by hakader           #+#    #+#             */
/*   Updated: 2025/07/10 19:37:20 by hakader          ###   ########.fr       */
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

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	dst = cub->minimap_data + (y * cub->line_len + x * (cub->bpp / 8));
	*(unsigned int *)dst = color;
}

void	draw_direction_line(t_cub *cub)
{
	int length = 20;
	int i = 0;
	double dx = cos(cub->axis.angle);
	double dy = sin(cub->axis.angle);
	double x = cub->axis.p_x * MINI_SIZE;
	double y = cub->axis.p_y * MINI_SIZE;

	while (i < length)
	{
		put_pixel(cub, (int)(x + dx * i), (int)(y + dy * i), 0x00FFFF);
		i++;
	}
}

void	draw_minimap(t_cub *cub)
{
	int x, y, dx, dy, color;

	if (cub->minimap_img)
		mlx_destroy_image(cub->mlx, cub->minimap_img);

	cub->minimap_img = mlx_new_image(cub->mlx, cub->column * MINI_SIZE, cub->row * MINI_SIZE);
	cub->minimap_data = mlx_get_data_addr(cub->minimap_img,
		&cub->bpp, &cub->line_len, &cub->endian);
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
			while (dy < MINI_SIZE)
			{
				dx = 0;
				while (dx < MINI_SIZE)
				{
					put_pixel(cub, x * MINI_SIZE + dx, y * MINI_SIZE + dy, color);
					dx++;
				}
				dy++;
			}
			x++;
		}
		y++;
	}
	int px = cub->axis.p_x * MINI_SIZE;
	int py = cub->axis.p_y * MINI_SIZE;
	for (dy = -2; dy <= 2; dy++)
		for (dx = -2; dx <= 2; dx++)
			put_pixel(cub, px + dx, py + dy, 0xFF0000);
	draw_direction_line(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap_img, 0, 0);
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
	if (cub->player.move_left)
		cub->axis.angle -= ROTATE_SPEED;
	if (cub->player.move_right)
		cub->axis.angle += ROTATE_SPEED;

	// Normalize angle to [0, 2π]
	if (cub->axis.angle < 0)
		cub->axis.angle += 2 * M_PI;
	else if (cub->axis.angle > 2 * M_PI)
		cub->axis.angle -= 2 * M_PI;

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
	cub->win = mlx_new_window(cub->mlx, cub->column * 100,
			cub->row * 100, "cub3D");
	if (!cub->win)
		return (put_error("WIN initialization failed", alloc));
	mlx_hook(cub->win, 2, 1L<<0, key_press, cub);
	mlx_hook(cub->win, 3, 1L<<1, key_release, cub);
	find_player(cub);
	draw_minimap(cub);
	mlx_loop_hook(cub->mlx, game_loop, cub);
	mlx_loop(cub->mlx);
}

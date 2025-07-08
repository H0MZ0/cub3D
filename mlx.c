/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:48:19 by hakader           #+#    #+#             */
/*   Updated: 2025/07/08 20:30:07 by hakader          ###   ########.fr       */
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

void	find_player(t_cub *mlx)
{
	mlx->axis.p_y = 0;
	while (mlx->game.jungle[mlx->axis.p_y])
	{
		mlx->axis.p_x = 0;
		while (mlx->game.jungle[mlx->axis.p_y][mlx->axis.p_x])
		{
			if (is_walkable(mlx->game.jungle[mlx->axis.p_y][mlx->axis.p_x]))
				return ;
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

void	draw_minimap(t_cub *cub)
{
	int x, y, dx, dy, color;
	int size = 15;

	if (cub->minimap_img)
		mlx_destroy_image(cub->mlx, cub->minimap_img);

	cub->minimap_img = mlx_new_image(cub->mlx, cub->column * size, cub->row * size);
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
			while (dy < size)
			{
				dx = 0;
				while (dx < size)
				{
					put_pixel(cub, x * size + dx, y * size + dy, color);
					dx++;
				}
				dy++;
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap_img, 0, 0);
}

int key_hook(int keyhook, t_cub *mlx)
{
	int new_x = mlx->axis.p_x;
	int new_y = mlx->axis.p_y;

	if (keyhook == KEY_W)
		new_y -= 1;
	else if (keyhook == KEY_S)
		new_y += 1;
	else if (keyhook == KEY_A)
		new_x -= 1;
	else if (keyhook == KEY_D)
		new_x += 1;
	else if (keyhook == KEY_ESC || keyhook == ON_DESTROY)
		exit(0);
	else
		return (0);

	if (new_y < 0 || new_y >= mlx->row)
		return (0);
	if (new_x < 0 || new_x >= (int)ft_strlen(mlx->game.jungle[new_y]))
		return (0);

	if (mlx->game.jungle[new_y][new_x] == '0')
	{
		mlx->game.jungle[mlx->axis.p_y][mlx->axis.p_x] = '0';
		mlx->game.jungle[new_y][new_x] = 'E';
		mlx->axis.p_x = new_x;
		mlx->axis.p_y = new_y;

		draw_minimap(mlx);
	}
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
	find_player(cub);
	draw_minimap(cub);
	mlx_key_hook(cub->win, key_hook, cub);
	mlx_loop(cub->mlx);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:03:17 by hakader           #+#    #+#             */
/*   Updated: 2025/07/15 17:04:13 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_pixel(t_cub *cub, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || y < 0 || x >= cub->column * MINI_SIZE || y >= cub->row * MINI_SIZE)
		return;
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
		put_pixel(cub, (int)(x + dx * i), (int)(y + dy * i), 0x212f3c);
		i++;
	}
}

void	draw_player(t_cub *cub)
{
	int (px), (py), (dx), (dy);
	px = cub->axis.p_x * MINI_SIZE;
	py = cub->axis.p_y * MINI_SIZE;
	dx = -3;
	dy = -3;
	while (dy <= 3)
	{
		dx = -3;
		while (dx <= 3)
		{
			put_pixel(cub, px + dx, py + dy, 0xFF0000);
			dx++;
		}
		dy++;
	}
}

int	get_color(t_cub *cub, t_var *var)
{
	if (cub->game.jungle[var->y][var->x] == '0')
				var->color = 0x00FF00;
	else if (cub->game.jungle[var->y][var->x] == '1')
		var->color = 0xFFFFFF;
	else if (is_walkable(cub->game.jungle[var->y][var->x]))
		var->color = 0xFF0000;
	else
	{
		var->x += 1;
		return (1);
	}
	return (0);
}

void	draw_minimap(t_cub *cub)
{
	t_var var;

	ft_bzero(&var, sizeof(t_var));
	if (cub->minimap_img)
		mlx_destroy_image(cub->mlx, cub->minimap_img);
	cub->minimap_img = mlx_new_image(cub->mlx, cub->column * MINI_SIZE, cub->row * MINI_SIZE);
	cub->minimap_data = mlx_get_data_addr(cub->minimap_img,
		&cub->bpp, &cub->line_len, &cub->endian);
	var.y = -1;
	while (cub->game.jungle[++var.y])
	{
		var.x = -1;
		while (cub->game.jungle[var.y][++var.x])
		{
			if (get_color(cub, &var))
				continue ;
			var.dy = -1;
			while (var.dy++ < MINI_SIZE)
			{
				var.dx = -1;
				while (var.dx++ < MINI_SIZE)
					put_pixel(cub, var.x * MINI_SIZE + var.dx, var.y * MINI_SIZE + var.dy, var.color);
			}
		}
	}
	draw_player(cub);
	draw_direction_line(cub);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap_img, 0, 0);
}

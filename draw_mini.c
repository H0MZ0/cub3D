/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_mini.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:03:17 by hakader           #+#    #+#             */
/*   Updated: 2025/07/18 11:48:23 by hakader          ###   ########.fr       */
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

void	mini_init(t_cub *cub, t_var *var)
{
	var->minimap_size = MINI_SIZE * MINIMAP_VIEW;
	var->start_x = (int)cub->axis.p_x - MINIMAP_VIEW / 2;
	var->start_y = (int)cub->axis.p_y - MINIMAP_VIEW / 2;
	if (cub->minimap_img)
		mlx_destroy_image(cub->mlx, cub->minimap_img);
	cub->minimap_img = mlx_new_image(cub->mlx, var->minimap_size, var->minimap_size);
	cub->minimap_data = mlx_get_data_addr(cub->minimap_img,
		&cub->bpp, &cub->line_len, &cub->endian);
}

void	draw_player(t_cub *cub, t_var *var)
{
	var->px = (cub->axis.p_x - var->start_x) * MINI_SIZE;
	var->py = (cub->axis.p_y - var->start_y) * MINI_SIZE;
	int dy = -3;
	while (dy <= 3)
	{
		int dx = -3;
		while (dx <= 3)
		{
			put_pixel(cub, (int)(var->px + dx), (int)(var->py + dy), 0xFF0000);
			dx++;
		}
		dy++;
	}
}

void	draw_line(t_cub *cub, t_var *var)
{
	int (length), (i);
	double (dx), (dy);
	length = 20;
	dx = cos(cub->axis.angle);
	dy = sin(cub->axis.angle);
	i = 0;
	while (i < length)
	{
		put_pixel(cub, (int)(var->px + dx * i), (int)(var->py + dy * i), 0x212f3c);
		i++;
	}
}

void	get_color(t_cub *cub, t_var *var)
{
	var->map_x = var->start_x + var->x;
	var->map_y = var->start_y + var->y;
	if (var->map_x >= 0 && var->map_x < cub->column && var->map_y >= 0 && var->map_y < cub->row)
	{
		if (cub->game.jungle[var->map_y][var->map_x] == '1')
			var->color = 0xFFFFFF;
		else if (cub->game.jungle[var->map_y][var->map_x] == '0')
			var->color = 0x00FF00;
		else
			var->color = 0xAAAAAA;
	}
	else
		var->color = 0x222222;
	
}

void	draw_minimap(t_cub *cub)
{
	t_var	var;

	ft_bzero(&var, sizeof(t_var));
	mini_init(cub, &var);
	var.y = -1;
	while (++var.y < MINIMAP_VIEW)
	{
		var.x = -1;
		while (++var.x < MINIMAP_VIEW)
		{
			get_color(cub, &var);
			var.dy = -1;
			while (++var.dy < MINI_SIZE)
			{
				var.dx = -1;
				while (++var.dx < MINI_SIZE)
					put_pixel(cub, var.x * MINI_SIZE + var.dx, var.y * MINI_SIZE + var.dy, var.color);
			}
		}
	}
	draw_player(cub, &var);
	draw_line(cub, &var);
	mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap_img, 0, 0);
}

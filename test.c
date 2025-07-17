/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 16:03:17 by hakader           #+#    #+#             */
/*   Updated: 2025/07/17 20:41:35 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	put_pixel(t_cub *cub, int x, int y, int color)
{
    char	*dst;

    if (x < 0 || y < 0
        || x >= MINI_SIZE * MINIMAP_VIEW
        || y >= MINI_SIZE * MINIMAP_VIEW)
        return ;
    dst = cub->minimap_data + (y * cub->line_len + x * (cub->bpp / 8));
    *(unsigned int *)dst = color;
}

int	get_tile_color(t_cub *cub, int map_x, int map_y)
{
    if (map_x < 0 || map_y < 0
        || map_x >= cub->column || map_y >= cub->row)
        return (0x222222);
    if (cub->game.jungle[map_y][map_x] == '1')
        return (0xFFFFFF);
    else if (cub->game.jungle[map_y][map_x] == '0')
        return (0x00FF00);
    else
        return (0xAAAAAA);
}

void	init_minimap_img(t_cub *cub, int minimap_size)
{
    if (cub->minimap_img)
        mlx_destroy_image(cub->mlx, cub->minimap_img);
    cub->minimap_img = mlx_new_image(cub->mlx, minimap_size, minimap_size);
    cub->minimap_data = mlx_get_data_addr(cub->minimap_img,
            &cub->bpp, &cub->line_len, &cub->endian);
}

void	draw_minimap(t_cub *cub)
{
    t_var	var;
    int		minimap_size;
    int		start_x;
    int		start_y;
    int		map_x;
    int		map_y;
    int		color;

    minimap_size = MINI_SIZE * MINIMAP_VIEW;
    start_x = (int)cub->axis.p_x - MINIMAP_VIEW / 2;
    start_y = (int)cub->axis.p_y - MINIMAP_VIEW / 2;
    init_minimap_img(cub, minimap_size);
    var.y = 0;
    while (var.y < MINIMAP_VIEW)
    {
        var.x = 0;
        while (var.x < MINIMAP_VIEW)
        {
            map_x = start_x + var.x;
            map_y = start_y + var.y;
            color = get_tile_color(cub, map_x, map_y);
            var.dy = 0;
            while (var.dy < MINI_SIZE)
            {
                var.dx = 0;
                while (var.dx < MINI_SIZE)
                {
                    put_pixel(cub, var.x * MINI_SIZE + var.dx,
                        var.y * MINI_SIZE + var.dy, color);
                    var.dx++;
                }
                var.dy++;
            }
            var.x++;
        }
        var.y++;
    }
}

void	draw_player_on_minimap(t_cub *cub)
{
    double	px;
    double	py;
    int		dx;
    int		dy;
    int		start_x;
    int		start_y;

    start_x = (int)cub->axis.p_x - MINIMAP_VIEW / 2;
    start_y = (int)cub->axis.p_y - MINIMAP_VIEW / 2;
    px = (cub->axis.p_x - start_x) * MINI_SIZE;
    py = (cub->axis.p_y - start_y) * MINI_SIZE;
    dy = -3;
    while (dy <= 3)
    {
        dx = -3;
        while (dx <= 3)
        {
            put_pixel(cub, (int)(px + dx), (int)(py + dy), 0xFF0000);
            dx++;
        }
        dy++;
    }
}

void	draw_direction_on_minimap(t_cub *cub)
{
    double	px;
    double	py;
    double	dx;
    double	dy;
    int		i;
    int		start_x;
    int		start_y;

    start_x = (int)cub->axis.p_x - MINIMAP_VIEW / 2;
    start_y = (int)cub->axis.p_y - MINIMAP_VIEW / 2;
    px = (cub->axis.p_x - start_x) * MINI_SIZE;
    py = (cub->axis.p_y - start_y) * MINI_SIZE;
    dx = cos(cub->axis.angle);
    dy = sin(cub->axis.angle);
    i = 0;
    while (i < 20)
    {
        put_pixel(cub, (int)(px + dx * i), (int)(py + dy * i), 0x212f3c);
        i++;
    }
}

void	render_minimap(t_cub *cub)
{
    draw_minimap(cub);
    draw_player_on_minimap(cub);
    draw_direction_on_minimap(cub);
    mlx_put_image_to_window(cub->mlx, cub->win, cub->minimap_img, 0, 0);
}

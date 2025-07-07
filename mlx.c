/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 17:48:19 by hakader           #+#    #+#             */
/*   Updated: 2025/07/07 23:10:32 by hakader          ###   ########.fr       */
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


// void	init_wind(t_cub *cub, t_list *alloc)
// {
// 	cub->tx.north = mlx_xpm_file_to_image(cub->mlx,
// 			"texture/mandatory/wall.xpm",
// 			&cub->column, &cub->row);
// 	cub->tx.south = mlx_xpm_file_to_image(cub->mlx,
// 			"texture/mandatory/floor.xpm",
// 			&cub->column, &cub->row);
// 	cub->tx.east = mlx_xpm_file_to_image(cub->mlx,
// 			"texture/mandatory/player.xpm",
// 			&cub->column, &cub->row);
// 	cub->tx.west = mlx_xpm_file_to_image(cub->mlx,
// 			"texture/mandatory/player.xpm",
// 			&cub->column, &cub->row);
// 	if (!cub->tx.north || !cub->tx.south
// 		|| !cub->tx.east || !cub->tx.west)
// 	{
// 		put_error("xpm file Error", alloc);
// 		// close_window(mlx);
// 	}
// }

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

// void	rendre_map(t_cub *mlx)
// {
// 	t_axis	ax;

// 	ax.p_y = 0;
// 	while (mlx->game.map[ax.p_y])
// 	{
// 		ax.p_x = 0;
// 		while (mlx->game.map[ax.p_y][ax.p_x] && ax.p_x < mlx->game.column)
// 		{
// 			if (mlx->game.map[ax.p_y][ax.p_x] == '1')
// 				mlx->tx.img = mlx->tx.north;
// 			else if (mlx->game.map[ax.p_y][ax.p_x] == '0')
// 				mlx->tx.img = mlx->tx.south;
// 			else if (mlx->game.map[ax.p_y][ax.p_x] == 'P')
// 				mlx->tx.img = mlx->tx.east;
// 			else if (mlx->game.map[ax.p_y][ax.p_x] == 'E')
// 				mlx->tx.img = mlx->tx.west;
// 			mlx_put_image_to_window(mlx->mlx, mlx->win,
// 				mlx->tx.img, ax.p_x * 80, ax.p_y * 80);
// 			ax.p_x++;
// 		}
// 		ax.p_y++;
// 	}
// }

int	key_hook(int keyhook, t_cub *mlx)
{
	find_player(mlx);
	count_things(mlx, 0);
	if (keyhook == KEY_ESC || keyhook == ON_DESTROY)
		exit(1);
		// close_window(mlx);
	// if (keyhook == KEY_W || keyhook == KEY_UP)
	// 	move_player(mlx, mlx->p_x, mlx->p_y - 1);
	// else if (keyhook == KEY_S || keyhook == KEY_DOWN)
	// 	move_player(mlx, mlx->p_x, mlx->p_y + 1);
	// else if (keyhook == KEY_A || keyhook == KEY_LEFT)
	// 	move_player(mlx, mlx->p_x - 1, mlx->p_y);
	// else if (keyhook == KEY_D || keyhook == KEY_RIGHT)
	// 	move_player(mlx, mlx->p_x + 1, mlx->p_y);
	// rendre_map(mlx);
	return (0);
}

void	in_mlx(t_cub *cub, t_list *alloc)
{
	get_sizes(cub);
	// printf_jungle(cub);
	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (put_error("MLX initialization failed", alloc));
	cub->win = mlx_new_window(cub->mlx, cub->column * 80,
			cub->row * 80, "so_long");
	if (!cub->win)
		return (put_error("WIN initialization failed", alloc));
	// init_wind(cub, alloc);
	find_player(cub);
	mlx_pixel_put(cub->mlx, cub->win, cub->column * 80,
			cub->row * 80, 0xFAFA);
	// rendre_map(mlx);
	mlx_key_hook(cub->win, key_hook, cub);
	mlx_loop(cub->mlx);
}
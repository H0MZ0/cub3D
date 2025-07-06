/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:40:51 by hakader           #+#    #+#             */
/*   Updated: 2025/07/06 20:09:34 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_valid_chars(t_cub *cub, t_list *alloc)
{
	char	**map;

	int (i), (j);
	map = cub->game.jungle;
	i = 0;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N' || map[i][j] == 'S'
				|| map[i][j] == 'W' || map[i][j] == 'E')
				cub->game.p_count++;
			if (!(is_valid_char(map[i][j])) && !is_whitespace(map[i][j]))
				put_error("invalid char in map!", alloc);
			j++;
		}
		i++;
	}
	if (cub->game.p_count != 1)
		put_error("check your player!", alloc);
}

static void	check_top_bottom(char **map, int row, t_list *alloc)
{
	int	x;

	x = 0;
	while (map[row][x])
	{
		if (!is_wall(map[row][x]) && !is_whitespace(map[row][x]))
			put_error("Map is NOT surrounded by walls!", alloc);
		x++;
	}
}

static void	check_sides(char **map, t_list *alloc)
{
	int (x), (y), (last), (row_len);
	y = 0;
	while (map[y])
	{
		row_len = ft_strlen(map[y]);
		x = 0;
		while (map[y][x] && is_whitespace(map[y][x]))
			x++;
		if (!is_wall(map[y][x]))
			put_error("Map is NOT surrounded by walls!", alloc);
		last = row_len - 1;
		while (last >= 0 && is_whitespace(map[y][last]))
			last--;
		if (!is_wall(map[y][last]))
			put_error("Map is NOT surrounded by walls!", alloc);
		y++;
	}
}

static void	check_walkable_cells(char **map, t_list *alloc)
{
	int (y), (x), (row_len);
	y = 0;
	while (map[y])
	{
		row_len = ft_strlen(map[y]);
		x = 0;
		while (x < row_len)
		{
			if (is_walkable(map[y][x]))
			{
				if ((y == 0 || x >= (int)ft_strlen(map[y - 1])
						|| is_whitespace(map[y - 1][x]))
					|| (map[y + 1] == NULL || x >= (int)ft_strlen(map[y + 1])
					|| is_whitespace(map[y + 1][x]))
					|| (x == 0 || is_whitespace(map[y][x - 1]))
					|| (x + 1 >= row_len || is_whitespace(map[y][x + 1])))
					put_error("Map is NOT surrounded by walls!", alloc);
			}
			x++;
		}
		y++;
	}
}

void	check_walls(char **map, t_list *alloc)
{
	int	lines;

	lines = 0;
	if (!map)
		return ;
	while (map[lines])
		lines++;
	check_top_bottom(map, 0, alloc);
	check_top_bottom(map, lines - 1, alloc);
	check_sides(map, alloc);
	check_walkable_cells(map, alloc);
}

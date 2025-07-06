/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_things.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:37:47 by hakader           #+#    #+#             */
/*   Updated: 2025/07/06 20:26:44 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	count_textures(t_cub *cub)
{
	return (cub->textures.n == 1 && cub->textures.s == 1
		&& cub->textures.w == 1 && cub->textures.e == 1
		&& cub->clr.c_cnt == 1 && cub->clr.f_cnt == 1);
}

int	textures_counter(t_cub *cub, int i, int start)
{
	if (ft_strncmp("NO ", &cub->game.map[i][start], 3) == 0)
		cub->textures.n++;
	else if (ft_strncmp("SO ", &cub->game.map[i][start], 3) == 0)
		cub->textures.s++;
	else if (ft_strncmp("WE ", &cub->game.map[i][start], 3) == 0)
		cub->textures.w++;
	else if (ft_strncmp("EA ", &cub->game.map[i][start], 3) == 0)
		cub->textures.e++;
	else if (ft_strncmp("F ", &cub->game.map[i][start], 2) == 0)
		cub->clr.f_cnt++;
	else if (ft_strncmp("C ", &cub->game.map[i][start], 2) == 0)
		cub->clr.c_cnt++;
	else
		return (1);
	return (0);
}

int	count_things(t_cub *cub, t_list *alloc)
{
	int (i), (start);
	i = 0;
	while (cub->game.map[i])
	{
		start = skip_whitespaces(cub->game.map, i, 0);
		if (cub->game.map[i][start] == '\0')
		{
			i++;
			continue ;
		}
		if (textures_counter(cub, i, start))
			break ;
		i++;
	}
	if (count_textures(cub))
		return (cub->game.jungle = &cub->game.map[i], 0);
	return (put_error("Invalid map", alloc), 1);
}

void	rgb_colors(t_cub *cub, t_list *alloc)
{
	if (count_commas(cub->clr.c) > 3 || count_commas(cub->clr.f) > 3)
		put_error("a lot of colors", alloc);
	cub->clr.f_colors = ft_split(cub->clr.f, ',', alloc);
	cub->clr.c_colors = ft_split(cub->clr.c, ',', alloc);
	if (cub->clr.f_colors == NULL || cub->clr.c_colors == NULL)
		return ;
	cub->clr.f_red = ft_atoi(cub->clr.f_colors[0], alloc);
	cub->clr.f_green = ft_atoi(cub->clr.f_colors[1], alloc);
	cub->clr.f_blue = ft_atoi(cub->clr.f_colors[2], alloc);
	cub->clr.c_red = ft_atoi(cub->clr.c_colors[0], alloc);
	cub->clr.c_green = ft_atoi(cub->clr.c_colors[1], alloc);
	cub->clr.c_blue = ft_atoi(cub->clr.c_colors[2], alloc);
	check_colors(cub, alloc);
}

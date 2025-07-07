/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:44:37 by hakader           #+#    #+#             */
/*   Updated: 2025/07/07 16:00:28 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	check_map(t_cub *cub, t_list *alloc)
{
	count_things(cub, alloc);
	clean_map(cub, alloc);
	whitespaces_handler(cub, alloc);
	rgb_colors(cub, alloc);
	remove_vide_lines(cub);
	check_valid_chars(cub, alloc);
	check_walls(cub->game.jungle, alloc);
}

void	check_colors(t_cub *cub, t_list *alloc)
{
	if (cub->clr.f_red < 0 || cub->clr.f_red > 255)
		put_error("Error\nColor not valid!", alloc);
	if (cub->clr.f_green < 0 || cub->clr.f_green > 255)
		exit_error("Error\nColor not valid!", alloc);
	if (cub->clr.f_blue < 0 || cub->clr.f_blue > 255)
		put_error("Error\nColor not valid!", alloc);
	if (cub->clr.c_red < 0 || cub->clr.c_red > 255)
		put_error("Error\ncolor not valid!", alloc);
	if (cub->clr.c_green < 0 || cub->clr.c_green > 255)
		put_error("Error\ncolor not valid!", alloc);
	if (cub->clr.c_blue < 0 || cub->clr.c_blue > 255)
		put_error("Error\nColor not valid!", alloc);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:39:16 by hakader           #+#    #+#             */
/*   Updated: 2025/06/30 16:35:51 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"


void	init_all(t_cub *cub)
{
	ft_bzero(&cub->axis, sizeof(t_axis));
	ft_bzero(&cub->clr, sizeof(t_color));
	ft_bzero(&cub->game, sizeof(t_game));
	ft_bzero(&cub->keys, sizeof(t_keys));
	ft_bzero(&cub->textutes, sizeof(t_textures));
	ft_bzero(cub, sizeof(t_cub));
}

int	skip_whitespaces(t_cub *cub, int line, int start)
{
	// if (!cub->game.map || !cub->game.map[line])
	// 	return (0);
	while (cub->game.map[line][start] <= 13 && cub->game.map[line][start] >= 9
		|| cub->game.map[line][start] == 32)
		start++;
	return (start);
}

int	is_whitespace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

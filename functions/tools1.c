/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 11:39:16 by hakader           #+#    #+#             */
/*   Updated: 2025/07/06 20:53:14 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	init_all(t_cub *cub)
{
	ft_bzero(&cub->axis, sizeof(t_axis));
	ft_bzero(&cub->clr, sizeof(t_color));
	ft_bzero(&cub->game, sizeof(t_game));
	ft_bzero(&cub->keys, sizeof(t_keys));
	ft_bzero(&cub->textures, sizeof(t_textures));
	ft_bzero(cub, sizeof(t_cub));
}

int	skip_whitespaces(char **map, int line, int start)
{
	char	c;

	if (!map || !map[line])
		return (start);
	c = map[line][start];
	while (c && ((c >= 9 && c <= 13) || c == 32))
		c = map[line][++start];
	return (start);
}

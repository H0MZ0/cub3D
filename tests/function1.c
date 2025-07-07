/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   function1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/07 15:15:32 by hakader           #+#    #+#             */
/*   Updated: 2025/07/07 15:16:07 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	check_textures(t_cub *cub, t_list *alloc)
{
	const char	*suffix;
	t_textures	*tx;

	suffix = ".xpm";
	tx = &cub->textures;
	if (ft_strlen(tx->ea) < 5 || ft_strlen(tx->no) < 5
		|| ft_strlen(tx->so) < 5 || ft_strlen(tx->we) < 5
		|| ft_strcmp(&tx->ea[ft_strlen(tx->ea) - 4], suffix) != 0
		|| ft_strcmp(&tx->no[ft_strlen(tx->no) - 4], suffix) != 0
		|| ft_strcmp(&tx->so[ft_strlen(tx->so) - 4], suffix) != 0
		|| ft_strcmp(&tx->we[ft_strlen(tx->we) - 4], suffix) != 0)
		put_error("textures name!", alloc);
}

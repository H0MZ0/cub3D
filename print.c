/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:36:51 by hakader           #+#    #+#             */
/*   Updated: 2025/07/07 15:19:09 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	print_map(t_cub *cub)
{
	int	i;

	i = 0;
	if (!cub || !cub->game.map)
		return ;
	while (cub->game.map[i])
		printf("%s\n", cub->game.map[i++]);
}

void	printf_jungle(t_cub *cub)
{
	int	i;

	i = 0;
	if (!cub->game.jungle)
		return ;
	while (cub->game.jungle[i])
		printf("%s\n", cub->game.jungle[i++]);
}

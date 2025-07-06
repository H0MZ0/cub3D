/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleaner.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:46:45 by hakader           #+#    #+#             */
/*   Updated: 2025/07/06 20:14:26 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

char	*whitespaces_remover(char *data, t_list *alloc)
{
	int	index;

	if (!data)
		return (NULL);
	index = ft_strlen(data) - 1;
	while (index > 0 && is_whitespace(data[index]))
		index--;
	data = ft_substr(data, 0, index + 1, alloc);
	return (data);
}

void	remove_vide_lines(t_cub *cub)
{
	int		i;
	char	**jungle;

	jungle = cub->game.jungle;
	if (!jungle)
		return ;
	i = 0;
	while (jungle[i])
		i++;
	i--;
	while (i >= 0 && jungle[i]
		&& skip_whitespaces(jungle, i, 0) == (int)ft_strlen(jungle[i]))
	{
		jungle[i] = NULL;
		i--;
	}
}

void	whitespaces_handler(t_cub *cub, t_list *alloc)
{
	cub->textures.so = whitespaces_remover(cub->textures.so, alloc);
	cub->textures.no = whitespaces_remover(cub->textures.no, alloc);
	cub->textures.ea = whitespaces_remover(cub->textures.ea, alloc);
	cub->textures.we = whitespaces_remover(cub->textures.we, alloc);
	cub->clr.c = whitespaces_remover(cub->clr.c, alloc);
	cub->clr.f = whitespaces_remover(cub->clr.f, alloc);
}

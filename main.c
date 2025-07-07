/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:17:49 by hakader           #+#    #+#             */
/*   Updated: 2025/07/07 22:48:25 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void	get_colors(t_cub *cub, int line, int start, t_list *alloc)
{
	int	i;

	i = skip_whitespaces(cub->game.map, line, start + 1);
	if (cub->game.map[line][start] == 'C'
		&& is_whitespace(cub->game.map[line][start + 1]))
		cub->clr.c = ft_strdup(&cub->game.map[line][i], alloc);
	else if (cub->game.map[line][start] == 'F'
		&& is_whitespace(cub->game.map[line][start + 1]))
		cub->clr.f = ft_strdup(&cub->game.map[line][i], alloc);
}

void	get_values(t_cub *cub, int line, int start, t_list *alloc)
{
	int	i;

	i = skip_whitespaces(cub->game.map, line, start + 2);
	if (cub->game.map[line][start] == 'N'
		&& cub->game.map[line][start + 1] == 'O')
		cub->textures.no = ft_strdup(&cub->game.map[line][i], alloc);
	else if (cub->game.map[line][start] == 'S'
		&& cub->game.map[line][start + 1] == 'O')
		cub->textures.so = ft_strdup(&cub->game.map[line][i], alloc);
	else if (cub->game.map[line][start] == 'W'
		&& cub->game.map[line][start + 1] == 'E')
		cub->textures.we = ft_strdup(&cub->game.map[line][i], alloc);
	else if (cub->game.map[line][start] == 'E'
		&& cub->game.map[line][start + 1] == 'A')
		cub->textures.ea = ft_strdup(&cub->game.map[line][i], alloc);
	else if ((cub->game.map[line][start] == 'F'
		|| cub->game.map[line][start] == 'C')
		&& is_whitespace(cub->game.map[line][start + 1]))
		get_colors(cub, line, start, alloc);
}

int	count_commas(char *data)
{
	int (i), (count);
	i = 0;
	count = 1;
	if (!data)
		return (0);
	while (data[i])
	{
		if (data[i] == ',')
			count++;
		i++;
	}
	return (count);
}

void	map_filter(t_cub *cub, char *map, t_list *alloc)
{
	parse_map_name(map, alloc);
	read_map(cub, map, alloc);
	check_map(cub, alloc);
}


int	main(int ac, char **av)
{
	t_cub	cub;
	t_list	*alloc;

	alloc = malloc(sizeof(t_list));
	if (!alloc)
		return (1);
	ft_bzero(alloc, sizeof(t_list));
	ft_bzero(&cub, sizeof(t_cub));
	if (ac != 2)
		return (put_error("Invalid arguments", alloc), 1);
	map_filter(&cub, av[1], alloc);
	in_mlx(&cub, alloc);
	// printf_jungle(&cub);
	free_all(&alloc);
	return (0);
}

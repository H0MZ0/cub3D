/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:17:49 by hakader           #+#    #+#             */
/*   Updated: 2025/06/27 14:06:24 by hakader          ###   ########.fr       */
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

int	column(char *map, t_list *alloc)
{
	char	*str;
	int		fd;
	int		size;

	fd = open(map, O_RDONLY);
	if (fd == -1)
		put_error("Failed to open map\n", alloc);
	size = 0;
	str = get_next_line(fd, alloc);
	while (str)
	{
		size++;
		str = get_next_line(fd, alloc);
	}
	close(fd);
	return (size);
}

void	read_map(t_cub *cub, char *map, t_list *alloc)
{
	char	*readed;
	
	int (i), (fd);
	fd = open (map, O_RDONLY);
	if (fd == -1)
		put_error("Error in map read", alloc);
	cub->column = column(map, alloc);
	cub->game.map = ft_malloc((cub->column + 1) * sizeof(char *), &alloc);
	if (!cub->column || !cub->game.map)
		put_error("Error\nMalloc failed", alloc);
	if (!cub->game.map)
	{
		close (fd);
		put_error ("Error in map", alloc);
	}
	readed = get_next_line(fd, alloc);
	i = 0;
	while (readed)
	{
		cub->game.map[i] = readed;
		readed = get_next_line(fd, alloc);
		i++;
	}
}

void	map_filter(t_cub cub, char *map, t_list *alloc)
{
	ft_bzero(&cub, sizeof(t_cub));
	read_map(&cub, map, alloc);
	
}

int	main(int ac, char **av)
{
	t_cub	cub;
	t_list	*alloc;

	alloc = malloc(sizeof(t_list));
	if (!alloc)
		return (1);
	ft_bzero(alloc, sizeof(t_list));
	if (ac != 2)
		return (put_error("invalid map!", alloc), 1);
	map_filter(cub, av[1], alloc);
	free_all(&alloc);
	return (1);
}

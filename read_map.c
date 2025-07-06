/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/06 19:36:24 by hakader           #+#    #+#             */
/*   Updated: 2025/07/06 20:28:58 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	get_map_name(char *map)
{
	int	len;

	len = ft_strlen(map) - 1;
	if (map[len] == '/')
		len--;
	while (len > 0)
	{
		if (map[len] == '/')
			return (len + 1);
		len--;
	}
	return (0);
}

void	parse_map_name(char *map, t_list *alloc)
{
	char	*name;

	int (start), (end);
	end = ft_strlen(map);
	start = get_map_name(map);
	name = ft_substr(map, start, end, alloc);
	if (name[ft_strlen(name) - 1] == '/')
		name = ft_substr(name, 0, ft_strlen(name) - 1, alloc);
	if (ft_strncmp(".cub", &name[ft_strlen(name) - 4], 4) != 0
		|| ft_strlen(name) < 5)
		put_error("invalid map name", alloc);
}

int	column(char *map, t_list *alloc)
{
	char	*str;

	int (fd), (size);
	fd = open(map, O_RDONLY);
	if (fd == -1)
		put_error("Failed to open map", alloc);
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
	fd = open(map, O_RDONLY);
	if (fd == -1)
		put_error("Failed to open map", alloc);
	cub->game.column = column(map, alloc);
	if (cub->game.column == 0)
		put_error("Empty map", alloc);
	cub->game.map = ft_malloc((cub->game.column + 1) * sizeof(char *), &alloc);
	if (!cub->game.column || !cub->game.map)
		put_error("Malloc failed", alloc);
	if (!cub->game.map)
	{
		close(fd);
		put_error("Error in map", alloc);
	}
	readed = get_next_line(fd, alloc);
	i = 0;
	while (readed)
	{
		cub->game.map[i++] = readed;
		readed = get_next_line(fd, alloc);
	}
	cub->game.map[i] = NULL;
}

void	clean_map(t_cub *cub, t_list *alloc)
{
	int (start), (line);
	line = 0;
	while (cub->game.map && cub->game.map[line])
	{
		start = skip_whitespaces(cub->game.map, line, 0);
		get_values(cub, line, start, alloc);
		line++;
	}
}

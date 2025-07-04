/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:17:49 by hakader           #+#    #+#             */
/*   Updated: 2025/07/02 10:25:25 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

void print_map(t_cub *cub)
{
	int i;

	i = 0;
	if (!cub || !cub->game.map)
		return;
	while (cub->game.map[i])
		printf("%s\n", cub->game.map[i++]);
}

int column(char *map, t_list *alloc)
{
	char *str;

	int(fd), (size);
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

void read_map(t_cub *cub, char *map, t_list *alloc)
{
	char *readed;

	int(i), (fd);
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

int count_textures(t_cub *cub)
{
	return (cub->textures.n == 1 && cub->textures.s == 1 &&
			cub->textures.w == 1 && cub->textures.e == 1 &&
			cub->clr.c_cnt == 1 && cub->clr.f_cnt == 1);
}

int count_things(t_cub *cub, t_list *alloc)
{
	int i, start;

	i = 0;
	while (cub->game.map[i])
	{
		start = skip_whitespaces(cub, i, 0);
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
			break;
		i++;
	}
	if (count_textures(cub))
		return (cub->game.jungle = &cub->game.map[i], 0);
	return (put_error("Invalid map", alloc), 1);
}

void get_colors(t_cub *cub, int line, int start, t_list *alloc)
{
	int i;

	i = skip_whitespaces(cub, line, start + 1);
	if (cub->game.map[line][start] == 'C'
		&& is_whitespace(cub->game.map[line][start + 1]))
		cub->clr.C = ft_strdup(&cub->game.map[line][i], alloc);
	else if (cub->game.map[line][start] == 'F'
		&& is_whitespace(cub->game.map[line][start + 1]))
		cub->clr.F = ft_strdup(&cub->game.map[line][i], alloc);
}

void	get_values(t_cub *cub, int line, int start, t_list *alloc)
{
	int	i;

	i = skip_whitespaces(cub, line, start + 2);
	if (cub->game.map[line][start] == 'N'
		&& cub->game.map[line][start + 1] == 'O')
		cub->textures.NO = ft_strdup(&cub->game.map[line][i], alloc);
	else if (cub->game.map[line][start] == 'S'
		&& cub->game.map[line][start + 1] == 'O')
		cub->textures.SO = ft_strdup(&cub->game.map[line][i], alloc);
	else if (cub->game.map[line][start] == 'W'
		&& cub->game.map[line][start + 1] == 'E')
		cub->textures.WE = ft_strdup(&cub->game.map[line][i], alloc);
	else if (cub->game.map[line][start] == 'E'
		&& cub->game.map[line][start + 1] == 'A')
		cub->textures.EA = ft_strdup(&cub->game.map[line][i], alloc);
	else if ((cub->game.map[line][start] == 'F'
			|| cub->game.map[line][start] == 'C')
		&& is_whitespace(cub->game.map[line][start + 1]))
		get_colors(cub, line, start, alloc);
}

void clean_map(t_cub *cub, t_list *alloc)
{
	int(start), (line);
	line = 0;
	while (cub->game.map && cub->game.map[line])
	{
		start = skip_whitespaces(cub, line, 0);
		get_values(cub, line, start, alloc);
		line++;
	}
}

char *whitespaces_remover(char *data, t_list *alloc)
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

void whitespaces_handler(t_cub *cub, t_list *alloc)
{
	cub->textures.SO = whitespaces_remover(cub->textures.SO, alloc);
	cub->textures.NO = whitespaces_remover(cub->textures.NO, alloc);
	cub->textures.EA = whitespaces_remover(cub->textures.EA, alloc);
	cub->textures.WE = whitespaces_remover(cub->textures.WE, alloc);
	cub->clr.C = whitespaces_remover(cub->clr.C, alloc);
	cub->clr.F = whitespaces_remover(cub->clr.F, alloc);
}

void check_colors(t_cub *cub, t_list *alloc)
{
	if (cub->clr.F_red < 0 || cub->clr.F_red > 255)
		put_error("Error\nColor not valid!", alloc);
	if (cub->clr.F_green < 0 || cub->clr.F_green > 255)
		exit_error("Error\nColor not valid!", alloc);
	if (cub->clr.F_blue < 0 || cub->clr.F_blue > 255)
		put_error("Error\nColor not valid!", alloc);
	if (cub->clr.C_red < 0 || cub->clr.C_red > 255)
		put_error("Error\nColor not valid!", alloc);
	if (cub->clr.C_green < 0 || cub->clr.C_green > 255)
		put_error("Error\nColor not valid!", alloc);
	if (cub->clr.C_blue < 0 || cub->clr.C_blue > 255)
		put_error("Error\nColor not valid!", alloc);
}

int count_commas(char *data)
{
	int i;
	int count;

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

void rgb_colors(t_cub *cub, t_list *alloc)
{
	if (count_commas(cub->clr.C) > 3 || count_commas(cub->clr.F) > 3)
		put_error("a lot of colors", alloc);
	cub->clr.f_colors = ft_split(cub->clr.F, ',', alloc);
	cub->clr.c_colors = ft_split(cub->clr.C, ',', alloc);
	if (cub->clr.f_colors == NULL || cub->clr.c_colors == NULL)
		return ;
	cub->clr.F_red = ft_atoi(cub->clr.f_colors[0], alloc);
	cub->clr.F_green = ft_atoi(cub->clr.f_colors[1], alloc);
	cub->clr.F_blue = ft_atoi(cub->clr.f_colors[2], alloc);
	cub->clr.C_red = ft_atoi(cub->clr.c_colors[0], alloc);
	cub->clr.C_green = ft_atoi(cub->clr.c_colors[1], alloc);
	cub->clr.C_blue = ft_atoi(cub->clr.c_colors[2], alloc);
	check_colors(cub, alloc);
}

void	check_textures(t_cub *cub, t_list *alloc)
{
	const char	*suffix;
	t_textures	*tx;

	suffix = ".xpm";
	tx = &cub->textures;
	if (ft_strlen(tx->EA) < 5 || ft_strlen(tx->NO) < 5
		|| ft_strlen(tx->SO) < 5 || ft_strlen(tx->WE) < 5
		|| ft_strcmp(&tx->EA[ft_strlen(tx->EA) - 4], suffix) != 0
		|| ft_strcmp(&tx->NO[ft_strlen(tx->NO) - 4], suffix) != 0
		|| ft_strcmp(&tx->SO[ft_strlen(tx->SO) - 4], suffix) != 0
		|| ft_strcmp(&tx->WE[ft_strlen(tx->WE) - 4], suffix) != 0)
		put_error("textures name!", alloc);
}

void check_map(t_cub *cub, t_list *alloc)
{
	count_things(cub, alloc);
	clean_map(cub, alloc);
	whitespaces_handler(cub, alloc);
	rgb_colors(cub, alloc);
	check_textures(cub, alloc);
	// print_map(cub);
	for(int i = 0; cub->game.jungle[i]; i++)
		printf("((%s))\n", cub->game.jungle[i]);
	// printf("textures.NO: {{%s}}\n", cub->textures.NO);
	// printf("textures.EA: {{%s}}\n", cub->textures.EA);
	// printf("textures.SO: {{%s}}\n", cub->textures.SO);
	// printf("textures.WE: {{%s}}\n", cub->textures.WE);
	// printf("F_red: {{%d}}\n", cub->clr.F_red);
	// printf("F_green: {{%d}}\n", cub->clr.F_green);
	// printf("F_blue: {{%d}}\n", cub->clr.F_blue);
	// printf("C_red: {{%d}}\n", cub->clr.C_red);
	// printf("C_green: {{%d}}\n", cub->clr.C_green);
	// printf("C_blue: {{%d}}\n", cub->clr.C_blue);

	// printf("cub->textures.SO=((%s))\n", cub->textures.SO);
	// printf("cub->textures.NO=((%s))\n", cub->textures.NO);
	// printf("cub->textures.EA=((%s))\n", cub->textures.EA);
	// printf("cub->textures.WE=((%s))\n", cub->textures.WE);
	// printf("cub->clr.C=((%s))\n", cub->clr.C);
	// printf("cub->clr.F=((%s))\n", cub->clr.F);
	// printf("\n\n");
}

int get_map_name(char *map)
{
	int len;

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

void parse_map_name(t_cub *cub, char *map, t_list *alloc)
{
	char *name;

	int(start), (end);
	end = ft_strlen(map);
	start = get_map_name(map);
	name = ft_substr(map, start, end, alloc);
	if (name[ft_strlen(name) - 1] == '/')
		name = ft_substr(name, 0, ft_strlen(name) - 1, alloc);
	if (ft_strncmp(".cub", &name[ft_strlen(name) - 4], 4) != 0
		|| ft_strlen(name) < 5)
		put_error("invalid map name", alloc);
}

void map_filter(t_cub cub, char *map, t_list *alloc)
{
	parse_map_name(&cub, map, alloc);
	ft_bzero(&cub, sizeof(t_cub));
	read_map(&cub, map, alloc);
	check_map(&cub, alloc);
	// handle_map(&cub, alloc);
	// print_map(&cub);
}

int main(int ac, char **av)
{
	t_cub cub;
	t_list *alloc;

	alloc = malloc(sizeof(t_list));
	if (!alloc)
		return (1);
	ft_bzero(alloc, sizeof(t_list));
	if (ac != 2)
		return (put_error("Invalid arguments", alloc), 1);
	map_filter(cub, av[1], alloc);
	free_all(&alloc);
	return (0);
}

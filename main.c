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
	cub->game.column = column(map, alloc);
	cub->game.map = ft_malloc((cub->game.column + 1) * sizeof(char *), &alloc);
	if (!cub->game.column || !cub->game.map)
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
	cub->game.map[i] = NULL;
}

void	count_things(t_cub *cub, t_list *alloc)
{
	int (i), (start);
	i = 0;
	while (cub->game.map[i])
	{
		start = skip_whitespaces(cub, i, 0);
		if (ft_strncmp("NO ", &cub->game.map[i][start], 3) == 0)
			cub->textutes.n += 1;
		else if (ft_strncmp("SO ", &cub->game.map[i][start], 3) == 0)
			cub->textutes.s += 1;
		else if (ft_strncmp("WE ", &cub->game.map[i][start], 3) == 0)
			cub->textutes.w += 1;
		else if (ft_strncmp("EA ", &cub->game.map[i][start], 3) == 0)
			cub->textutes.e += 1;
		else if (ft_strncmp("F ", &cub->game.map[i][start], 2) == 0)
			cub->clr.f_cnt += 1;
		else if (ft_strncmp("C ", &cub->game.map[i][start], 2) == 0)
			cub->clr.c_cnt += 1;
		i++;
	}
	if (cub->textutes.n != 1 || cub->textutes.s != 1 ||
		cub->textutes.w != 1 || cub->textutes.e != 1 ||
		cub->clr.c_cnt != 1 || cub->clr.f_cnt != 1)
		put_error("Error\nInvalid structure", alloc);
}

void	get_colors(t_cub *cub, int line, int start, t_list *alloc)
{
	int	i;

	i = 0;
	if (cub->game.map[line][start] == 'C' && is_whitespace(cub->game.map[line][start + 1]))
	{
		i = skip_whitespaces(cub, line, start + 1);
		cub->clr.C = ft_strdup(&cub->game.map[line][i], alloc);
	}
	else if (cub->game.map[line][start] == 'F' && is_whitespace(cub->game.map[line][start + 1]))
	{
		i = skip_whitespaces(cub, line, start + 1);
		cub->clr.F = ft_strdup(&cub->game.map[line][i], alloc);
	}
}

void	get_values(t_cub *cub, int line, int start, t_list *alloc)
{
	int	i;

	i = 0;
	// printf("{{%c%c}}\n", cub->game.map[line][start], cub->game.map[line][start + 1]);
	if (cub->game.map[line][start] == 'N' && cub->game.map[line][start + 1] == 'O' && is_whitespace(cub->game.map[line][start + 2]))
	{
		i = skip_whitespaces(cub, line, start + 2);
		cub->textutes.NO = ft_strdup(&cub->game.map[line][i], alloc);
	}
	else if (cub->game.map[line][start] == 'S' && cub->game.map[line][start + 1] == 'O' && is_whitespace(cub->game.map[line][start + 2]))
	{
		i = skip_whitespaces(cub, line, start + 2);
		cub->textutes.SO = ft_strdup(&cub->game.map[line][i], alloc);
	}
	else if (cub->game.map[line][start] == 'W' && cub->game.map[line][start + 1] == 'E' && is_whitespace(cub->game.map[line][start + 2]))
	{
		i = skip_whitespaces(cub, line, start + 2);
		cub->textutes.WE = ft_strdup(&cub->game.map[line][i], alloc);
	}
	else if (cub->game.map[line][start] == 'E' && cub->game.map[line][start + 1] == 'A' && is_whitespace(cub->game.map[line][start + 2]))
	{
		i = skip_whitespaces(cub, line, start + 2);
		cub->textutes.EA = ft_strdup(&cub->game.map[line][i], alloc);
	}
	else
		get_colors(cub, line, start, alloc);
}

void	clean_map(t_cub *cub, t_list *alloc)
{
	int (start), (line);
	line = 0;
	while (cub->game.map && cub->game.map[line])
	{
		start = skip_whitespaces(cub, line, 0);
		// while (cub->game.map[line][start])
		// {
		// 	if ((cub->game.map[line][start] >= 9 && cub->game.map[line][start] <= 13)
		// 		|| cub->game.map[line][start] == 32)
		// 		start++;
		// 	else
				get_values(cub, line, start, alloc);
			// start++;
		// }
		line++;
	}
}

char	*whitespaces_remover(char *data, t_list *alloc)
{
	int	index;

	index = ft_strlen(data) - 1;
	while (index > 0 && is_whitespace(data[index]))
		index--;
	data = ft_substr(data, 0, index + 1, alloc);
	return (data);
}

void	whitespaces_handler(t_cub *cub, t_list *alloc)
{
	cub->textutes.SO = whitespaces_remover(cub->textutes.SO, alloc);
	cub->textutes.NO = whitespaces_remover(cub->textutes.NO, alloc);
	cub->textutes.EA = whitespaces_remover(cub->textutes.EA, alloc);
	cub->textutes.WE = whitespaces_remover(cub->textutes.WE, alloc);
	cub->clr.C = whitespaces_remover(cub->clr.C, alloc);
	cub->clr.F = whitespaces_remover(cub->clr.F, alloc);
}

void	check_colors(t_cub *cub, t_list *alloc)
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

int	count_commas(char *data)
{
	int	i;
	int	count;

	i = 0;
	count = 1;
	while (data[i])
	{
		if (data[i] == ',')
			count++;
		i++;
	}
	return (count);
}

void	rgb_colors(t_cub *cub, t_list *alloc)
{
	if (count_commas(cub->clr.C) > 3 || count_commas(cub->clr.F) > 3)
		put_error("a lot of colors", alloc);
	cub->clr.f_colors = ft_split(cub->clr.F, ',', alloc);
	cub->clr.c_colors = ft_split(cub->clr.C, ',', alloc);
	cub->clr.F_red = ft_atoi(cub->clr.f_colors[0], alloc);
	cub->clr.F_green = ft_atoi(cub->clr.f_colors[1], alloc);
	cub->clr.F_blue = ft_atoi(cub->clr.f_colors[2], alloc);
	cub->clr.C_red = ft_atoi(cub->clr.c_colors[0], alloc);
	cub->clr.C_green = ft_atoi(cub->clr.c_colors[1], alloc);
	cub->clr.C_blue = ft_atoi(cub->clr.c_colors[2], alloc);
	check_colors(cub, alloc);
}



void	check_map(t_cub *cub, t_list *alloc)
{
	count_things(cub, alloc);
	clean_map(cub, alloc);
	whitespaces_handler(cub, alloc);
	rgb_colors(cub, alloc);

	printf("F_red: {{%d}}\n", cub->clr.F_red);
	printf("F_green: {{%d}}\n", cub->clr.F_green);
	printf("F_blue: {{%d}}\n", cub->clr.F_blue);
	printf("C_red: {{%d}}\n", cub->clr.C_red);
	printf("C_green: {{%d}}\n", cub->clr.C_green);
	printf("C_blue: {{%d}}\n", cub->clr.C_blue);

	// printf("cub->textutes.SO=((%s))\n", cub->textutes.SO);
	// printf("cub->textutes.NO=((%s))\n", cub->textutes.NO);
	// printf("cub->textutes.EA=((%s))\n", cub->textutes.EA);
	// printf("cub->textutes.WE=((%s))\n", cub->textutes.WE);
	// printf("cub->clr.C=((%s))\n", cub->clr.C);
	// printf("cub->clr.F=((%s))\n", cub->clr.F);
	// printf("\n\n");
}

void	map_filter(t_cub cub, char *map, t_list *alloc)
{
	ft_bzero(&cub, sizeof(t_cub));
	read_map(&cub, map, alloc);
	check_map(&cub, alloc);
	// print_map(&cub);
	
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
		return (put_error("Invalid arguments", alloc), 1);
	map_filter(cub, av[1], alloc);
	free_all(&alloc);
	return (0);
}

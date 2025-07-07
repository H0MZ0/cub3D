/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.1337.ma>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:17:03 by hakader           #+#    #+#             */
/*   Updated: 2025/07/07 23:02:07 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# define KEY_ESC 65307
# define KEY_UP 65362
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define KEY_LEFT 65361
# define KEY_W 119
# define KEY_D 100
# define KEY_S 115
# define KEY_A 97
# define ESC 65307
# define ON_DESTROY 17

# include "functions/structs.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>
# include <strings.h>
# include "mlx/mlx.h"
# include "LIBFT/libft.h"

void	rgb_colors(t_cub *cub, t_list *alloc);
void	check_valid_chars(t_cub *cub, t_list *alloc);
char	*whitespaces_remover(char *data, t_list *alloc);
void	remove_vide_lines(t_cub *cub);
void	whitespaces_handler(t_cub *cub, t_list *alloc);
int		count_textures(t_cub *cub);
int		count_things(t_cub *cub, t_list *alloc);
void	check_textures(t_cub *cub, t_list *alloc);
void	check_walls(char **map, t_list *alloc);
void	check_map(t_cub *cub, t_list *alloc);
void	check_colors(t_cub *cub, t_list *alloc);
int		is_whitespace(int c);
int		is_valid_char(char c);
int		is_walkable(char c);
int		is_wall(char c);
void	get_colors(t_cub *cub, int line, int start, t_list *alloc);
void	get_values(t_cub *cub, int line, int start, t_list *alloc);
int		count_commas(char *data);
void	print_map(t_cub *cub);
void	printf_jungle(t_cub *cub);
int		get_map_name(char *map);
void	parse_map_name(char *map, t_list *alloc);
int		column(char *map, t_list *alloc);
void	read_map(t_cub *cub, char *map, t_list *alloc);
void	clean_map(t_cub *cub, t_list *alloc);
int		skip_whitespaces(char **map, int line, int start);
void	in_mlx(t_cub *cub, t_list *alloc);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/27 10:17:03 by hakader           #+#    #+#             */
/*   Updated: 2025/06/29 12:26:18 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include "structs.h"
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include "LIBFT/libft.h"

void	print_map(t_cub *cub);
int		is_whitespace(int c);
int	    skip_whitespaces(char **map, int line, int start);
int		is_map_line(char *line);
int		validate_textures_and_colors(t_cub *cub, char *map_file, t_list *alloc);

#endif
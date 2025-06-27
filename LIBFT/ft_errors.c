/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/16 16:40:54 by hakader           #+#    #+#             */
/*   Updated: 2025/06/27 14:02:27 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	put_error(char *msg, t_list *alloc)
{
	write(2, msg, ft_strlen(msg));
	write(2, "\n", 1);
	free_all(&alloc);
	exit (1);
}

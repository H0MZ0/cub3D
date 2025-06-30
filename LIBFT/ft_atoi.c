/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:12:11 by hakader           #+#    #+#             */
/*   Updated: 2025/06/30 15:27:30 by hakader          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	exit_error(const char *str, t_list *alloc_list)
{
	ft_putstr_fd("Error\nInvalid color ->{", 2);
	ft_putstr_fd((char *)str, 2);
	ft_putendl_fd("}", 2);
	free_all(&alloc_list);
	exit(1);
}

int	skip(const char *str, int start)
{
	while ((str[start] >= 9 && str[start] <= 13) || str[start] == 32)
		start++;
	return (start);
}

long	ft_atoi(const char *str, t_list *alloc_list)
{
	long long	result;

	int (i), (sign);
	i = 0;
	sign = 1;
	result = 0;
	if (!str)
		exit_error(str, alloc_list);
	i = skip(str, i);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > ((LONG_MAX - (str[i] - '0')) / 10))
			exit_error(str, alloc_list);
		result = result * 10 + (str[i] - 48);
		i++;
	}
	i = skip(str, i);
	result = (long)result;
	if (str[i])
		exit_error(str, alloc_list);
	return (sign * result);
}

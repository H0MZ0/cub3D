/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hakader <hakader@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 18:12:11 by hakader           #+#    #+#             */
/*   Updated: 2025/07/01 12:04:04 by hakader          ###   ########.fr       */
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
	i = skip(str, 0);
	while (str[i] >= '0' && str[i] <= '9')
	{
		if (result > INT_MAX || result < INT_MIN)
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

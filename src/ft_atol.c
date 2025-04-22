/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:50:39 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/11 14:00:43 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	parse_number(const char *nptr, int i, long sign, long *result)
{
	long	num;

	num = 0;
	if (!(nptr[i] >= '0' && nptr[i] <= '9'))
		return (0);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (num > (LONG_MAX - (nptr[i] - '0')) / 10)
			return (0);
		num = num * 10 + (nptr[i] - '0');
		i++;
	}
	if (nptr[i] != '\0')
		return (0);
	*result = num * sign;
	return (1);
}

int	is_valid_range(long val, long min, long max)
{
	return (val >= min && val <= max);
}

int	ft_is_valid_int(const char *nptr, long *result)
{
	int		i;
	long	sign;

	i = 0;
	sign = 1;
	while (nptr[i] == ' ' || nptr[i] == '\t' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\f' || nptr[i] == '\v')
		i++;
	if (nptr[i] == '+' || nptr[i] == '-')
	{
		if (nptr[i] == '-')
			sign = -1;
		i++;
	}
	return (parse_number(nptr, i, sign, result));
}

long	ft_atol(const char *nptr)
{
	long	result;

	if (!ft_is_valid_int(nptr, &result))
		return (0);
	return (result);
}

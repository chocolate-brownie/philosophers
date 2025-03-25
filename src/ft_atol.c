/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:15:13 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/25 13:46:12 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static int	ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static int	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static int	validata_sign(const char *str, unsigned int *i)
{
	int	sign;

	sign = 1;
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			sign = -1;
		(*i)++;
	}
	return (sign);
}

long	ft_atol(const char *str)
{
	unsigned int	i;
	long			sign;
	long			number;

	i = 0;
	sign = 1;
	number = 0;
	while (ft_isspace(str[i]) == 1)
		i++;
	sign = validata_sign(str, &i);
	if (!ft_isdigit(str[i]))
		return (LONG_MIN);
	while (ft_isdigit(str[i]))
	{
		if (number > (LONG_MAX - (str[i] - '0')) / 10)
			return (LONG_MIN);
		number = ((number * 10) + (str[i] - '0'));
		i++;
	}
	if (str[i] != '\0')
		return (LONG_MIN);
	return (number * sign);
}

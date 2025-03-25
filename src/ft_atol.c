/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 11:15:13 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/25 17:26:10 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static inline bool	ft_isspace(char c)
{
	return (c == ' ' || (c >= 9 && c <= 13));
}

static inline bool	ft_isdigit(char c)
{
	return (c >= '0' && c <= '9');
}

static const char	*validate_input(const char *str)
{
	const char	*valid_number;
	int			length;

	length = 0;
	while (ft_isspace(*str))
		++str;
	if (*str == '+')
		++str;
	else if (*str == '-')
		error_exit("You've entered a negative number");
	if (!ft_isdigit(*str))
		error_exit("You've entered a non-digit character");
	valid_number = str;
	while (ft_isdigit(*str++))
		length++;
	if (length > 10)
		error_exit("Range overflow (INTMAX is the limit)");
	return (valid_number);
}

long	ft_atol(const char *str)
{
	long	sign;
	long	number;

	sign = 1;
	number = 0;
	str = validate_input(str);
	while (ft_isdigit(*str))
		number = (number * 10) + (*str++ - '0');
	if (number > INT_MAX)
		error_exit("Range overflow (INTMAX is the limit)");
	return (number * sign);
}

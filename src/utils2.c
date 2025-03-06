/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:53:33 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/06 00:47:42 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

struct timeval	get_current_time(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		error_exit("gettimeofday failed");
	return (*time);
}

int	ft_usleep(uint32_t milliseconds)
{
	struct timeval start;
	uint32_t elapsed;

	get_current_time(&start);
	while (1)
	{
		elapsed = get_elapsed_time(start);
		if (elapsed >= milliseconds)
			break ;
		usleep(500);
	}
	return (0);
}
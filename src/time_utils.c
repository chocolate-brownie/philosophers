/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/04 21:12:46 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/11 11:50:06 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

__uint32_t	elapsed_time(struct timeval *ref)
{
	struct timeval	current;
	__uint32_t		diff;

	gettimeofday(&current, NULL);
	diff = (current.tv_sec - ref->tv_sec) * 1000;
	diff += (current.tv_usec - ref->tv_usec) / 1000;
	return (diff);
}

void	ft_usleep(__uint32_t time, t_data *data)
{
	struct timeval	current;

	gettimeofday(&current, NULL);
	while (elapsed_time(&current) < time)
	{
		if (check_sb_dead(data))
			break ;
		usleep(100);
	}
}

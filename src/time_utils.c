/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:53:33 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/21 15:57:45 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_usleep(uint32_t time, t_data *data)
{
	struct timeval	current;

	get_current_time(&current);
	while (get_elapsed_time(current) < time)
	{
		if (check_death(data))
			break ;
		usleep(100);
	}
}

struct timeval	get_current_time(struct timeval *time)
{
	if (gettimeofday(time, NULL))
		error_exit("gettimeofday failed");
	return (*time);
}

uint32_t	get_elapsed_time(struct timeval start)
{
	struct timeval	current;
	uint32_t		diff;

	if (gettimeofday(&current, NULL))
		perror("gettimeofday error");
	diff = (current.tv_sec - start.tv_sec) * 1000;
	diff += (current.tv_usec - start.tv_usec) / 1000;
	return (diff);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:36:55 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/28 20:53:13 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	get_time(t_time timecode)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		error_exit("getimeofday failed");
	if (timecode == SECONDS)
		return (tv.tv_sec + (tv.tv_usec / 1e6));
	else if (timecode == MILLISECONDS)
		return (tv.tv_sec * 1e3) + (tv.tv_usec / 1e3);
	else if (timecode == MICROSECONDS)
		return ((tv.tv_sec * 1e6) + tv.tv_usec);
	else
		error_exit("wrong timecode");
	return (LONG_MIN);
}

void	ft_usleep(long microsec, t_global *data)
{
	long	start;
	long	elapsed;
	long	remaining;

	start = get_time(MICROSECONDS);
	while ((get_time(MICROSECONDS) - start) < microsec)
	{
		if (simulation_finished(data))
			break ;
		elapsed = get_time(MICROSECONDS) - start;
		remaining = microsec - elapsed;
		if (remaining > 1e3)
			usleep(remaining / 2);
		else
		{
			while ((get_time(MICROSECONDS) - start) < microsec)
				;
		}
	}
}

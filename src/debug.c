/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:54:52 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/25 20:29:44 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_data(t_global *data)
{
	double	time_in_sec;

	printf("Number of philosophers: %u\n", data->nbr_of_philo);
	printf("Time to die: %u\n", data->time_to_die);
	printf("Time to eat: %u\n", data->time_to_eat);
	printf("Time to sleep: %u\n", data->time_to_sleep);
	printf("Must eat count %u\n", data->must_eat_count);
	time_in_sec = data->start_simul->tv_sec + (data->start_simul->tv_usec
			/ 1000000.0);
	printf("Time: %.6f seconds\n", time_in_sec);
	printf("Anybody died? Are philos full?: %d\n", data->end_simul);
}

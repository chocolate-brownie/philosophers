/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:54:52 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/07 02:31:22 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_data(t_data *data)
{
	printf("-----------------------------------\n");
	printf("Number of philosophers: %u\n", data->nbr_of_phils);
	printf("Time to die: %u\n", data->time_to_die);
	printf("Time to eat: %u\n", data->time_to_eat);
	printf("Time to sleep: %u\n", data->time_to_sleep);
	printf("Must eat count %u\n", data->must_eat_times);
	printf("Time to think: %u\n", data->time_to_think);
	printf("-----------------------------------\n");
}

void	write_status_debug(t_status status, t_philo *philo,
		__uint32_t elapsed_time)
{
	if (status == FORK_ONE)
		printf("%05u %d has taken 1st fork " CYAN "[id: %u]\n" RESET,
			elapsed_time, philo->id, philo->data->fork_id);
	else if (status == FORK_TWO)
		printf("%05u %d has taken 2nd fork " CYAN "[id: %u]\n" RESET,
			elapsed_time, philo->id, philo->data->fork_id);
	else if (status == EATING)
		printf("%05u %d is eating " YELLOW "[meals eaten: %u]\n" RESET,
			elapsed_time, philo->id, philo->num_meals + 1);
	else if (status == THINKING)
		printf("%05u %d is thinkin\n", elapsed_time, philo->id);
	else if (status == SLEEPING)
		printf("%05u %d is sleeping\n", elapsed_time, philo->id);
	else if (status == DIED)
		printf(RED "%05u %d died\n" RESET, elapsed_time, philo->id);
}

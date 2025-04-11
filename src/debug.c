/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 18:54:52 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/11 13:04:15 by mgodawat         ###   ########.fr       */
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

void	debug_init_philo(t_philo *philo, t_data *data, __uint16_t i)
{
	printf("-----------------------------------\n");
	printf("Philo id: %u " BLUE "[fork in front: %u]\n" RESET, philo->id, i);
	printf("Philo status: %u\n", philo->status);
	printf(CYAN "Philo last meal time: %.6f seconds\n" RESET,
		data->last_meal[i].tv_sec + data->last_meal[i].tv_usec / 1000000.0);
	printf("Philo num of meals: %u\n", philo->num_meals);
	printf("Philo full: %u\n", philo->is_full);
	printf("-----------------------------------\n");
}

void	check_meal_completion_status(t_data *data)
{
	printf(GREEN "\n----- FINAL MEAL STATUS -----\n" RESET);
	printf("Required meals: %u, Philosophers who finished: %u\n",
		data->must_eat_times, data->fulled_phils);
	if (data->fulled_phils == data->nbr_of_phils && data->must_eat_times > 0)
	{
		printf(GREEN "SUCCESS: All philosophers completed %u meals\n" RESET,
			data->must_eat_times);
	}
	else if (data->must_eat_times > 0)
	{
		printf(RED "INCOMPLETE: %u/%u \n" RESET, data->fulled_phils,
			data->nbr_of_phils);
	}
	else
	{
		printf(YELLOW "No meal requirement was set\n" RESET);
	}
	printf(GREEN "----------------------------\n" RESET);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 06:45:37 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/20 09:50:32 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	print_validated_data(t_data *data)
{
	(void)data;
	DEBUG_PRINT("----------------------------\n");
	DEBUG_PRINT("Number of philosophers: %u\n", data->nbr_of_philo);
	DEBUG_PRINT("Time to die: %u\n", data->time_to_die);
	DEBUG_PRINT("Time to eat: %u\n", data->time_to_eat);
	DEBUG_PRINT("Time to sleep: %u\n", data->time_to_sleep);
	DEBUG_PRINT("Number of meals: %u\n", data->must_eat_count);
	DEBUG_PRINT("----------------------------\n");
}

/*
void	print_philo_data(t_philo *philo, unsigned int i)
{
	DEBUG_PRINT(CYAN "Philo id: [%d]:" RESET "\n", philo->philo_id);
	DEBUG_PRINT("Meals eaten: %u\n", philo->meals_eaten);
	DEBUG_PRINT("Last meal at: %lu ms\n", print_relative_ms(philo->last_meal,
			philo->data->simul_start));
	DEBUG_PRINT("Left fork: [%d]\n", i);
	DEBUG_PRINT("Right fork: [%d]\n", (i + 1) % philo->data->nbr_of_philo);
	DEBUG_PRINT("\n");
}
*/
/*
void	print_final_state(t_data *data)
{
	unsigned int	i;
	struct timeval	simul_end_time;

	get_current_time(&simul_end_time);
	DEBUG_PRINT(RED "\nSimulation ended at: %lu ms\n\n" RESET,
		print_relative_ms(simul_end_time, data->simul_start));
	i = -1;
	while (++i < data->nbr_of_philo)
		print_philo_data(&data->philos[i], i);
}
*/

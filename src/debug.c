/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 06:45:37 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/11 01:37:15 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdint.h>
#include <sys/types.h>

#define TOP_LEFT "╔"
#define TOP_RIGHT "╗"
#define BOTTOM_LEFT "╚"
#define BOTTOM_RIGHT "╝"
#define HORIZONTAL "═"
#define VERTICAL "║"

void	print_box_message(const char *msg)
{
	int	i;

	printf(GREEN);
	printf("%s", TOP_LEFT);
	i = -1;
	while (++i < 25)
		printf("%s", HORIZONTAL);
	printf("%s\n", TOP_RIGHT);
	printf("%s   %s   %s\n", VERTICAL, msg, VERTICAL);
	printf("%s", BOTTOM_LEFT);
	i = -1;
	while (++i < 25)
		printf("%s", HORIZONTAL);
	printf("%s\n", BOTTOM_RIGHT);
	printf(RESET);
}

void	print_validated_data(t_data *data)
{
	printf("\n");
	print_box_message("  Input successful ");
	printf("\n");
	printf("Number of philosophers: %u\n", data->nbr_of_philo);
	printf("Time to die: %u\n", data->time_to_die);
	printf("Time to eat: %u\n", data->time_to_eat);
	printf("Time to sleep: %u\n", data->time_to_sleep);
	printf("Number of meals: %u\n", data->must_eat_count);
	printf("\n");
}

uint64_t	print_relative_ms(struct timeval time, struct timeval start)
{
	uint64_t	time_ms;
	uint64_t	start_ms;

	time_ms = (time.tv_sec * (uint64_t)1000) + (time.tv_usec / 1000);
	start_ms = (start.tv_sec * (uint64_t)1000) + (start.tv_usec / 1000);
	return (time_ms - start_ms);
}

void	print_philo_data(t_philo *philo, unsigned int i)
{
	printf(CYAN "Philo id: [%d]:" RESET "\n", philo->philo_id);
	printf("Meals eaten: %u\n", philo->meals_eaten);
	printf("Last meal at: %lu ms\n", print_relative_ms(philo->last_meal,
			philo->data->simul_start));
	printf("Left fork: [%d]\n", i);
	printf("Right fork: [%d]\n", (i + 1) % philo->data->nbr_of_philo);
	printf("\n");
}

void	print_final_state(t_data *data)
{
	unsigned int	i;
	struct timeval	simul_end_time;

	get_current_time(&simul_end_time);
	printf(RED "\nSimulation ended at: %lu ms\n\n" RESET,
		print_relative_ms(simul_end_time, data->simul_start));
	i = -1;
	while (++i < data->nbr_of_philo)
		print_philo_data(&data->philos[i], i);
}

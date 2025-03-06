/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 06:45:37 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/05 10:01:36 by mgodawat         ###   ########.fr       */
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

static void	print_box_message(const char *msg)
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
	printf("\n");
}

void	print_philo_data(t_philo *philo)
{
	uint64_t	ms;

	ms = (philo->last_meal.tv_sec * 1000) + (philo->last_meal.tv_usec / 1000);
	printf(CYAN "Philosopher %u initialized:" RESET "\n", philo->philo_id);
	printf("  - Meals eaten: %u\n", philo->meals_eaten);
	printf("  - Fork left: %u\n", philo->fork_left);
	printf("  - Fork right: %u\n", philo->fork_right);
	printf("  - Last meal timestamp: %lu ms\n\n", ms);
}

uint64_t	print_ms(struct timeval ref)
{
	return ((ref.tv_sec * 1000) + (ref.tv_usec / 1000));
}

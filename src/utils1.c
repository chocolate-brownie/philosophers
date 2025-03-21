/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:09:18 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/21 16:14:22 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <stdio.h>

/**
 * TODO: make a ft_atol function
 * TODO: make cleanup function
 */

void	philo_mark_dead(t_data *data)
{
	handle_mutexes(data->mtx_death, LOCK);
	data->someone_dead = true;
	handle_mutexes(data->mtx_death, UNLOCK);
}

void	check_input(int argc, char *argv[])
{
	int	i;

	DEBUG_PRINT_YELLOW("Checking input\n");
	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Program should be as follows:\n");
		printf("./philo num_of_phils time_to_die time_to_eat time_to_sleep ");
		printf("[optional: must_eat_time]\n");
		error_exit("Input validation");
	}
	while (++i < argc)
	{
		if (atol(argv[i]) < 1)
			error_exit("Arguments should contain positive values");
	}
	DEBUG_PRINT_GREEN("Checking input success\n");
}

void	error_exit(const char *err_msg)
{
	fprintf(stderr, RED "[ERROR]: %s\n" RESET, err_msg);
	exit(1);
}

void	print_message(t_philo *philo, t_status status)
{
	uint32_t	timestamp;

	timestamp = get_elapsed_time(philo->data->simul_start);
	handle_mutexes(philo->data->mtx_print, LOCK);
	if (status == THINKING)
		printf("%05u %2d is " YELLOW "thinking\n" RESET, timestamp,
			philo->philo_id);
	else if (status == EATING)
		printf("%05u %2d is " GREEN "eating\n" RESET, timestamp,
			philo->philo_id);
	else if (status == SLEEPING)
		printf("%05u %2d is " CYAN "sleeping\n" RESET, timestamp,
			philo->philo_id);
	else if (status == FORK)
		printf("%05u %2d has taken a fork\n", timestamp, philo->philo_id);
	else if (status == DIED)
		printf("%05u %2d " RED "died\n" RESET, timestamp, philo->philo_id);
	else
		error_exit("Invalid philosoper status");
	handle_mutexes(philo->data->mtx_print, UNLOCK);
}

bool	check_death(t_data *data)
{
	bool	is_dead;

	is_dead = false;
	handle_mutexes(data->mtx_death, LOCK);
	if (data->someone_dead)
		is_dead = true;
	handle_mutexes(data->mtx_death, UNLOCK);
	return (is_dead);
}

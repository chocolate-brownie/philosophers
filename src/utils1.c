/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:09:18 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/07 00:11:17 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_exit(const char *error_msg)
{
	if (error_msg)
		printf(RED "ERROR: %s\n" RESET, error_msg);
	exit(EXIT_FAILURE);
}

void	*safe_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
	{
		fprintf(stderr, "Memory allocation failed for %zu bytes\n", size);
		exit(1);
	}
	return (ptr);
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

/** You can control the mtx_print in this function
 * dont print if someone is dead
 */
void	print_message(t_philo *philo, t_status status)
{
	bool	is_dead;

	handle_mutexes(&philo->data->mtx_death, LOCK);
	is_dead = philo->data->someone_dead;
	handle_mutexes(&philo->data->mtx_death, UNLOCK);
	if (is_dead && status == DIED)
		return ;
	handle_mutexes(&philo->data->mtx_print, LOCK);
	if (status == THINKING)
		printf("%d %d is " YELLOW "thinking\n" RESET,
			get_elapsed_time(philo->data->simul_start), philo->philo_id);
	else if (status == EATING)
		printf("%d %d is " GREEN "eating\n" RESET, get_elapsed_time(philo->data->simul_start),
			philo->philo_id);
	else if (status == SLEEPING)
		printf("%d %d is " CYAN "sleeping\n" RESET,
			get_elapsed_time(philo->data->simul_start), philo->philo_id);
	else if (status == FORK)
		printf("%d %d has taken a fork\n",
			get_elapsed_time(philo->data->simul_start), philo->philo_id);
	else if (status == DIED)
		printf("%d %d " RED "died\n" RESET, get_elapsed_time(philo->data->simul_start),
			philo->philo_id);
	handle_mutexes(&philo->data->mtx_print, UNLOCK);
}

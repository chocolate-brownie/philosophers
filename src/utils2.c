/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/05 09:53:33 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/12 04:52:34 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/**
 * TODO: check whether they are dying during the system sleep
 */
int	ft_usleep(uint32_t milliseconds)
{
	struct timeval	start;
	uint32_t		elapsed;

	get_current_time(&start);
	while (1)
	{
		elapsed = get_elapsed_time(start);
		if (elapsed >= milliseconds)
			break ;
		usleep(500);
	}
	return (0);
}

bool	check_meals_complete(t_philo *philo)
{
	if (philo->data->must_eat_count == 0)
		return (false);
	return (philo->meals_eaten >= philo->data->must_eat_count);
}

void	cleanup(t_philo **philos, t_data *data)
{
	unsigned int	i;

	printf(RED "\nCleaning up resources...\n\n" RESET);
	i = 0;
	while (i < data->nbr_of_philo)
	{
		handle_mutexes(&data->mtx_forks[i], DESTROY);
		printf("mtx_fork[%d]\tDESTROY\t" GREEN "success\n" RESET, i);
		i++;
	}
	handle_mutexes(&data->mtx_death, DESTROY);
	printf("mtx_death\tDESTROY\t" GREEN "success\n" RESET);
	handle_mutexes(&data->mtx_print, DESTROY);
	printf("mtx_print\tDESTROY\t" GREEN "success\n" RESET);
	handle_mutexes(&data->mtx_meal, DESTROY);
	printf("mtx_meal\tDESTROY\t" GREEN "success\n" RESET);
	if (data->mtx_forks)
	{
		free(data->mtx_forks);
		printf("mtx_forks\tFREE\t" GREEN "success\n" RESET);
	}
	if (*philos)
	{
		free(*philos);
		*philos = NULL;
		printf("philos\t\tFREE\t" GREEN "success\n" RESET);
	}
	printf(GREEN "\nCleanup complete!\n\n" RESET);
}

void	*ft_memset(void *s, int c, size_t n)
{
	unsigned char	*ptr;

	ptr = s;
	while (n--)
		*ptr++ = (unsigned char)c;
	return (s);
}

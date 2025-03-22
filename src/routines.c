/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 19:57:59 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/22 12:13:07 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	perform_eating(t_philo *philo)
{
	print_message(philo, EATING);
	handle_mutexes(philo->data->mtx_meal, LOCK);
	get_current_time(&philo->data->last_meal[philo->philo_id - 1]);
	handle_mutexes(philo->data->mtx_meal, UNLOCK);
	philo->meals_eaten++;
	if (philo->data->must_eat_count > 0 && !philo->is_full)
	{
		if (philo->meals_eaten >= philo->data->must_eat_count)
		{
			handle_mutexes(philo->data->mtx_full, LOCK);
			philo->data->fulled_phils++;
			handle_mutexes(philo->data->mtx_full, UNLOCK);
			philo->is_full = true;
		}
	}
	ft_usleep(philo->data->time_to_eat, philo->data);
}

static void	thinking(t_philo *philo)
{
	print_message(philo, THINKING);
	if (philo->data->nbr_of_philo % 2)
		ft_usleep(philo->data->time_to_think, philo->data);
	philo->status = EATING;
}

static void	eating(t_philo *philo)
{
	unsigned int	left_fork;
	unsigned int	right_fork;

	get_fork_indices(philo, &left_fork, &right_fork);
	if (!grabbing_forks(philo))
		return ;
	perform_eating(philo);
	if (philo->data->nbr_of_philo > 1)
	{
		handle_mutexes(&philo->data->mtx_forks[left_fork], UNLOCK);
		handle_mutexes(&philo->data->mtx_forks[right_fork], UNLOCK);
	}
	philo->status = SLEEPING;
}

static void	sleeping(t_philo *philo)
{
	print_message(philo, SLEEPING);
	ft_usleep(philo->data->time_to_sleep, philo->data);
	philo->status = THINKING;
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->philo_id % 2))
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	while (1)
	{
		if (check_death(philo->data))
			break ;
		if (philo->status == THINKING)
			thinking(philo);
		else if (philo->status == EATING)
			eating(philo);
		else if (philo->status == SLEEPING)
			sleeping(philo);
	}
	free(philo);
	return (NULL);
}

/* void	*monitor_routine(void *arg)
{
	t_data	*data;

	data = (t_data *)arg;
	(void)data;
	// Your monitor logic here
	return (NULL);
} */

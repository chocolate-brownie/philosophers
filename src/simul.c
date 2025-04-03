/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:00:13 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/03 15:00:37 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	thinking(t_philo *philo, bool pre_simul)
{
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	time_to_think;

	time_to_eat = philo->global_data->time_to_eat;
	time_to_sleep = philo->global_data->time_to_sleep;
	time_to_think = (time_to_eat * 2) - time_to_sleep;
	if (!pre_simul)
		print_status(THINKING, philo, DEBUG);
	if (philo->global_data->nbr_of_philo % 2 == 0)
		return ;
	ft_usleep(time_to_think * 0.42, philo->global_data);
}

static void	*handle_philo_one(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->global_data);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECONDS));
	set_increase_long(&philo->global_data->mutex_data,
		&philo->global_data->nbr_running_threads);
	print_status(FORK_ONE, philo, DEBUG);
	while (!simulation_finished(philo->global_data))
		usleep(200);
	return (NULL);
}

static void	eating(t_philo *philo)
{
	unsigned int	meals_count;

	meals_count = 0;
	pthread_mutex_lock(&philo->right_fork->mtx_fork);
	print_status(FORK_ONE, philo, DEBUG);
	pthread_mutex_lock(&philo->left_fork->mtx_fork);
	print_status(FORK_TWO, philo, DEBUG);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECONDS));
	meals_count = philo->meals_count + 1;
	set_long(&philo->philo_mutex, &philo->meals_count, meals_count);
	print_status(EATING, philo, DEBUG);
	ft_usleep(philo->global_data->time_to_eat, philo->global_data);
	if (philo->global_data->must_eat_count > 0
		&& philo->meals_count == philo->global_data->must_eat_count)
		set_bool(&philo->philo_mutex, &philo->full, true);
	pthread_mutex_unlock(&philo->right_fork->mtx_fork);
	pthread_mutex_unlock(&philo->left_fork->mtx_fork);
}

static void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->global_data);
	set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECONDS));
	set_increase_long(&philo->global_data->mutex_data,
		&philo->global_data->nbr_running_threads);
	calculate_thinking(philo);
	while (!simulation_finished(philo->global_data))
	{
		if (get_bool(&philo->global_data->mutex_data, &philo->full))
			break ;
		eating(philo);
		print_status(SLEEPING, philo, DEBUG);
		ft_usleep(philo->global_data->time_to_sleep, philo->global_data);
		thinking(philo, false);
	}
	return (NULL);
}

void	simulation(t_global *data)
{
	unsigned int	i;

	if (data->must_eat_count == 0)
		return ;
	if (data->nbr_of_philo == 1)
	{
		pthread_create(&data->philos[0].thread_id, NULL, &handle_philo_one,
			&data->philos[0]);
	}
	else
	{
		i = -1;
		while (++i < data->nbr_of_philo)
			pthread_create(&data->philos[i].thread_id, NULL, &start_routine,
				&data->philos[i]);
	}
	monitoring(data);
	data->start_simul = get_time(MILLISECONDS);
	set_bool(&data->mutex_data, &data->all_threads_ready, true);
	i = -1;
	while (++i < data->nbr_of_philo)
		pthread_join(data->philos[i].thread_id, NULL);
	set_bool(&data->mutex_data, &data->end_simul, true);
	pthread_join(data->thread_monitor, NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:00:13 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/01 13:59:23 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	thinking(t_philo *philo)
{
	print_status(THINKING, philo, DEBUG);
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
	/* printf("Philo thread data structure at %p\n",
		(void *)philo->global_data);
	printf("Philo thread mutex_data at %p\n",
		(void *)&philo->global_data->mutex_data); */
	wait_all_threads(philo->global_data);
	set_increase_long(&philo->global_data->mutex_data,
		&philo->global_data->nbr_running_threads);
	/* printf(BLUE "Philo thread nbr_running_threads at %p (value:
		%ld)\n" RESET,
		(void *)&philo->global_data->nbr_running_threads,
		philo->global_data->nbr_running_threads); */
	/* set_long(&philo->philo_mutex, &philo->last_meal_time,
		get_time(MILLISECONDS)); */
	handle_philo_one(philo->global_data);
	while (!simulation_finished(philo->global_data))
	{
		if (get_bool(&philo->global_data->mutex_data, &philo->full))
			break ;
		eating(philo);
		print_status(SLEEPING, philo, DEBUG);
		ft_usleep(philo->global_data->time_to_sleep, philo->global_data);
		thinking(philo);
	}
	return (NULL);
}

void	simulation(t_global *data)
{
	int				thread_result;
	unsigned int	i;
	unsigned int	j;

	if (get_long(&data->mutex_data, (long *)&data->must_eat_count) == 0)
		return ;
	i = -1;
	while (++i < data->nbr_of_philo)
	{
		thread_result = pthread_create(&data->philos[i].thread_id, NULL,
				&start_routine, &data->philos[i]);
		if (thread_result != 0)
		{
			j = -1;
			while (++j < i)
				pthread_detach(data->philos[j].thread_id);
			cleanup(data);
			error_exit("Creating threads for start_routine");
		}
	}
	monitoring(data);
	data->start_simul = get_time(MILLISECONDS);
	if (!set_bool(&data->mutex_data, &data->all_threads_ready, true))
		return ;
	join_threads(data);
}

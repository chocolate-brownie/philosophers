/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:24:17 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/11 12:26:30 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*monitor_routine(void *arg)
{
	t_data		*data;
	__uint16_t	i;

	data = (t_data *)arg;
	while (1)
	{
		i = 0;
		while (i < data->nbr_of_phils)
		{
			if (check_starved_time(i, data))
			{
				turn_dead(data);
				return (NULL);
			}
			i++;
		}
		if (check_all_full(data))
		{
			turn_dead(data);
			return (NULL);
		}
	}
	return (NULL);
}

static void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!(philo->id % 2))
		ft_usleep(philo->data->time_to_eat / 2, philo->data);
	while (1)
	{
		if (check_sb_dead(philo->data))
			break ;
		if (philo->status == THINKING)
			thinking(philo);
		else if (philo->status == EATING)
		{
			if (philo->id % 2)
				eat_with_fork_left(philo);
			else
				eat_with_fork_right(philo);
			philo->status = SLEEPING;
		}
		else if (philo->status == SLEEPING)
			sleeping(philo);
	}
	free(philo);
	return (NULL);
}

static int	init_threads(t_data *data, pthread_t *thread)
{
	__uint16_t	i;
	t_philo		*philo;

	i = -1;
	if (DEBUG == 1)
		print_data(data);
	while (++i < data->nbr_of_phils)
	{
		philo = malloc(sizeof(t_philo));
		if (!philo)
			return (1);
		init_philo(philo, i, data);
		if (pthread_create(&thread[i], NULL, &start_routine, philo))
			return (2);
	}
	if (pthread_create(&thread[i], NULL, &monitor_routine, data))
		return (2);
	return (0);
}

static void	join_threads(t_data *data, pthread_t *thread)
{
	__uint8_t	i;

	i = -1;
	while (++i < data->nbr_of_phils + 1)
	{
		if (pthread_join(thread[i], NULL))
			return ;
	}
	free(thread);
	free(data->last_meal);
}

int	main(int argc, char *argv[])
{
	t_data			data;
	pthread_t		*thread;
	pthread_mutex_t	*mtx_fork;
	pthread_mutex_t	mtx[4];
	int				err;

	if (control_args(argc, argv))
		return (1);
	if (init_data(argc, argv, &data))
		return (2);
	thread = malloc(sizeof(pthread_t) * (data.nbr_of_phils + 1));
	if (!thread)
		return (free(data.last_meal), 2);
	mtx_fork = malloc(sizeof(pthread_mutex_t) * data.nbr_of_phils);
	if (!mtx_fork)
		return (free(data.last_meal), free(thread), 2);
	init_mutexes(&data, mtx_fork, mtx);
	err = init_threads(&data, thread);
	if (err)
		turn_dead(&data);
	join_threads(&data, thread);
	if (DEBUG == 1)
		check_meal_completion_status(&data);
	destroy_mutex(&data, mtx_fork, mtx);
}

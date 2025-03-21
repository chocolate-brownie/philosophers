/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:24:17 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/21 15:14:18 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_philo(t_philo *philo, unsigned int i, t_data *data)
{
	DEBUG_PRINT("----------------------------\n");
	philo->philo_id = i + 1;
	DEBUG_PRINT_PURPLE("philo_id: %u\n", philo->philo_id);
	philo->status = EATING;
	DEBUG_PRINT_PURPLE("philo_status: %d\n", philo->status);
	philo->meals_eaten = 0;
	DEBUG_PRINT_PURPLE("philo_meals_eaten: %u\n", philo->meals_eaten);
	philo->is_full = false;
	DEBUG_PRINT_PURPLE("philo_is_full: %s\n",
		philo->is_full ? "true" : "false");
	philo->data = data;
	handle_mutexes(data->mtx_meal, LOCK);
	data->last_meal[i] = data->simul_start;
	DEBUG_PRINT_PURPLE("Philo #%u - Last meal set to: %ld.%06ld seconds\n",
		philo->philo_id, data->last_meal[i].tv_sec, data->last_meal[i].tv_usec);
	handle_mutexes(data->mtx_meal, UNLOCK);
	DEBUG_PRINT("----------------------------\n");
}

static int	create_threads(t_data *data, pthread_t *thread)
{
	unsigned int	i;
	t_philo			*philos;

	i = -1;
	philos = malloc(data->nbr_of_philo * sizeof(t_philo));
	if (!philos)
		return (1);
	while (++i < data->nbr_of_philo)
	{
		init_philo(&philos[i], i, data);
		handle_threads(&thread[i], &philo_routine, &philos[i], CREATE);
	}
	// handle_threads(&thread[i], &monitor_routine, data, CREATE);
	return (0);
}

static void	create_mutexes(t_data *data, pthread_mutex_t *mtx_forks,
		pthread_mutex_t control_mtx[4])
{
	unsigned int	i;

	i = -1;
	while (++i < 4)
		handle_mutexes(&control_mtx[i], INIT);
	i = -1;
	while (++i < data->nbr_of_philo)
		handle_mutexes(&mtx_forks[i], INIT);
	data->mtx_forks = mtx_forks;
	data->mtx_full = &control_mtx[0];
	data->mtx_meal = &control_mtx[1];
	data->mtx_print = &control_mtx[2];
	data->mtx_death = &control_mtx[3];
	DEBUG_PRINT_GREEN("Success create_mutexes function\n");
}

static void	init_data(t_data *data, int argc, char **argv)
{
	data->nbr_of_philo = atol(argv[1]);
	if (data->nbr_of_philo > PHILO_MAX)
		error_exit("Max number of philosophers has to be under 200");
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	data->time_to_think = 0;
	if (data->time_to_sleep <= data->time_to_eat)
		data->time_to_think = 2 * data->time_to_eat - data->time_to_sleep;
	data->must_eat_count = 0;
	if (argc == 6)
		data->must_eat_count = atol(argv[5]);
	get_current_time(&data->simul_start);
	data->someone_dead = false;
	data->fulled_phils = 0;
	data->last_meal = malloc(data->nbr_of_philo * sizeof(struct timeval));
	if (!data->last_meal) // WARNING: free me
		error_exit("Malloc failed: last_meal @init_data");
	data->mtx_death = NULL;
	data->mtx_print = NULL;
	data->mtx_meal = NULL;
	data->mtx_forks = NULL;
	data->mtx_full = NULL;
	print_validated_data(data);
	DEBUG_PRINT_GREEN("Success init_data function\n");
}

int	main(int argc, char **argv)
{
	t_data			data;
	pthread_t		*philo_threads;
	pthread_mutex_t	*mtx_forks;
	pthread_mutex_t	control_mutexes[4];

	check_input(argc, argv);
	init_data(&data, argc, argv);
	// WARNING: free me
	philo_threads = malloc(data.nbr_of_philo * sizeof(pthread_t));
	if (!philo_threads)
		return (free(data.last_meal), 1);
	DEBUG_PRINT_GREEN("Success mallocing philo_threads\n");
	// WARNING: free me
	mtx_forks = malloc(data.nbr_of_philo * sizeof(pthread_mutex_t));
	if (!mtx_forks)
		return (free(data.last_meal), 1);
	DEBUG_PRINT_GREEN("Success mallocing forks\n");
	create_mutexes(&data, mtx_forks, control_mutexes);
	if (create_threads(&data, philo_threads) != 0)
		philo_mark_dead(&data);
	// NOTE: freeing stuff
	free(philo_threads);
	free(data.last_meal);
	free(mtx_forks);
	// create_threads(&data, philo_threads);
	return (0);
}

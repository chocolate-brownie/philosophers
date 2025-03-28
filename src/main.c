/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:24:17 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/28 17:52:29 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	parsing_input(t_global *data, int argc, char **argv)
{
	if (!control_args(argc))
		error_exit("Wrong argument count");
	else
	{
		data->nbr_of_philo = ft_atol(argv[1]);
		if (data->nbr_of_philo > PHILO_MAX)
			error_exit("Number of philosophers should be less than 200");
		data->time_to_die = ft_atol(argv[2]) * 1e3;
		data->time_to_eat = ft_atol(argv[3]) * 1e3;
		data->time_to_sleep = ft_atol(argv[4]) * 1e3;
		if (data->time_to_die < 6e4 || data->time_to_eat < 6e4
			|| data->time_to_sleep < 6e4)
			error_exit("Timestamps should be major than 60ms");
		if (argv[5])
			data->must_eat_count = ft_atol(argv[5]);
		else
			data->must_eat_count = -1;
	}
}

static void	assign_forks(t_philo *philo, t_fork *forks,
		unsigned int philo_position)
{
	unsigned int	nbr_of_philo;

	nbr_of_philo = philo->global_data->nbr_of_philo;
	if (philo->philo_id % 2 == 0)
	{
		philo->right_fork = &forks[philo_position];
		philo->left_fork = &forks[(philo_position + 1) % nbr_of_philo];
	}
	else
	{
		philo->right_fork = &forks[(philo_position + 1) % nbr_of_philo];
		philo->left_fork = &forks[philo_position];
	}
}

/** @note potential FIXME: bucause of the pointer arithmetic with moving to the next
philosopher */
static void	init_philo(t_global *data)
{
	unsigned int	i;

	data->philos = safe_malloc(sizeof(t_philo) * data->nbr_of_philo);
	i = 0;
	while (i < data->nbr_of_philo)
	{
		data->philos[i].global_data = data;
		data->philos[i].philo_id = i + 1;
		data->philos[i].full = false;
		data->philos[i].meals_count = 0;
		memset(&data->philos[i].last_meal_time, 0, sizeof(struct timeval));
		data->philos[i].thread_id = 0;
		assign_forks(&data->philos[i], data->forks, i);
		i++;
	}
}

static void	init_data(t_global *data)
{
	unsigned int	i;
	int				mtx_result;
	unsigned int	j;

	memset(&data->start_simul, 0, sizeof(struct timeval));
	data->end_simul = false;
	data->forks = safe_malloc(sizeof(t_fork) * data->nbr_of_philo);
	i = -1;
	while (++i < data->nbr_of_philo)
	{
		mtx_result = pthread_mutex_init(&data->forks[i].mtx_fork, NULL);
		if (mtx_result != 0)
		{
			j = -1;
			while (++j < i)
				pthread_mutex_destroy(&data->forks[j].mtx_fork);
			cleanup(data);
			error_exit("initiating forks mutexes");
		}
		data->forks[i].fork_id = i;
	}
	init_philo(data);
}

int	main(int argc, char *argv[])
{
	t_global	data;

	parsing_input(&data, argc, argv);
	init_data(&data);
	simulation(&data);
	// print_data(&data);
	cleanup(&data);
	return (0);
}

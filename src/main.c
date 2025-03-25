/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:24:17 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/25 18:00:10 by mgodawat         ###   ########.fr       */
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

/**WARNING: this function causes potential memory leaks
 * if you create a clean_up function this could cause double free errors
 * */
static void	init_data(t_global *data)
{
	unsigned int	i;
	int				mtx_result;

	memset(&data->start_simul, 0, sizeof(struct timeval));
	data->end_simul = false;
	data->forks = safe_malloc(sizeof(t_fork) * data->nbr_of_philo);
	data->philos = safe_malloc(sizeof(t_philo) * data->nbr_of_philo);
	i = -1;
	while (++i < data->nbr_of_philo)
	{
		mtx_result = pthread_mutex_init(data->forks[i].mtx_fork, NULL);
		if (mtx_result != 0)
		{
			free(data->forks);
			free(data->philos);
			error_exit("initiating mutexes");
		}
		data->forks[i].fork_id = i;
	}
}

int	main(int argc, char *argv[])
{
	t_global	data;

	parsing_input(&data, argc, argv);
	init_data(&data);
	// start_simulation(&data);
}

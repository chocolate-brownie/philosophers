/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:24:17 by mgodawat          #+#    #+#             */
/*   Updated: 2025/02/26 23:03:59 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	init_mutexes(t_data *data)
{
	create_mutex(data->mtx_death, INIT);
	create_mutex(data->mtx_print, INIT);
	create_mutex(data->mtx_meal, INIT);
	create_mutex(data->mtx_forks, INIT);
}

static void	init_philo(t_data *data, int argc, char **argv)
{
	if (argc != 5 || argc != 6)
		error_exit(RED "Invalid argument count" RESET);
	data->nbr_of_philo = atol(argv[1]);
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	if (argv[5])
		data->must_eat_count = atol(argv[5]);
	else
		data->must_eat_count = 1;
	// if (!gettimeofday(&data->simul_start, NULL))
	//     error_exit(RED"gettimeofday failed at init_philo\n"RESET);
	data->someone_dead = false;
	init_mutexes(data);
	// print_validated_data(data);
}

int	main(int argc, char **argv)
{
	t_philo	philo;
	t_data	data;

	init_philo(&data, argc, argv);
	return (0);
}

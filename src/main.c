/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:24:17 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/15 11:18:03 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	start_simulation(t_data *data)
{
	unsigned int	i;

	i = -1;
	get_current_time(&data->simul_start);
	print_box_message("     Simulation    ");
	printf("\n");
	while (++i < data->nbr_of_philo)
		handle_threads(&data->philos[i].philo_thread, start_routine,
			&data->philos[i], CREATE);
	// TODO: create a monitoring thread
	i = -1;
	while (++i < data->nbr_of_philo)
		handle_threads(&data->philos[i].philo_thread, NULL, NULL, JOIN);
}

static void	init_philo(t_philo **philo_ptr, t_data *data)
{
	unsigned int	i;
	t_philo			*philos;

	i = -1;
	// FIXME: free the malloc
	*philo_ptr = safe_malloc(sizeof(t_philo) * data->nbr_of_philo);
	philos = *philo_ptr;
	data->philos = philos;
	while (++i < data->nbr_of_philo)
	{
		ft_memset(&philos[i].last_meal, 0, sizeof(struct timeval));
		philos[i].data = data;
		philos[i].philo_id = i + 1;
		philos[i].meals_eaten = 0;
		philos[i].fork_left = &data->mtx_forks[i];
		philos[i].fork_right = &data->mtx_forks[(i + 1) % data->nbr_of_philo];
		philos[i].status = EATING;
		print_philo_data(&philos[i], i);
	}
}

static void	init_mutexes(t_data *data)
{
	unsigned int	i;

	printf(YELLOW "Creating mutexes...\n\n" RESET);
	handle_mutexes(&data->mtx_death, INIT);
	printf("mtx_death\tINIT\t" GREEN "success\n" RESET);
	handle_mutexes(&data->mtx_print, INIT);
	printf("mtx_print\tINIT\t" GREEN "success\n" RESET);
	handle_mutexes(&data->mtx_meal, INIT);
	printf("mtx_meal\tINIT\t" GREEN "success\n" RESET);
	data->mtx_forks = safe_malloc(sizeof(pthread_mutex_t) * data->nbr_of_philo);
	i = -1;
	while (++i < data->nbr_of_philo)
		handle_mutexes(&data->mtx_forks[i], INIT);
	printf("mtx_forks (%d)\tINIT\t" GREEN "success\n\n" RESET, i);
}

//  TODO: check for valid arguments inside the ft_atol function
//  TODO: make sure you check for the PHILO_MAX 200
static void	init_data(t_data *data, int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		error_exit(RED "Invalid argument count" RESET);
	data->nbr_of_philo = atol(argv[1]);
	if (data->nbr_of_philo > PHILO_MAX)
		error_exit("Max number of philosophers has to be under 200");
	data->time_to_die = atol(argv[2]);
	data->time_to_eat = atol(argv[3]);
	data->time_to_sleep = atol(argv[4]);
	if (argv[5])
		data->must_eat_count = atol(argv[5]);
	else
		data->must_eat_count = 0;
	data->someone_dead = false;
	ft_memset(&data->simul_start, 0, sizeof(struct timeval));
	print_validated_data(data);
	init_mutexes(data);
}

int	main(int argc, char **argv)
{
	t_philo	*philos;
	t_data	data;

	philos = NULL;
	init_data(&data, argc, argv);
	init_philo(&philos, &data);
	start_simulation(&data);
	cleanup(&philos, &data);
	// print_final_state(&data);
	return (0);
}

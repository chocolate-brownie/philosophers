/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:58:53 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/01 21:25:14 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_exit(const char *msg)
{
	printf(RED "[ERROR]: %s\n" RESET, msg);
	exit(EXIT_FAILURE);
}

bool	control_args(int argc)
{
	if (argc > 6 || argc < 5)
	{
		printf("The program should be executed as follows:\n");
		printf("./philo number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (false);
	}
	return (true);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc((bytes));
	if (!ret)
		error_exit("malloc");
	return (ret);
}

void	cleanup(t_global *data)
{
	if (data->forks)
		free(data->forks);
	else if (data->philos)
		free(data->philos);
	pthread_mutex_destroy(&data->mutex_data);
}

bool	simulation_finished(t_global *data)
{
	bool	result;

	result = get_bool(&data->mutex_data, &data->end_simul);
	return (result);
}

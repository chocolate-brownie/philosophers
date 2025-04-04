/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phils_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 19:31:20 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/03 19:55:07 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	init_data(int argc, char *argv[], t_data *data)
{
	data->nbr_of_phils = ft_atol(argv[1]);
	data->time_to_die = ft_atol(argv[2]);
	data->time_to_eat = ft_atol(argv[3]);
	data->time_to_sleep = ft_atol(argv[4]);
	data->time_to_think = 0;
	if (data->time_to_sleep <= data->time_to_eat)
		data->time_to_think = 2 * data->time_to_eat - data->time_to_sleep;
	data->must_eat_times = 0;
	if (argc == 6)
		data->must_eat_times = ft_atol(argv[5]);
	gettimeofday(&data->simul_start, NULL);
	data->philo_died = 0;
	data->fulled_phils = 0;
	data->last_meal = malloc(sizeof(struct timeval) * data->nbr_of_phils);
	if (!data->last_meal)
		return (1);
	data->mtx_fork = NULL;
	data->mtx_full = NULL;
	data->mtx_dead = NULL;
	data->mtx_meal = NULL;
	data->mtx_print = NULL;
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:58:53 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/11 12:48:50 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	control_args(int argc, char *argv[])
{
	int		i;
	long	val;

	if (argc > 6 || argc < 5)
	{
		write(ER, "The program should be executed as follows:\n", 43);
		write(ER, "./philo nbr_of_philosophers time_to_die time_to_eat ", 52);
		write(ER, "time_to_sleep [must_eat_count]\n", 31);
		return (1);
	}
	i = 0;
	while (++i < argc)
	{
		if (!ft_is_valid_int(argv[i], &val) || val < 1)
		{
			write(ER, "Wrong input. Must be positive integers\n", 39);
			return (2);
		}
	}
	return (0);
}

int	check_all_full(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->mtx_full);
	if (data->fulled_phils == data->nbr_of_phils)
		i = 1;
	pthread_mutex_unlock(data->mtx_full);
	return (i);
}

int	check_starved_time(int id, t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->mtx_meal);
	if (elapsed_time(&data->last_meal[id]) > data->time_to_die)
		i = 1;
	pthread_mutex_unlock(data->mtx_meal);
	if (i == 1)
		print_message(data, id + 1, DIED);
	return (i);
}

int	check_sb_dead(t_data *data)
{
	int	i;

	i = 0;
	pthread_mutex_lock(data->mtx_dead);
	if (data->philo_died)
		i = 1;
	pthread_mutex_unlock(data->mtx_dead);
	return (i);
}

void	turn_dead(t_data *data)
{
	pthread_mutex_lock(data->mtx_dead);
	data->philo_died = 1;
	pthread_mutex_unlock(data->mtx_dead);
}

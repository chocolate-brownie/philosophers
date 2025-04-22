/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:58:53 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/11 14:01:46 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	control_args(int argc, char *argv[])
{
	int		i;
	long	val;

	if (argc > 6 || argc < 5)
	{
		write(ER, "[ERROR]: Invalid arguments\n", 27);
		return (1);
	}
	if (!ft_is_valid_int(argv[1], &val) || !is_valid_range(val, 1, UINT16_MAX))
	{
		write(ER, "[ERROR]: Invalid arguments\n", 27);
		return (2);
	}
	i = 1;
	while (++i < argc)
	{
		if (!ft_is_valid_int(argv[i], &val) || !is_valid_range(val, 1,
				UINT32_MAX))
		{
			write(ER, "[ERROR]: Invalid arguments\n", 27);
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

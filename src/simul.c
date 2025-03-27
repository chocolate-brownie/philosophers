/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:00:13 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/27 14:55:16 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

/*
static void	handle_philo_one(t_global *data)
{
	if (data->nbr_of_philo == 1)
	{
		gettimeofday(&data->start_simul, NULL);
		print_state(&data->philos[0], "has taken a fork");
		usleep(data->time_to_die);
		print_state(&data->philos[0], "died");
		data->end_simul = true;
		return ;
	}
}
 */
void	*start_routine(void *arg)
{
	return (NULL);
}

void	simulation(t_global *data)
{
	int				thread_result;
	unsigned int	i;
	unsigned int	j;

	if (data->must_eat_count == 0)
		return ;
	// handle_philo_one(data);
	i = -1;
	while (++i < data->nbr_of_philo)
	{
		thread_result = pthread_create(&data->philos[i].thread_id, NULL,
				&start_routine, &data->philos[i]);
		if (thread_result != 0)
		{
			j = -1;
			while (++j < i)
				pthread_detach(data->philos[j].thread_id);
			cleanup(data);
			error_exit("Creating threads for start_routine");
		}
	}
	i = -1;
	while (++i < data->nbr_of_philo)
		pthread_join(data->philos[i].thread_id, NULL);
}

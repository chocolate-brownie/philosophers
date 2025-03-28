/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simul.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/27 13:00:13 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/28 19:01:25 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	handle_philo_one(t_global *data)
{
	(void)data;
	return ;
}

void	*start_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	wait_all_threads(philo->global_data);
	return (NULL);
}

void	simulation(t_global *data)
{
	int				thread_result;
	unsigned int	i;
	unsigned int	j;

	if (data->must_eat_count == 0)
		return ;
	handle_philo_one(data); // TODO: function
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
	if (!set_bool(&data->mutex_data, &data->all_threads_ready, true))
		return ;
}

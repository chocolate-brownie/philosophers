/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sync_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:00:56 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/30 13:34:41 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	wait_all_threads(t_global *data)
{
	while (!get_bool(&data->mutex_data, &data->all_threads_ready))
		;
}

void	print_status(t_status status, t_philo *philo, bool debug)
{
	long	elapsed_time;

	elapsed_time = get_time(MILLISECONDS) - philo->global_data->start_simul;
	if (philo->full)
		return ;
	pthread_mutex_lock(&philo->global_data->mtx_print);
	if (debug)
		write_status_debug(status, philo, elapsed_time); // TODO:
	else
	{
		if ((status == FORK_ONE || status == FORK_TWO)
			&& (!simulation_finished(philo->global_data)))
			printf(BLUE "%-6ld %d has taken a fork\n" RESET, elapsed_time,
				philo->philo_id);
		else if (status == EATING && (!simulation_finished(philo->global_data)))
			printf(YELLOW "%-6ld %d is eating\n" RESET, elapsed_time,
				philo->philo_id);
		else if (status == THINKING
			&& (!simulation_finished(philo->global_data)))
			printf(PURPLE "%-6ld %d is thinking\n" RESET, elapsed_time,
				philo->philo_id);
		else if (status == SLEEPING
			&& (!simulation_finished(philo->global_data)))
			printf(GREEN "%-6ld %d is sleeping\n" RESET, elapsed_time,
				philo->philo_id);
		else if (status == DIED)
			printf(RED "%-6ld %d died\n" RESET, elapsed_time, philo->philo_id);
	}
	pthread_mutex_unlock(&philo->global_data->mtx_print);
}

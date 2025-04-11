/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/06 17:56:34 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/11 11:54:27 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	philo_one(t_philo *philo, __uint16_t fork_index)
{
	if (philo->data->nbr_of_phils == 1)
	{
		pthread_mutex_unlock(philo->data->mtx_fork + fork_index);
		ft_usleep(philo->data->time_to_die + 10, philo->data);
		return (1);
	}
	return (0);
}

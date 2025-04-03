/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:55:50 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/02 20:24:47 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	set_bool(pthread_mutex_t *mutex_data, bool *dest, bool value)
{
	unsigned int	err_result;

	err_result = pthread_mutex_lock(mutex_data);
	if (err_result != 0)
		error_exit("locking mutex at set_bool");
	*dest = value;
	err_result = pthread_mutex_unlock(mutex_data);
	if (err_result != 0)
		error_exit("unlocking mutex at set_bool");
}

bool	get_bool(pthread_mutex_t *mutex_data, bool *value)
{
	bool			result;
	unsigned int	err_result;

	err_result = pthread_mutex_lock(mutex_data);
	if (err_result != 0)
	{
		write(STDERR_FILENO, "Error: locking mutex at get_bool\n", 33);
		return (false);
	}
	result = *value;
	err_result = pthread_mutex_unlock(mutex_data);
	if (err_result != 0)
	{
		write(STDERR_FILENO, "Error: unlocking mutex at get_bool\n", 35);
		return (false);
	}
	return (result);
}

void	set_long(pthread_mutex_t *mutex_data, long *dest, long value)
{
	unsigned int	err_result;

	err_result = pthread_mutex_lock(mutex_data);
	if (err_result != 0)
		error_exit("locking mutexes at set_long");
	*dest = value;
	err_result = pthread_mutex_unlock(mutex_data);
	if (err_result != 0)
		error_exit("unlocking mutexes at set_long");
}

long	get_long(pthread_mutex_t *mutex_data, long *value)
{
	unsigned int	err_result;
	long			result;

	err_result = pthread_mutex_lock(mutex_data);
	if (err_result != 0)
		write(STDERR_FILENO, "Error: locking mutex at get_long\n", 33);
	result = *value;
	err_result = pthread_mutex_unlock(mutex_data);
	if (err_result != 0)
		write(STDERR_FILENO, "Error: unlocking mutex at get_long\n", 35);
	return (result);
}

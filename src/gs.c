/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gs.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 17:55:50 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/29 17:55:56 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

bool	set_bool(pthread_mutex_t *mutex_data, bool *dest, bool value)
{
	unsigned int	err_result;

	err_result = pthread_mutex_lock(mutex_data);
	if (err_result != 0)
	{
		write(STDERR_FILENO, "Error: locking mutex\n", 21);
		return (false);
	}
	*dest = value;
	err_result = pthread_mutex_unlock(mutex_data);
	if (err_result != 0)
	{
		write(STDERR_FILENO, "Error: unlocking mutex\n", 23);
		return (false);
	}
	return (true);
}

bool	get_bool(pthread_mutex_t *mutex_data, bool *value)
{
	bool			result;
	unsigned int	err_result;

	err_result = pthread_mutex_lock(mutex_data);
	if (err_result != 0)
	{
		write(STDERR_FILENO, "Error: locking mutex\n", 21);
		return (false);
	}
	result = *value;
	err_result = pthread_mutex_unlock(mutex_data);
	if (err_result != 0)
	{
		write(STDERR_FILENO, "Error: unlocking mutex\n", 23);
		return (false);
	}
	return (result);
}

bool	set_long(pthread_mutex_t *mutex_data, long *dest, long value)
{
	unsigned int	err_result;

	err_result = pthread_mutex_lock(mutex_data);
	if (err_result != 0)
	{
		write(STDERR_FILENO, "Error: locking mutex\n", 21);
		return (false);
	}
	*dest = value;
	err_result = pthread_mutex_unlock(mutex_data);
	if (err_result != 0)
	{
		write(STDERR_FILENO, "Error: unlocking mutex\n", 23);
		return (false);
	}
	return (true);
}

long	get_long(pthread_mutex_t *mutex_data, long *value)
{
	unsigned int err_result;
	long result;

	err_result = pthread_mutex_lock(mutex_data);
	if (err_result != 0)
		write(STDERR_FILENO, "Error: locking mutex\n", 21);
	result = *value;
	err_result = pthread_mutex_unlock(mutex_data);
	if (err_result != 0)
		write(STDERR_FILENO, "Error: unlocking mutex\n", 23);
	return (result);
}

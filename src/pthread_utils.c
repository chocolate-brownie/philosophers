/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:58:16 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/07 03:10:03 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	safe_mutex(int status, t_opcode opcode)
{
	if (status == 0)
		return ;
	if (status == EINVAL && (opcode == LOCK || opcode == UNLOCK))
		error_exit("The value specified by mutex is invalid");
	else if (status == EINVAL && opcode == INIT)
		error_exit("The value specified by attr is invalid");
	else if (status == EDEADLK)
		error_exit("A deadlock would occur if the thread blocked waiting for mutex");
	else if (status == EPERM)
		error_exit("The current thread does not hold a lock on mutex");
	else if (status == ENOMEM)
		error_exit("The process cannot allocate enough memory to create another mutex");
	else if (status == EBUSY)
		error_exit("Mutex is locked");
}

void	handle_mutexes(pthread_mutex_t *mutex, t_opcode opcode)
{
	if (opcode == INIT)
		safe_mutex(pthread_mutex_init(mutex, NULL), opcode);
	else if (opcode == DESTROY)
		safe_mutex(pthread_mutex_destroy(mutex), opcode);
	else if (opcode == LOCK)
		safe_mutex(pthread_mutex_lock(mutex), opcode);
	else if (opcode == UNLOCK)
		safe_mutex(pthread_mutex_unlock(mutex), opcode);
	else
		error_exit("Wrong opcode");
}

void	handle_threads(pthread_t *thread, void *(*function_name)(void *),
		void *arg, t_opcode opcode)
{
	int	status;

	if (opcode == CREATE)
	{
		status = pthread_create(thread, NULL, start_routine, arg);
		if (status != 0)
			error_exit("Failed to create thread");
	}
	else if (opcode == JOIN)
	{
		status = pthread_join(*thread, NULL);
		if (status != 0)
			error_exit("Failed to join thread");
	}
	else if (opcode == DETATCH)
	{
		status = pthread_detach(*thread);
		if (status != 0)
			error_exit("Failed to detach thread");
	}
	else
		error_exit("Invalid thread opcode");
}

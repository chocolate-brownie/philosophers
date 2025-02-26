/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pthread_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:58:16 by mgodawat          #+#    #+#             */
/*   Updated: 2025/02/26 23:00:43 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static void	safe_mutex(int status, enum t_opcode opcode)
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

void	create_mutex(pthread_mutex_t *mutex, enum t_opcode opcode)
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sig_exit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/02 22:13:07 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/02 22:30:00 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"
#include <signal.h>

static t_global	*data_ptr = NULL;

void	sigint_handler(int sig)
{
	(void)sig;
	if (data_ptr)
	{
		pthread_mutex_lock(&data_ptr->mutex_data);
		data_ptr->end_simul = true;
		pthread_mutex_unlock(&data_ptr->mutex_data);
		printf(RED "\nshutting down...\n" RESET);
	}
}

void	setup_signal_handling(t_global *data)
{
	data_ptr = data;
	signal(SIGINT, sigint_handler);
}

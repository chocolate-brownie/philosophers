/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:58:53 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/27 13:28:44 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_exit(const char *msg)
{
	printf(RED "[ERROR]: %s\n" RESET, msg);
	exit(EXIT_FAILURE);
}

bool	control_args(int argc)
{
	if (argc > 6 || argc < 5)
	{
		printf("The program should be executed as follows:\n");
		printf("./philo number_of_philosophers time_to_die time_to_eat ");
		printf("time_to_sleep [number_of_times_each_philosopher_must_eat]\n");
		return (false);
	}
	return (true);
}

void	*safe_malloc(size_t bytes)
{
	void	*ret;

	ret = malloc((bytes));
	if (!ret)
		error_exit("malloc");
	return (ret);
}

void	cleanup(t_global *data)
{
	if (data->forks)
		free(data->forks);
	else if (data->philos)
		free(data->philos);
}

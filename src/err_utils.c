/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:58:53 by mgodawat          #+#    #+#             */
/*   Updated: 2025/04/03 19:16:15 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_exit(const char *msg)
{
	printf(RED "[ERROR]: %s\n" RESET, msg);
	exit(EXIT_FAILURE);
}

int	control_args(int argc)
{
	if (argc > 6 || argc < 5)
	{
		write(ER, "The program should be executed as follows:\n", 43);
		write(ER, "./philo nbr_of_philosophers time_to_die time_to_eat ", 52);
		write(ER, "time_to_sleep [must_eat_count]\n", 31);
		return (1);
	}
	return (0);
}

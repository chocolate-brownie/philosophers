/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/21 20:24:17 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/25 15:09:08 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

static bool	control_args(int argc)
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

int	main(int argc, char *argv[])
{
	t_global	data;

	(void)data;
	(void)argv;
	if (!control_args(argc))
		error_exit("Wrong argument count");
	// parsing_input(&data, argc, argv);
	/* init_data(&data);
	start_simulation(&data); */
}

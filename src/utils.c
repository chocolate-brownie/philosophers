/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 08:09:18 by mgodawat          #+#    #+#             */
/*   Updated: 2025/02/26 22:43:31 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_exit(const char *error_msg)
{
	if (error_msg)
		printf(RED "ERROR: %s\n" RESET, error_msg);
	exit(EXIT_FAILURE);
}

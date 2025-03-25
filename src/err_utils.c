/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   err_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 10:58:53 by mgodawat          #+#    #+#             */
/*   Updated: 2025/03/25 15:03:48 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	error_exit(const char *msg)
{
	printf(RED "[ERROR]: %s\n" RESET, msg);
	exit(EXIT_FAILURE);
}

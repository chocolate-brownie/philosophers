/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgodawat <mgodawat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 06:45:37 by mgodawat          #+#    #+#             */
/*   Updated: 2025/02/23 19:09:04 by mgodawat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

#define TOP_LEFT "╔"
#define TOP_RIGHT "╗"
#define BOTTOM_LEFT "╚"
#define BOTTOM_RIGHT "╝"
#define HORIZONTAL "═"
#define VERTICAL "║"

static void	print_box_message(const char *msg)
{
	int	i;
	printf(GREEN);
	printf("%s", TOP_LEFT);
	i = -1;
	while (++i < 25)
		printf("%s", HORIZONTAL);
	printf("%s\n", TOP_RIGHT);
	printf("%s   %s   %s\n", VERTICAL, msg, VERTICAL);
	printf("%s", BOTTOM_LEFT);
	i = -1;
	while (++i < 25)
		printf("%s", HORIZONTAL);
	printf("%s\n", BOTTOM_RIGHT);
	printf(RESET);
}

void	print_validated_data(t_philo *philo)
{
	printf("\n");
	print_box_message("  Input successful ");
	printf("\n");
    printf("Number of philosophers: "YELLOW"%u"RESET, philo->data->nbr_of_philo);
    printf("Number of philosophers: "YELLOW"%u"RESET, philo->data->nbr_of_philo);
	print_box_message("      Routine      ");
}

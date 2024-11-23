/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:52:59 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/23 15:29:46 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	whats_the_time(struct timeval start_time)
{
	struct timeval	temp;

	gettimeofday(&temp, NULL);
	return (((temp.tv_usec - start_time.tv_usec) / 1000 + \
		(temp.tv_sec - start_time.tv_sec) * 1000));
}

void	sleep_ms(long int sleep_ms, t_philos *philos)
{
	size_t	start_time;

	start_time = whats_the_time(philos->env->start_time);
	while (check_dead(philos) == 0 && whats_the_time(philos->env->start_time) - \
			start_time < (unsigned long)sleep_ms)
		usleep(50);
}

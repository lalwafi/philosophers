/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:52:59 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/07 18:30:54 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	whats_the_time(struct timeval start_time)
{
	struct timeval	temp;

	gettimeofday(&temp, NULL);
	return (((temp.tv_usec - start_time.tv_usec)/1000 + \
		(temp.tv_sec - start_time.tv_sec)*1000));
}

void	sleep_ms(long int sleep_ms)
{
	struct timeval	temp;
	struct timeval	start;

	gettimeofday(&temp, NULL);
	gettimeofday(&start, NULL);
	while (((temp.tv_usec - start.tv_usec)/1000 + \
		(temp.tv_sec - start.tv_sec)*1000) < sleep_ms)
	{
		usleep(100);
		gettimeofday(&temp, NULL);
	}
}

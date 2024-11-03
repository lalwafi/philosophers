/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:52:59 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/03 14:53:32 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

size_t	whats_the_time(struct timeval start_time)
{
	// printf("%ld\n", start_time.tv_sec);
	struct timeval	temp;
	gettimeofday(&temp, NULL);
	while (((temp.tv_usec - start_time.tv_usec)/1000 + \
		(temp.tv_sec - start_time.tv_sec)*1000) < 700)
	{
		usleep(100);
		gettimeofday(&temp, NULL);
	}
	// printf("%ld\n", ((temp.tv_usec - start_time.tv_usec)/1000 + (temp.tv_sec - start_time.tv_sec)*1000));
	return (((temp.tv_usec - start_time.tv_usec)/1000 + \
		(temp.tv_sec - start_time.tv_sec)*1000));
}

void	sleep_ms(struct timeval start_time, long int sleep_ms)
{
	gettimeofday(&start_time, NULL);
	// printf("%ld\n", start_time.tv_sec);
	struct timeval	temp;
	gettimeofday(&temp, NULL);
	while (((temp.tv_usec - start_time.tv_usec)/1000 + \
		(temp.tv_sec - start_time.tv_sec)*1000) < sleep_ms)
	{
		usleep(100);
		gettimeofday(&temp, NULL);
	}
	// printf("%ld\n", ((temp.tv_usec - start_time.tv_usec)/1000 + (temp.tv_sec - start_time.tv_sec)*1000));
}

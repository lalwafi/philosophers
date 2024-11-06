/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 04:02:27 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/05 04:22:34 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_fork(t_philos **philos)
{
	if ((*philos)->index != 0)
	{
		if ((*philos)->left_fork == 0 && (*philos)->env.forks[(*philos)->index] == 0 && (*philos)->env.forks[(*philos)->index - 1] == 0)
		{
			pthread_mutex_lock(&(*philos)->env.lock);
			(*philos)->env.forks[(*philos)->index] = 1;
			(*philos)->env.forks[(*philos)->index - 1] = 1;
			(*philos)->left_fork = 1;
			(*philos)->right_fork = 1;
			pthread_mutex_unlock(&(*philos)->env.lock);
		}
	}
	if ((*philos)->index == 0)
	{
		if ((*philos)->left_fork == 0 && (*philos)->env.forks[0] == 0 && (*philos)->env.forks[(*philos)->env.nop - 1] == 0)
		{
			pthread_mutex_lock(&(*philos)->env.lock);
			(*philos)->env.forks[0] = 1;
			(*philos)->env.forks[(*philos)->env.nop - 1] = 1;
			(*philos)->left_fork = 1;
			(*philos)->right_fork = 1;
			pthread_mutex_unlock(&(*philos)->env.lock);
		}
	}
}

// 0  1  2  3  4
// 0  0  1  2  3
// 4  1  2  3  4

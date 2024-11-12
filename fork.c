/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 04:02:27 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/12 18:22:02 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philos **philo)
{
	printf("take forks maybe\n");
	if ((*philo)->index != 0)
	{
		if ((*philo)->env->forks[(*philo)->index] == 0 && (*philo)->env->forks[(*philo)->index - 1] == 0)
		{
			pthread_mutex_lock(&(*philo)->env->fork_lock);
			(*philo)->env->forks[(*philo)->index] = 1;
			(*philo)->env->forks[(*philo)->index - 1] = 1;
			(*philo)->left_fork = 1;
			(*philo)->right_fork = 1;
			print_smth(*philo, 'f');
			print_smth(*philo, 'f');
			pthread_mutex_unlock(&(*philo)->env->fork_lock);
		}
	}
	else if ((*philo)->index == 0)
	{
		if ((*philo)->env->forks[0] == 0 && (*philo)->env->forks[(*philo)->env->nop - 1] == 0)
		{
			pthread_mutex_lock(&(*philo)->env->fork_lock);
			(*philo)->env->forks[0] = 1;
			(*philo)->env->forks[(*philo)->env->nop - 1] = 1;
			(*philo)->left_fork = 1;
			(*philo)->right_fork = 1;
			print_smth(*philo, 'f');
			print_smth(*philo, 'f');
			pthread_mutex_unlock(&(*philo)->env->fork_lock);
		}
	}
}

void	drop_forks(t_philos **philo)
{
	printf("drop forks maybe\n");
	if ((*philo)->index != 0)
	{
		if ((*philo)->env->forks[(*philo)->index] == 1 && \
			(*philo)->env->forks[(*philo)->index - 1] == 1)
		{
			pthread_mutex_lock(&(*philo)->env->fork_lock);
			(*philo)->env->forks[(*philo)->index] = 0;
			(*philo)->env->forks[(*philo)->index - 1] = 0;
			(*philo)->left_fork = 0;
			(*philo)->right_fork = 0;
			pthread_mutex_unlock(&(*philo)->env->fork_lock);
		}
	}
	else if ((*philo)->index == 0)
	{
		if ((*philo)->env->forks[0] == 1 && \
			(*philo)->env->forks[(*philo)->env->nop - 1] == 1)
		{
			pthread_mutex_lock(&(*philo)->env->fork_lock);
			(*philo)->env->forks[0] = 0;
			(*philo)->env->forks[(*philo)->env->nop - 1] = 0;
			(*philo)->left_fork = 0;
			(*philo)->right_fork = 0;
			pthread_mutex_unlock(&(*philo)->env->fork_lock);
		}
	}
}

// 0  1  2  3  4
// 0  0  1  2  3
// 4  1  2  3  4

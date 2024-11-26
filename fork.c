/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 04:02:27 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/26 17:27:25 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks_left(t_philos **philo)
{
	pthread_mutex_lock(&(*philo)->env->fork_locks[(*philo)->index]);
	if ((*philo)->env->forks[(*philo)->index] == 0 && \
		(*philo)->left_fork == 0)
	{
		(*philo)->env->forks[(*philo)->index] = 1;
		(*philo)->left_fork = 1;
		print_smth(*philo, 'f');
	}
	pthread_mutex_unlock(&(*philo)->env->fork_locks[(*philo)->index]);
}

void	take_forks_right(t_philos **philo)
{
	if ((*philo)->index != 0 && (*philo)->left_fork == 1)
	{
		pthread_mutex_lock(&(*philo)->env->fork_locks[(*philo)->index - 1]);
		if ((*philo)->right_fork == 0 && \
			(*philo)->env->forks[(*philo)->index - 1] == 0)
		{
			(*philo)->env->forks[(*philo)->index - 1] = 1;
			(*philo)->right_fork = 1;
			print_smth(*philo, 'f');
		}
		pthread_mutex_unlock(&(*philo)->env->fork_locks[(*philo)->index - 1]);
	}
	else if ((*philo)->index == 0 && (*philo)->left_fork == 1)
	{
		pthread_mutex_lock(&(*philo)->env->fork_locks[(*philo)->env->nop - 1]);
		if ((*philo)->right_fork == 0 && \
			(*philo)->env->forks[(*philo)->env->nop - 1] == 0)
		{
			(*philo)->env->forks[(*philo)->env->nop - 1] = 1;
			(*philo)->right_fork = 1;
			print_smth(*philo, 'f');
		}
		pthread_mutex_unlock(&(*philo)->env->\
			fork_locks[(*philo)->env->nop - 1]);
	}
}

void	drop_forks(t_philos **philo)
{
	if ((*philo)->index != 0 && (*philo)->env->forks[(*philo)->index] == 1 && \
		(*philo)->env->forks[(*philo)->index - 1] == 1)
	{
		pthread_mutex_lock(&(*philo)->env->fork_locks[(*philo)->index]);
		pthread_mutex_lock(&(*philo)->env->fork_locks[(*philo)->index - 1]);
		(*philo)->env->forks[(*philo)->index] = 0;
		(*philo)->env->forks[(*philo)->index - 1] = 0;
		(*philo)->left_fork = 0;
		(*philo)->right_fork = 0;
		pthread_mutex_unlock(&(*philo)->env->fork_locks[(*philo)->index - 1]);
		pthread_mutex_unlock(&(*philo)->env->fork_locks[(*philo)->index]);
	}
	else if ((*philo)->index == 0 && (*philo)->env->forks[0] == 1 && \
		(*philo)->env->forks[(*philo)->env->nop - 1] == 1)
	{
		pthread_mutex_lock(&(*philo)->env->fork_locks[(*philo)->env->nop - 1]);
		pthread_mutex_lock(&(*philo)->env->fork_locks[0]);
		(*philo)->env->forks[0] = 0;
		(*philo)->env->forks[(*philo)->env->nop - 1] = 0;
		(*philo)->left_fork = 0;
		(*philo)->right_fork = 0;
		pthread_mutex_unlock(&(*philo)->env->fork_locks[0]);
		pthread_mutex_unlock(&(*philo)->env->\
			fork_locks[(*philo)->env->nop - 1]);
	}
}

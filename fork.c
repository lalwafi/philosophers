/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fork.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 04:02:27 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/24 00:29:55 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	take_forks(t_philos **philo)
{
	if ((*philo)->index != 0)
		take_not_zero(philo);
	else if ((*philo)->index == 0)
	{
		pthread_mutex_lock(&(*philo)->env->fork_locks[0]);
		pthread_mutex_lock(&(*philo)->env->fork_locks[(*philo)->env->nop - 1]);
		if ((*philo)->env->forks[0] == 0 && \
			(*philo)->env->forks[(*philo)->env->nop - 1] == 0)
		{
			(*philo)->env->forks[0] = 1;
			(*philo)->env->forks[(*philo)->env->nop - 1] = 1;
			(*philo)->left_fork = 1;
			(*philo)->right_fork = 1;
			pthread_mutex_lock(&(*philo)->env->print_lock);
			ft_printf("%d %d has taken a fork\n", \
			(int)whats_the_time((*philo)->env->start_time), ((*philo)->index + 1));
			ft_printf("%d %d has taken a fork\n", \
			(int)whats_the_time((*philo)->env->start_time), ((*philo)->index + 1));
			pthread_mutex_unlock(&(*philo)->env->print_lock);
		}
		pthread_mutex_unlock(&(*philo)->env->\
			fork_locks[(*philo)->env->nop - 1]);
		pthread_mutex_unlock(&(*philo)->env->fork_locks[0]);
	}
}

void	take_not_zero(t_philos **philo)
{
	pthread_mutex_lock(&(*philo)->env->fork_locks[(*philo)->index - 1]);
	pthread_mutex_lock(&(*philo)->env->fork_locks[(*philo)->index]);
	if ((*philo)->env->forks[(*philo)->index] == 0 && \
		(*philo)->env->forks[(*philo)->index - 1] == 0)
	{
		(*philo)->env->forks[(*philo)->index] = 1;
		(*philo)->env->forks[(*philo)->index - 1] = 1;
		(*philo)->left_fork = 1;
		(*philo)->right_fork = 1;
		pthread_mutex_lock(&(*philo)->env->print_lock);
		ft_printf("%d %d has taken a fork\n", \
		(int)whats_the_time((*philo)->env->start_time), ((*philo)->index + 1));
		ft_printf("%d %d has taken a fork\n", \
		(int)whats_the_time((*philo)->env->start_time), ((*philo)->index + 1));
		pthread_mutex_unlock(&(*philo)->env->print_lock);
	}
	pthread_mutex_unlock(&(*philo)->env->fork_locks[(*philo)->index]);
	pthread_mutex_unlock(&(*philo)->env->fork_locks[(*philo)->index - 1]);
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
		pthread_mutex_lock(&(*philo)->env->fork_locks[0]);
		pthread_mutex_lock(&(*philo)->env->fork_locks[(*philo)->env->nop - 1]);
		(*philo)->env->forks[0] = 0;
		(*philo)->env->forks[(*philo)->env->nop - 1] = 0;
		(*philo)->left_fork = 0;
		(*philo)->right_fork = 0;
		pthread_mutex_unlock(&(*philo)->env->\
			fork_locks[(*philo)->env->nop - 1]);
		pthread_mutex_unlock(&(*philo)->env->fork_locks[0]);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:36:21 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/07 21:10:23 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*process(void *ptr)
{
	t_philos	*philo;

	philo = ptr;
	if ((philo->index % 2) == 0)
		sleep_ms(philo->env->tte / 2, philo);
	while (check_dead(philo) == 0 && philo->env->dead == 0 && philo->meals < philo->env->meal_count)
	{
		while (philo->left_fork == 0 && philo->right_fork == 0 && \
			philo->env->dead == 0 && check_dead(philo) == 0)
			take_forks(&philo);
		if (check_dead(philo) == 1 || philo->env->dead == 1)
			break ;
		eat(&philo);
		if (philo->meals >= philo->env->meal_count)
			break ;
		print_smth(philo, 's');
		sleep_ms(philo->env->tts, philo);
		if (check_dead(philo) == 1 || philo->env->dead == 1)
			break ;
		print_smth(philo, 't');
		usleep(100);
		// printf("dead = %d\n", philo->env->dead);
	}
	// printf("%d meals = %d\n", philo->index + 1, philo->meals);
	return (NULL);
}

void	eat(t_philos **philo)
{
	if (check_dead(*philo) == 1)
		return ;
	print_smth((*philo), 'e');
	(*philo)->meals++;
	sleep_ms((*philo)->env->tte, (*philo));
	if (check_dead(*philo) == 1)
		return ;
	gettimeofday(&(*philo)->last_meal, NULL);
	if (check_dead(*philo) == 1)
		return ;
	drop_forks(philo);
}

int	check_dead(t_philos *philo)
{
	pthread_mutex_lock(&philo->env->lock);
	pthread_mutex_lock(&philo->check_lock);
	pthread_mutex_lock(&philo->print_lock);
	if (philo->env->dead == 1)
	{
		philo->env->dead = 1;
		pthread_mutex_unlock(&philo->env->lock);
		pthread_mutex_unlock(&philo->print_lock);
		pthread_mutex_unlock(&philo->check_lock);
		return (1);
	}
	else if (whats_the_time(philo->last_meal) \
		> philo->env->ttd)
	{
		philo->dead_alive = 1;
		philo->env->dead = 1;
		print_smth(philo, 'd');
		pthread_mutex_unlock(&philo->env->lock);
		pthread_mutex_unlock(&philo->check_lock);
		pthread_mutex_unlock(&philo->print_lock);
		return (1);
	}
	// printf("check death maybe\n");
	pthread_mutex_unlock(&philo->print_lock);
	pthread_mutex_unlock(&philo->env->lock);
	pthread_mutex_unlock(&philo->check_lock);
	return	(0);
}

void	print_smth(t_philos *philo, char c)
{
	pthread_mutex_lock(&philo->print_lock);
	if (c == 'f' && philo->env->dead == 0)
		printf("\e[33m%ld %d has taken a fork\e[0m\n", \
			whats_the_time(philo->env->start_time), (philo->index + 1));
	else if (c == 'e' && philo->env->dead == 0)
		printf("\e[32m%ld %d is eating\e[0m\n", \
			whats_the_time(philo->env->start_time), (philo->index + 1));
	else if (c == 's' && philo->env->dead == 0)
		printf("\e[36m%ld %d is sleeping\e[0m\n", \
			whats_the_time(philo->env->start_time), (philo->index + 1));
	else if (c == 't' && philo->env->dead == 0)
		printf("\e[35m%ld %d is thinking\e[0m\n", \
			whats_the_time(philo->env->start_time), (philo->index + 1));
	else if (c == 'd')
		printf("\e[31m%ld %d died\e[0m\n", \
			whats_the_time(philo->env->start_time), (philo->index + 1));
	pthread_mutex_unlock(&philo->print_lock);
}
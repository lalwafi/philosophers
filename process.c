/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:36:21 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/07 18:37:08 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*process(void *ptr)
{
	t_philos	*philo;

	philo = ptr;
	if ((philo->index % 2) == 0)
		sleep_ms(philo->env.tte / 2);
	while (check_dead(philo) == 0 && philo->env.dead == 0)
	{
		printf("is it working\n");
		while (philo->left_fork == 0 && philo->right_fork == 0)
			take_forks(&philo);
		if (check_dead(philo) == 1 || philo->env.dead == 1)
			break ;
		eat(&philo);
		sleep_ms(philo->env.tts);
		
	}
	return (NULL);
}

void	eat(t_philos **philo)
{
	if (check_dead(*philo) == 1)
		return ;
	print_smth((*philo), 'e');
	sleep_ms((*philo)->env.tte);
	if (check_dead(*philo) == 1)
		return ;
	gettimeofday(&(*philo)->last_meal, NULL);
	if (check_dead(*philo) == 1)
		return ;
}

int	check_dead(t_philos *philo)
{
	pthread_mutex_lock(&philo->env.lock);
	pthread_mutex_lock(&philo->check_lock);
	if ((whats_the_time(philo->env.start_time)	\
		- ((philo->last_meal.tv_sec + philo->last_meal.tv_usec) * 1000)) \
		> philo->env.ttd)
	{
		printf("this?\n");
		philo->dead_alive = 1;
		philo->env.dead = 1;
		pthread_mutex_unlock(&philo->env.lock);
		pthread_mutex_unlock(&philo->check_lock);
		return (1);
	}
	else if (philo->env.dead == 1)
	{
		pthread_mutex_unlock(&philo->env.lock);
		pthread_mutex_unlock(&philo->check_lock);
		return (1);
	}
	printf("check death maybe\n");
	pthread_mutex_unlock(&philo->env.lock);
	pthread_mutex_unlock(&philo->check_lock);
	return	(0);
}

void	print_smth(t_philos *philo, char c)
{
	pthread_mutex_lock(&philo->print_lock);
	if (c == 'f')
		printf("%ld %d has taken a fork\n", \
			whats_the_time(philo->env.start_time), philo->index);
	else if (c == 'e')
		printf("%ld %d is eating\n", \
			whats_the_time(philo->env.start_time), philo->index);
	else if (c == 's')
		printf("%ld %d is sleeping\n", \
			whats_the_time(philo->env.start_time), philo->index);
	else if (c == 't')
		printf("%ld %d is thinking\n", \
			whats_the_time(philo->env.start_time), philo->index);
	else if (c == 'd')
		printf("%ld %d died\n", \
			whats_the_time(philo->env.start_time), philo->index);
	else
		printf("U SENT A WEIRD CHAR TO PRINT_SMTH!!!!!!\n");
	pthread_mutex_unlock(&philo->print_lock);
}
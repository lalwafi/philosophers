/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:53:42 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/22 18:08:07 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	init_env(t_env *env, char **av, int ac)
{
	int	i;

	i = -1;
	if (is_it_max(env, av, ac) == 1)
		return (1);
	env->dead = 0;
	if (init_mutex(env) == 1)
		return (1);
	gettimeofday(&env->start_time, NULL);
	env->forks = malloc(sizeof(int) * env->nop);
	if (!env->forks)
		return (1);
	while (++i < env->nop)
		env->forks[i] = 0;
	return (0);
}

int	is_it_max(t_env *env, char **av, int ac)
{
	int valid;

	valid = 1;
	env->nop = ft_atoi(av[1], &valid);
	env->ttd = ft_atoi(av[2], &valid);
	env->tte = ft_atoi(av[3], &valid);
	env->tts = ft_atoi(av[4], &valid);
	if (ac == 6)
		env->meal_count = ft_atoi(av[5], &valid);
	else
		env->meal_count = -1;
	if (valid == 0)
		return (printf("Overflow\n"), 1);
	return (0);
}

int	init_mutex(t_env *env)
{
	int	i;

	i = -1;
	if (pthread_mutex_init(&env->print_lock, NULL))
		return (printf("mutex error\n"), 1);
	if (pthread_mutex_init(&env->check_lock, NULL))
	{
		pthread_mutex_destroy(&env->print_lock);
		return (printf("mutex error\n"), 1);
	}
	env->fork_locks = malloc(sizeof(pthread_mutex_t) * env->nop);
	while (++i < env->nop)
	{
		if (pthread_mutex_init(&env->fork_locks[i], NULL))
			return (free_all(NULL, (*env)),\
				printf("mutex error\n"), 1);
	}
	return (0);
}

t_philos	**init_philos(t_env *env)
{
	t_philos	**philos;
	int			i;

	i = -1;
	philos = malloc(sizeof(t_philos *) * (env->nop));
	if (!philos)
		return (NULL);
	while (++i < env->nop)
	{
		philos[i] = malloc(sizeof(t_philos));
		if (!philos[i])
		{
			while (--i >= 0)
				free(philos[i]);
			free(philos);
		}
		philos[i]->index = i;
		philos[i]->dead_alive = 0;
		gettimeofday(&philos[i]->last_meal, NULL);
		philos[i]->meals = 0;
		philos[i]->left_fork = 0;
		philos[i]->right_fork = 0;
		philos[i]->env = env;
	}
	return (philos);
}

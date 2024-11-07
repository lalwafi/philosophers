/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:53:42 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/07 17:21:03 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_env(t_env *env, char **av, int ac)
{
	int	i;

	i = -1;
	env->nop = ft_atoi(av[1]);
	env->ttd = ft_atoi(av[2]);
	env->tte = ft_atoi(av[3]);
	env->tts = ft_atoi(av[4]);
	env->dead = 0;
	if (pthread_mutex_init(&env->lock, NULL))
		exit(EXIT_FAILURE);
	gettimeofday(&env->start_time, NULL);
	if (ac == 6)
		env->meal_count = ft_atoi(av[5]);
	else
		env->meal_count = -1;
	env->forks = malloc(sizeof(int) * env->nop);
	while (++i < env->nop)
		env->forks[i] = 0;
}

t_philos	**init_philos(t_env env)
{
	t_philos	**philos;
	int			i;

	i = -1;
	philos = malloc(sizeof(t_philos *) * (env.nop));
	if (!philos)
		return (NULL);
	while (++i < env.nop)
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

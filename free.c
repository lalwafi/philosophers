/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:08:45 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/25 20:13:51 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philos **philos, t_env env)
{
	int	i;

	i = env.nop;
	if (philos)
	{
		while (--i >= 0)
			free(philos[i]);
		free(philos);
	}
	if (env.forks)
		free(env.forks);
	pthread_mutex_destroy(&env.print_lock);
	pthread_mutex_destroy(&env.check_lock);
	pthread_mutex_destroy(&env.lock);
	if (env.fork_locks)
	{
		i = env.nop;
		while (--i >= 0)
			pthread_mutex_destroy(&env.fork_locks[i]);
		free(env.fork_locks);
	}
}

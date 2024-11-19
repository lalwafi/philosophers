/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:08:45 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/19 17:29:09 by lalwafi          ###   ########.fr       */
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
	pthread_mutex_destroy(&env.lock);
	pthread_mutex_destroy(&env.fork_lock);
	pthread_mutex_destroy(&env.print_lock);
	pthread_mutex_destroy(&env.check_lock);
}

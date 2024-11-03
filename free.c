/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/03 14:08:45 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/03 14:10:18 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	free_all(t_philos **philos, t_env env)
{
	int	i;

	i = env.nop;
	while (--i >= 0)
		free(philos[i]);
	free(philos);
	free(env.forks);
}
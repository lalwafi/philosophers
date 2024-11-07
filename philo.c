/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:35:35 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/07 18:00:45 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	check_args(char **av, int ac)
{
	int	i;
	int	j;

	i = 1;
	j = -1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) <= 0)
		{
			printf("should be positive integers\n");
			exit(EXIT_FAILURE);
		}
		while (av[i][++j])
		{
			if (ft_isdigit(av[i][j]) == 0)
			{
				printf("only integers pls\n");
				exit(EXIT_FAILURE);
			}
		}
		j = -1;
		i++;
	}
}

// void	*run_em(void *idk)
// {
// 	t_philos *philos = idk;
	
// 	if (philos->index % 2 == 0)
// 		sleep_ms(200);
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philos->env.lock);
// 		printf("%d - %ld\n", philos->index, whats_the_time(philos->env.start_time));
// 		take_forks(&philos);
// 		pthread_mutex_unlock(&philos->env.lock);
// 		sleep_ms(200);
// 	}
// 	return (NULL);
// }

void	create_them_threads(t_philos **philos, int nop)
{
	int	i;

	i = -1;
	while (++i < nop)
	{
		pthread_create(&philos[i]->thread_id, NULL, process, philos[i]);
	}
	i = -1;
	while (++i < nop)
		pthread_join(philos[i]->thread_id, NULL);
}

void	one_philo(char **av)
{
	struct timeval	start;

	gettimeofday(&start, NULL);
	printf("%ld 1 has taken a fork\n", whats_the_time(start));
	sleep_ms(ft_atoi(av[2]));
	printf("%ld 1 died\n", whats_the_time(start));
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_env 		env;
	t_philos	**philos;

	if (ac < 5 || ac > 6)
		(printf("%s\n", ARGERROR), exit(EXIT_FAILURE));
	check_args(av, ac);
	if (ft_atoi(av[1]) == 1)
		one_philo(av);
	init_env(&env, av, ac);
	philos = init_philos(env);
	if (!philos)
		(free(env.forks), exit(EXIT_FAILURE));
	create_them_threads(philos, env.nop);
	// whats_the_time(&env);
	printf("%d, %d, %d, %d, %d\n", env.nop, env.ttd, env.tte, env.tts, env.meal_count);
	free_all(philos, env);
}

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

// parse first, then make the processes, then start eating and all, then free stuff
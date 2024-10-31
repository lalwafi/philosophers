/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:35:35 by lalwafi           #+#    #+#             */
/*   Updated: 2024/10/31 17:41:02 by lalwafi          ###   ########.fr       */
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
	if (ac == 6)
		env->meal_count = ft_atoi(av[5]);
	else
		env->meal_count = -1;
	env->forks = malloc(sizeof(int) * env->nop);
	while (++i < env->nop)
		env->forks[i] = 0;
}

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

void	run_em(t_philos	**philos, )
{
	
}

void	create_them_threads(t_philos **philos, int nop)
{
	int	i;

	i = 0;
	while (--i )
	{
		pthread_create(&philos[i]->thread_id, NULL, run_em, &philos[i]);
	}
}

void	whats_the_time(t_env *env)
{
	gettimeofday(&env->start_time, NULL);
	// printf("%ld\n", env->start_time.tv_sec);
	struct timeval	temp;
	gettimeofday(&temp, NULL);
	while (((temp.tv_usec - env->start_time.tv_usec)/1000 + \
		(temp.tv_sec - env->start_time.tv_sec)*1000) < 700)
	{
		usleep(100);
		gettimeofday(&temp, NULL);
	}
	printf("%ld\n", ((temp.tv_usec - env->start_time.tv_usec)/1000 + \
		(temp.tv_sec - env->start_time.tv_sec)*1000));
}

int	main(int ac, char **av)
{
	t_env env;
	t_philos	**philos;
	(void)philos;
	if (ac < 5 || ac > 6)
		(printf("%s\n", ARGERROR), exit(EXIT_FAILURE));
	check_args(av, ac);
	init_env(&env, av, ac);
	// create_them_threads(philos, env.nop);
	whats_the_time(&env);
	printf("%d, %d, %d, %d, %d\n", env.nop, env.ttd, env.tte, env.tts, env.meal_count);
	free(env.forks);
}

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

// parse first, then make the processes, then start eating and all, then free stuff
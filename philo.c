/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:35:35 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/02 11:22:19 by lalwafi          ###   ########.fr       */
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

void	init_philos(t_philos **philos, t_env env)
{
	int	i;

	i = -1;
	philos = malloc(sizeof(t_philos) * (env.nop + 1));
	while (++i < env.nop)
	{
		philos[i]->index = i;
		philos[i]->meals = 0;
		philos[i]->left_fork = 0;
		philos[i]->right_fork = 0;
		philos[i]->env = env;
	}
	philos[i] = NULL;
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

void	*run_em(void *idk)
{
	int	i = 10;
	t_philos *philos = idk;
	while (--i > 0)
	{
		printf("%d - %ld\n", i, whats_the_time(philos->env.start_time));
		sleep_ms(philos->env.start_time, 200);
	}
	return (NULL);
}

void	create_them_threads(t_philos **philos, int nop)
{
	int	i;

	i = -1;
	while (++i < nop)
	{
		pthread_create(&philos[i]->thread_id, NULL, run_em, &philos[i]);
	}
	i = -1;
	while (++i < nop)
		pthread_join(philos[i]->thread_id, NULL);
}

size_t	whats_the_time(struct timeval start_time)
{
	gettimeofday(&start_time, NULL);
	// printf("%ld\n", start_time.tv_sec);
	struct timeval	temp;
	gettimeofday(&temp, NULL);
	while (((temp.tv_usec - start_time.tv_usec)/1000 + \
		(temp.tv_sec - start_time.tv_sec)*1000) < 700)
	{
		usleep(100);
		gettimeofday(&temp, NULL);
	}
	// printf("%ld\n", ((temp.tv_usec - start_time.tv_usec)/1000 + (temp.tv_sec - start_time.tv_sec)*1000));
	return (((temp.tv_usec - start_time.tv_usec)/1000 + \
		(temp.tv_sec - start_time.tv_sec)*1000));
}

void	sleep_ms(struct timeval start_time, long int sleep_ms)
{
	gettimeofday(&start_time, NULL);
	// printf("%ld\n", start_time.tv_sec);
	struct timeval	temp;
	gettimeofday(&temp, NULL);
	while (((temp.tv_usec - start_time.tv_usec)/1000 + \
		(temp.tv_sec - start_time.tv_sec)*1000) < sleep_ms)
	{
		usleep(100);
		gettimeofday(&temp, NULL);
	}
	// printf("%ld\n", ((temp.tv_usec - start_time.tv_usec)/1000 + (temp.tv_sec - start_time.tv_sec)*1000));
}

int	main(int ac, char **av)
{
	t_env 		env;
	t_philos	**philos;

	philos = NULL;
	if (ac < 5 || ac > 6)
		(printf("%s\n", ARGERROR), exit(EXIT_FAILURE));
	check_args(av, ac);
	init_env(&env, av, ac);
	init_philos(philos, env);
	create_them_threads(philos, env.nop);
	// whats_the_time(&env);
	printf("%d, %d, %d, %d, %d\n", env.nop, env.ttd, env.tte, env.tts, env.meal_count);
	free(env.forks);
}

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

// parse first, then make the processes, then start eating and all, then free stuff
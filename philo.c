/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:35:35 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/20 18:00:26 by lalwafi          ###   ########.fr       */
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
			printf("should be positive integers above 0\n");
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

void	create_them_threads(t_philos **philos, int nop)
{
	int	i;

	i = -1;
	while (++i < nop)
		pthread_create(&philos[i]->thread_id, NULL, process, philos[i]);
	i = -1;
	while (++i < nop)
		pthread_join(philos[i]->thread_id, NULL);
}

void	one_philo(char **av)
{
	struct timeval	start;
	struct timeval	temp;

	gettimeofday(&start, NULL);
	gettimeofday(&temp, NULL);
	printf("\e[33m%ld 1 has taken a fork\e[0m\n", whats_the_time(start));
	while (((temp.tv_usec - start.tv_usec) / 1000 + \
		(temp.tv_sec - start.tv_sec) * 1000) < ft_atoi(av[2]))
	{
		usleep(100);
		gettimeofday(&temp, NULL);
	}
	printf("\e[31m%ld 1 died\e[0m\n", whats_the_time(start));
	exit(EXIT_SUCCESS);
}

int	main(int ac, char **av)
{
	t_env		env;
	t_philos	**philos;

	if (ac < 5 || ac > 6)
		(printf("%s\n", ARGERROR), exit(EXIT_FAILURE));
	check_args(av, ac);
	if (ft_atoi(av[1]) == 1)
		one_philo(av);
	init_env(&env, av, ac);
	philos = init_philos(&env);
	if (!philos)
		(free(env.forks), exit(EXIT_FAILURE));
	create_them_threads(philos, env.nop);
	free_all(philos, env);
}

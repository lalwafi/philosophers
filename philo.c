/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:35:35 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/22 21:39:15 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_args(char **av, int ac)
{
	int	i;
	int	j;
	int	valid;

	i = 1;
	j = -1;
	valid = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i], &valid) <= 0 || valid == 0)
			return (printf("Only integers between 1 - 2147483647\n"), 1);
		while (av[i][++j])
		{
			if (ft_isdigit(av[i][j]) == 0)
				return (printf("only integers pls\n"), 1);
		}
		valid = 1;
		j = -1;
		i++;
	}
	return (0);
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

int	one_philo(char **av)
{
	struct timeval	start;
	struct timeval	temp;

	gettimeofday(&start, NULL);
	gettimeofday(&temp, NULL);
	printf("\e[33m%ld 1 has taken a fork\e[0m\n", whats_the_time(start));
	while (((temp.tv_usec - start.tv_usec) / 1000 + \
		(temp.tv_sec - start.tv_sec) * 1000) < ft_atoi(av[2], 0))
	{
		usleep(100);
		gettimeofday(&temp, NULL);
	}
	printf("\e[31m%ld 1 died\e[0m\n", whats_the_time(start));
	return (0);
}

int	main(int ac, char **av)
{
	t_env		env;
	t_philos	**philos;
	int			valid;

	if (ac < 5 || ac > 6)
		return (printf("%s\n", ARGERROR), 1);
	if (check_args(av, ac) == 1)
		return (1);
	valid = 1;
	ft_atoi(av[1], &valid);
	if (ft_atoi(av[1], &valid) == 1 && valid == 1)
		return (one_philo(av));
	else
		printf("what the fuck is valid\n");
	if (init_env(&env, av, ac) == 1)
	{
		write(1, "Init error\n", 11);
		return (1);
	}
	philos = init_philos(&env);
	if (!philos)
		return (free(env.forks), 1);
	create_them_threads(philos, env.nop);
	free_all(philos, env);
}

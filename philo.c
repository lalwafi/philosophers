/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:35:35 by lalwafi           #+#    #+#             */
/*   Updated: 2024/10/16 17:55:41 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	init_philo(t_philo *philo, char **av, int ac)
{
	// philo = malloc(sizeof(t_philo));
	if (ac == 5 || ac == 6)
	{
		philo->nop = ft_atoi(av[1]);
		philo->ttd = ft_atoi(av[2]);
		philo->tte = ft_atoi(av[3]);
		philo->tts = ft_atoi(av[4]);
		if (ac == 6)
			philo->meal_count = ft_atoi(av[5]);
		else
			philo->meal_count = -1;
	}
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

int	main(int ac, char **av)
{
	t_philo philo;
	// (void)av;
	if (ac < 5 || ac > 6)
	{
		printf("usage : ./philo num_of_philos ttd tte tts [meal_count]\n");
		exit(EXIT_FAILURE);
	}
	check_args(av, ac);
	init_philo(&philo, av, ac);
	printf("%d, %d, %d, %d, %d\n", philo.nop, philo.ttd, philo.tte, philo.tts, philo.meal_count);
}

// number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]

// parse first, then make the processes, then start eating and all, then free stuff
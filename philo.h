/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:36:07 by lalwafi           #+#    #+#             */
/*   Updated: 2024/10/23 00:56:06 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <string.h>
# include <sys/time.h>
# include <pthread.h>

# define ARGERROR "usage : ./philosophers [number_of_philosophers] [time_to_die] [time_to_eat] [time_to_sleep] (optional)[number_of_times_each_philosopher_must_eat]"

typedef struct env
{
	int		nop; //number of philosophers
	int		ttd;
	int		tte;
	int		tts;
	int		meal_count; //how many meals each philosopher should eat
	int		*forks;
} t_env;

typedef struct philos
{
	int			index;
	int			meals;
	int			left_fork;
	int			right_fork;
	pthread_t	thread_id;	
} t_philos;


// functions

void	init_env(t_env *env, char **av, int ac);
void	check_args(char **av, int ac);

// utils

char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:36:07 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/03 14:39:24 by lalwafi          ###   ########.fr       */
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
	struct timeval	start_time;
	int		meal_count; //how many meals each philosopher should eat
	int		*forks;
	pthread_mutex_t	lock;
} t_env;

typedef struct philos
{
	int			index;
	int			meals;
	int			left_fork;
	int			right_fork;
	pthread_t	thread_id;
	t_env		env;	
} t_philos;

// typedef struct forks
// {
// 	int	
// };


// functions

void		init_env(t_env *env, char **av, int ac);
void		check_args(char **av, int ac);
void		*run_em(void *idk);
void		create_them_threads(t_philos **philos, int nop);
size_t		whats_the_time(struct timeval start_time);
void		sleep_ms(struct timeval start_time, long int sleep_ms);
t_philos	**init_philos(t_env env);
void		free_all(t_philos **philos, t_env env);

// utils

char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif
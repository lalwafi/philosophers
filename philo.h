/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:36:07 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/26 17:31:16 by lalwafi          ###   ########.fr       */
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
# include <limits.h>

# define ARGERROR "usage : ./philosophers [number_of_philosophers] \
				[time_to_die] [time_to_eat] [time_to_sleep] \
				(optional)[number_of_times_each_philosopher_must_eat]"

typedef struct env
{
	int				nop;
	unsigned long	ttd;
	unsigned long	tte;
	unsigned long	tts;
	struct timeval	start_time;
	int				meal_count;
	int				*forks;
	pthread_mutex_t	*fork_locks;
	int				dead;
	pthread_mutex_t	print_lock;
	pthread_mutex_t	check_lock;
	pthread_mutex_t	lock;
}	t_env;

typedef struct philos
{
	int				index;
	int				meals;
	int				left_fork;
	int				right_fork;
	int				dead_alive;
	struct timeval	last_meal;
	pthread_t		thread_id;
	t_env			*env;	
}	t_philos;

// functions

int			check_args(char **av, int ac);
int			one_philo(char **av);
int			init_env(t_env *env, char **av, int ac);
int			is_it_max(t_env *env, char **av, int ac);
t_philos	**init_philos(t_env *env);
int			init_mutex(t_env *env);
void		create_them_threads(t_philos **philos, int nop);
void		*process(void *ptr);

// process

void		take_forks_left(t_philos **philo);
void		take_forks_right(t_philos **philo);
void		drop_forks(t_philos **philo);
void		eat(t_philos **philo);

// utils

char		*ft_strdup(const char *s1);
size_t		ft_strlen(const char *s);
int			ft_isdigit(int c);
int			ft_atoi(const char *str, int *valid);
int			handle_overflow(const char *str, int sign, int *valid);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

// utils for philo

void		free_all(t_philos **philos, t_env env);
size_t		whats_the_time(struct timeval start_time);
void		sleep_ms(long int sleep_ms, t_philos *philos);
void		print_smth(t_philos *philo, char c);
int			check_dead(t_philos *philo);
int			meals_check(t_philos *philo);

#endif
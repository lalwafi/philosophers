/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 18:36:07 by lalwafi           #+#    #+#             */
/*   Updated: 2024/10/16 14:19:17 by lalwafi          ###   ########.fr       */
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

typedef struct philo
{
	int	nop; //number of philosophers
	int	ttd;
	int	tte;
	int	tts;
	int	meal_count; //how many meals each philosopher should eat
} t_philo;

// functions

void	init_philo(t_philo *philo, char **av, int ac);
void	check_args(char **av, int ac);

// utils

char	*ft_strdup(const char *s1);
size_t	ft_strlen(const char *s);
int		ft_isdigit(int c);
int		ft_atoi(const char *str);

#endif
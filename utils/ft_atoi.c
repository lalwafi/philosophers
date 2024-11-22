/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalwafi <lalwafi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 10:43:37 by lalwafi           #+#    #+#             */
/*   Updated: 2024/11/22 17:57:03 by lalwafi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	handle_overflow(const char *str, int sign, int *valid)
{
	long	n;
	long	temp;

	n = 0;
	while ((*str >= '0') && (*str <= '9'))
	{
		temp = n;
		n = n * 10 + (*str - '0');
		if (temp > n)
		{
			valid = 0;
			break ;
		}
		str++;
	}
	if (n < INT_MIN || n > INT_MAX)
	{
		write(1, "overflow\n", 9);
		*valid = 0;
		return (0);
	}
	return (sign * n);
}

int	ft_atoi(const char *str, int *valid)
{
	int	sign;
	int	i;

	i = 0;
	sign = 1;
	if (ft_strncmp(str, "-2147483648", 12) == 0)
		return (-2147483648);
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if ((str[i] == '-' || str[i] == '+') && ft_isdigit(str[i + 1]) == 0)
	{
		write(1, "overflow\n", 9);
		*valid = 0;
		return (0);
	}
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	else if (*str == '+')
		str++;
	return (handle_overflow(str, sign, valid));
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	if (!n)
		return (0);
	while (s2[i] && s1[i] && i < n - 1)
	{
		if (s1[i] != s2[i])
			break ;
		i++;
	}
	return ((unsigned char)s1[i] - (unsigned char)s2[i]);
}

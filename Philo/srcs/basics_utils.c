/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelle <maelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:29:11 by mberthet          #+#    #+#             */
/*   Updated: 2022/02/12 12:18:13 by maelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned int	ft_atoi(const char *str)
{
	long	res;

	res = 0;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (0);
		while (*str >= '0' && *str <= '9')
			res = res * 10 + (*str++ - '0');
	}
	if (res > 4294967295)
	{
		return (0);
	}
	return (res);
}

int	isnum(int n)
{
	if (n < '0' || n > '9')
		return (0);
	return (1);
}

void	ft_clean(t_arg *arg, t_philo *philo_st, pthread_mutex_t *fork,
		pthread_t *philo_th)
{
	unsigned int	i;
	pthread_mutex_unlock(&arg->speak);
	pthread_mutex_destroy(&(arg->speak));
	i = -1;
	while (++i < arg->nb_philo)
	{
		pthread_mutex_unlock(fork + i);
		pthread_mutex_destroy(fork + i);
	}
	free_all(arg, philo_st, fork, philo_th);
}

int	free_all(t_arg *arg, t_philo *philo_st, pthread_mutex_t *fork, pthread_t *philo_th)
{
	free(arg);
	free(philo_st);
	free(fork);
	free(philo_th);
	return (0);
}

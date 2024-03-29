/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:23:15 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/05 12:18:09 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	ft_join_pthread(pthread_t *philo_th, t_arg *arg, pthread_mutex_t *fork,
	t_philo *philo_st)
{
	unsigned int	i;

	i = -1;
	while (++i < arg->nb_philo)
	{
		if (pthread_join(philo_th[i], NULL))
		{
			free_all(arg, philo_st, fork, philo_th);
			return (-1);
		}
	}
	return (0);
}

int	ft_pth_creat_philo(t_arg *arg, pthread_t *philo_th, t_philo *philo_st)
{
	unsigned int	i;

	i = 0;
	while (i < arg->nb_philo)
	{
		if (pthread_create(philo_th + i, NULL, &routine_one,
				(void *)(philo_st + i)))
			return (-1);
		usleep(20);
		i += 2;
	}
	i = 1;
	usleep(500);
	while (i < arg->nb_philo)
	{
		if (pthread_create(philo_th + i, NULL, &routine_one,
				(void *)(philo_st + i)))
			return (-1);
		usleep(20);
		i += 2;
	}
	return (0);
}

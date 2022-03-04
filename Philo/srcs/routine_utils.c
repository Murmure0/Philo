/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 11:32:44 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/04 16:21:15 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	my_printf(t_philo *philo_st, char *str)
{
	usleep(100);
	pthread_mutex_lock(&(philo_st->arg->speak));
	if (check_death(philo_st) || philo_st->arg->nb_meal_ok
		== philo_st->arg->nb_philo)
	{
		unlock_fork(philo_st);
		return (-1);
	}
	printf("%u %u %s\n", real_time(philo_st->arg->start),
		philo_st->num_philo, str);
	pthread_mutex_unlock(&(philo_st->arg->speak));
	return (0);
}

int	take_fork_eat(int num_fork_r, int num_fork_l, t_philo *philo_st)
{
	if (check_death(philo_st))
	{
		my_printf(philo_st, "died");
		pthread_mutex_lock(&(philo_st->arg->death));
		philo_st->arg->dead_philo = philo_st->num_philo;
		pthread_mutex_unlock(&(philo_st->arg->death));
		return (-1);
	}
	pthread_mutex_lock(philo_st->fork + num_fork_l);
	if (my_printf(philo_st, "has taken a fork") < 0)
		return (-1);
	pthread_mutex_lock(philo_st->fork + num_fork_r);
	if (my_printf(philo_st, "has taken a fork") < 0)
		return (-1);
	pthread_mutex_lock(&(philo_st->meal));
	philo_st->last_meal = real_time(philo_st->arg->start);
	pthread_mutex_unlock(&(philo_st->meal));
	if (my_printf(philo_st, "is eating") < 0)
		return (-1);
	return (0);
}

int check_last_meal(t_philo *philo_st)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(philo_st->meal));
	ret  = philo_st->last_meal;
	pthread_mutex_unlock(&(philo_st->meal));
	return (ret);
}

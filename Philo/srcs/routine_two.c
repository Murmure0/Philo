/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_two.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 11:32:44 by mberthet          #+#    #+#             */
/*   Updated: 2022/02/06 12:03:20 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	dead_unlock_fork(t_philo *philo_st)
{
	printf("%u %u died\n", real_time(philo_st->arg->start),
		philo_st->num_philo);
	philo_st->arg->dead_philo = philo_st->num_philo;
	pthread_mutex_unlock(&(philo_st->fork[(philo_st->num_philo) - 1]));
	pthread_mutex_unlock(&(philo_st->fork[(philo_st->num_philo)
			% (philo_st->arg->nb_philo)]));
	pthread_mutex_unlock(&(philo_st->arg->speak));
}

void	unlock_fork(t_philo *philo_st)
{
	pthread_mutex_unlock(&(philo_st->fork[(philo_st->num_philo)
			- 1]));
	pthread_mutex_unlock(&(philo_st->fork[(philo_st->num_philo)
			% (philo_st->arg->nb_philo)]));
	pthread_mutex_unlock(&(philo_st->arg->speak));
}

void	*death(void *data)
{
	t_philo	*philo_st;

	philo_st = (t_philo *)data;
	while (1)
	{
		usleep(1000);
		if (philo_st->arg->time_to_die < (real_time(philo_st->arg->start)
				- philo_st->last_meal) || philo_st->arg->dead_philo
			|| philo_st->arg->nb_meal_ok == philo_st->arg->nb_philo)
		{
			pthread_mutex_lock(&(philo_st->arg->speak));
			if (philo_st->arg->nb_meal_ok == philo_st->arg->nb_philo
				|| philo_st->arg->dead_philo)
			{
				unlock_fork(philo_st);
				return (NULL);
			}
			dead_unlock_fork(philo_st);
			break ;
		}
	}
	return (NULL);
}

int	my_printf(t_philo *philo_st, char *str)
{
	usleep(100);
	pthread_mutex_lock(&(philo_st->arg->speak));
	if (philo_st->arg->dead_philo || philo_st->arg->nb_meal_ok
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
	if (philo_st->arg->dead_philo)
	{
		my_printf(philo_st, "died");
		philo_st->arg->dead_philo = philo_st->num_philo;
		return (-1);
	}
	if (pthread_mutex_lock(philo_st->fork + num_fork_l))
		return (-1);
	if (my_printf(philo_st, "has taken a fork") < 0)
		return (-1);
	if (pthread_mutex_lock(philo_st->fork + num_fork_r))
		return (-1);
	if (my_printf(philo_st, "has taken a fork") < 0)
		return (-1);
	philo_st->last_meal = real_time(philo_st->arg->start);
	if (my_printf(philo_st, "is eating") < 0)
		return (-1);
	return (0);
}

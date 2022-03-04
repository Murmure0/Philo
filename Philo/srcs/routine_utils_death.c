/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils_death.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/04 14:39:58 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/04 16:25:14 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	check_death(t_philo *philo_st)
{
	int	ret;

	ret = 0;
	pthread_mutex_lock(&(philo_st->arg->death));
	ret  = philo_st->arg->dead_philo;
	pthread_mutex_unlock(&(philo_st->arg->death));
	return (ret);
}

void	dead_unlock_fork(t_philo *philo_st)
{
	printf("%u %u died\n", real_time(philo_st->arg->start),
		philo_st->num_philo);
	pthread_mutex_lock(&(philo_st->arg->death));
	philo_st->arg->dead_philo = philo_st->num_philo;
	pthread_mutex_unlock(&(philo_st->arg->death));
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
				- check_last_meal(philo_st))
				|| check_death(philo_st)
			|| philo_st->arg->nb_meal_ok == philo_st->arg->nb_philo)
		{
			pthread_mutex_lock(&(philo_st->arg->speak));
			if (philo_st->arg->nb_meal_ok == philo_st->arg->nb_philo
				|| check_death(philo_st))
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

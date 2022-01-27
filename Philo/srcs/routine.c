/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:36:14 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/27 17:00:49 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death(void *data)
{
	t_philo	*philo_st;

	philo_st = (t_philo *)data;
	while (1)
	{
		usleep(philo_st->arg->time_to_die);
		if (philo_st->arg->time_to_die < (reel_time(philo_st->arg->start)
			- philo_st->last_meal) || philo_st->arg->dead_philo)
		{
			my_printf(philo_st, "is dead");
			philo_st->arg->dead_philo = philo_st->num_philo;
			break ;
		}
	}
	return (NULL);
}

int	my_printf(t_philo *philo_st, char *str)
{
	pthread_mutex_lock(&(philo_st->arg->speak));
	if (philo_st->arg->dead_philo)
	{
		pthread_mutex_unlock(&(philo_st->arg->speak));
		return (-1);
	}
	printf("%u %u %s.\n",reel_time(philo_st->arg->start),
		philo_st->num_philo, str);
	pthread_mutex_unlock(&(philo_st->arg->speak));
	return (0);
}

int	philo_eat(t_philo *philo_st)
{
	int	num_fork_r;
	int	num_fork_l;

	num_fork_r = (philo_st->num_philo) % (philo_st->arg->nb_philo);
	num_fork_l = (philo_st->num_philo) - 1;
	if (num_fork_l == num_fork_r || philo_st->arg->dead_philo)
	{
		my_printf(philo_st, "is dead");
		philo_st->arg->dead_philo = philo_st->num_philo;
		return (-1);
	}
	if (pthread_mutex_lock(philo_st->fork + num_fork_l))
		return (-1); 
	if(my_printf(philo_st, "has taken a fork") < 0)
		return (-1);
	if (pthread_mutex_lock(philo_st->fork + num_fork_r))
		return (-1);
	if(my_printf(philo_st, "has taken a fork") < 0)
		return (-1);
	philo_st->last_meal = reel_time(philo_st->arg->start);
	if(my_printf(philo_st, "is eating") < 0)
		return (-1);
	my_usleep(philo_st, philo_st->arg->time_to_eat, 'e');
	pthread_mutex_unlock(&(philo_st->fork[num_fork_l]));
	pthread_mutex_unlock(&(philo_st->fork[num_fork_r]));
	return (0);
}

int philo_sleep(t_philo *philo_st)
{
	if(my_printf(philo_st, "is sleeping") < 0)
		return (-1);
	my_usleep(philo_st, philo_st->arg->time_to_sleep, 's');
	return (0);
}

int philo_think(t_philo *philo_st)
{
	if(my_printf(philo_st, "is thinking") < 0)
		return (-1);
	return (0);
}

int routine(t_philo *philo_st)
{
	if (philo_eat(philo_st))
		return (-1);
	if (philo_sleep(philo_st))
		return (-1);
	if (philo_think(philo_st))
		return (-1);
	return (0);
}

void *routine_one(void *data)
{
	t_philo *philo_st;
	pthread_t	check_death;

	philo_st = (t_philo *)data;
	if (philo_st->num_philo % 2 != 0)
		usleep(1000);
	if (pthread_create(&check_death, NULL, &death, (void *)(philo_st)))
		return (NULL);
	while (1)
	{
		if (routine(philo_st))
			break ;
	}
	pthread_join(check_death, NULL);
	pthread_detach(check_death);
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelle <maelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:36:14 by mberthet          #+#    #+#             */
/*   Updated: 2022/02/12 13:25:09 by maelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	philo_eat(t_philo *philo_st)
{
	int	num_fork_r;
	int	num_fork_l;

	num_fork_r = (philo_st->num_philo) % (philo_st->arg->nb_philo);
	num_fork_l = (philo_st->num_philo) - 1;
	if (take_fork_eat(num_fork_r, num_fork_l, philo_st) < 0)
		return (-1);
	if (philo_st->arg->nb_meal && philo_st->nb_meal_ok == 0)
	{
		philo_st->nb_meal++;
		pthread_mutex_lock(&(philo_st->arg->speak));
		if (philo_st->nb_meal == philo_st->arg->nb_meal)
			philo_st->arg->nb_meal_ok++;
		pthread_mutex_unlock(&(philo_st->arg->speak));
	}
	ft_usleep(philo_st, philo_st->arg->time_to_eat);
	pthread_mutex_unlock(&(philo_st->fork[num_fork_l]));
	pthread_mutex_unlock(&(philo_st->fork[num_fork_r]));
	return (0);
}

int	philo_sleep(t_philo *philo_st)
{
	if (my_printf(philo_st, "is sleeping") < 0)
		return (-1);
	ft_usleep(philo_st, philo_st->arg->time_to_sleep);
	return (0);
}

int	philo_think(t_philo *philo_st)
{
	if (my_printf(philo_st, "is thinking") < 0)
		return (-1);
	return (0);
}

int	routine(t_philo *philo_st)
{
	if (philo_eat(philo_st))
		return (-1);
	if (philo_sleep(philo_st))
		return (-1);
	if (philo_think(philo_st))
		return (-1);
	return (0);
}

void	*routine_one(void *data)
{
	t_philo		*philo_st;
	pthread_t	check_death;

	philo_st = (t_philo *)data;
	if (pthread_create(&check_death, NULL, &death, (void *)(philo_st)))
		return (NULL);
	while (1)
		if (routine(philo_st))
			break ;
	pthread_detach(check_death);
	return (NULL);
}

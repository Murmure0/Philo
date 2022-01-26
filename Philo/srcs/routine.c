/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:36:14 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/26 17:13:29 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int death(t_philo *philo_st)
{
	//printf("time to die : %u, temp en cours : %u\n", philo_st->arg->time_to_die,(reel_time(philo_st->arg->start) - philo_st->last_meal));
	//printf("temps last meal : %u\n\n",philo_st->last_meal);
	if (philo_st->arg->time_to_die < (reel_time(philo_st->arg->start) - philo_st->last_meal))
	{
		philo_st->arg->dead_philo = philo_st->num_philo;
		return (1);
	}
	return (0);
}

int my_printf(t_philo *philo_st, char *str)
{
	pthread_mutex_lock(&(philo_st->arg->speak));	
	printf("%u philosopher %u %s.\n",reel_time(philo_st->arg->start), philo_st->num_philo, str);
	//pthread_mutex_unlock(&(philo_st->arg->speak));
	if (death(philo_st) == 0)
		pthread_mutex_unlock(&(philo_st->arg->speak));
	else if (death > 0)
	{
		printf("%u philosopher %u %s",reel_time(philo_st->arg->start), philo_st->num_philo, "\033[31;01mis ded\033[00m\n");
		return (1) ;
	}
	return (0);
}

int philo_eat(t_philo *philo_st, int num_fork_l)
{
	int num_fork_r;
	num_fork_r = (philo_st->num_philo) % (philo_st->num_philo);
	printf("num fork l :%d\n", num_fork_l);
	printf("num fork r :%d\n", num_fork_r);

	if (pthread_mutex_lock(philo_st->fork + num_fork_l))
		write(2, "Hey mate!\n", 10);
	// pthread_mutex_lock(philo_st->fork); //&str[0] == str + 0 == str
	if (my_printf(philo_st, "\033[35;01mhas taken a fork\033[00m") > 0)
		return (1);
	// pthread_mutex_lock(&(philo_st->fork[num_fork_r]));
	if (my_printf(philo_st, "\033[35;01mhas taken a fork\033[00m") > 0)
		return (1);
	philo_st->last_meal = reel_time(philo_st->arg->start);
	if (my_printf(philo_st, "\033[33;01mis eating\033[00m") > 0)
		return (1);
	my_usleep(philo_st, philo_st->arg->time_to_eat);
	pthread_mutex_unlock(&(philo_st->fork[num_fork_l]));
	// pthread_mutex_unlock(&(philo_st->fork[num_fork_r]));
	return (0);
}

int philo_sleep(t_philo *philo_st)
{
	if (my_printf(philo_st, "\033[34;01mis sleeping\033[00m") > 0)
		return (1);
	//printf("time to sleep : %u\n", philo_st->arg->time_to_sleep);
	my_usleep(philo_st, philo_st->arg->time_to_sleep);
	return (0);
}

int philo_think(t_philo *philo_st)
{
	if (my_printf(philo_st, "\033[32;01mis thinking\033[00m") > 0)
		return(1);
	return (0);
}

void *routine_one(void *data)
{
	t_philo *philo_st;

	// philo_st = malloc(sizeof(philo_st));
	philo_st = (t_philo *)data;
	int num_fork_l;
	num_fork_l = (philo_st->num_philo) - 1;
	if (philo_st->num_philo % 2 != 0)
		usleep(10000);
	while (1)
	{
		if (philo_eat(philo_st, num_fork_l))
			break;
		if (philo_sleep(philo_st))
			break;
		if (philo_think(philo_st))
			break;
	}
	return (NULL);
}
// void *routine(void *data)
// {
// 	t_philo *philo_st;

// 	philo_st = malloc(sizeof(philo_st));
// 	philo_st = (t_philo *)data;
// 	int num_fork_l;
// 	num_fork_l = (philo_st->num_philo) - 1;

// 	while (1)
// 	{
// 		if (philo_eat(philo_st, num_fork_l))
// 			break;
// 		if (philo_sleep(philo_st))
// 			break;
// 		if (philo_think(philo_st))
// 			break;
// 	}
// 	return (0);
// }
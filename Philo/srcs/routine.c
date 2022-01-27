/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:36:14 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/27 16:18:02 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void *death(void *data)
{
	t_philo *philo_st;
	philo_st = (t_philo *)data;

	while (1)
	{
		usleep(philo_st->arg->time_to_die);
		if (philo_st->arg->time_to_die < (reel_time(philo_st->arg->start) - philo_st->last_meal) || philo_st->arg->dead_philo)
		{
			my_printf(philo_st, "\033[31;01mis dead\033[00m");
			philo_st->arg->dead_philo = philo_st->num_philo;
			break ;
		}
	}
	return (NULL);
}

int my_printf(t_philo *philo_st, char *str)
{
	pthread_mutex_lock(&(philo_st->arg->speak));
	if (philo_st->arg->dead_philo)
	{
		pthread_mutex_unlock(&(philo_st->arg->speak));
		return (-1);
	}
	printf("%u philo %u %s.\n",reel_time(philo_st->arg->start), philo_st->num_philo, str);
	pthread_mutex_unlock(&(philo_st->arg->speak));
	return (0);
}

	//pthread_mutex_lock(philo_st->fork); //&str[0] == str + 0 == str
int philo_eat(t_philo *philo_st)
{
	int num_fork_r;
	int num_fork_l;
	num_fork_r = (philo_st->num_philo) % (philo_st->arg->nb_philo);
	num_fork_l = (philo_st->num_philo) - 1;

	if (num_fork_l == num_fork_r || philo_st->arg->dead_philo)
	{
		my_printf(philo_st, "\033[31;01mis dead\033[00m");
		philo_st->arg->dead_philo = philo_st->num_philo;
		return (-1);
	}
	if (pthread_mutex_lock(philo_st->fork + num_fork_l))
		write(2, "Hey mate!\n", 10); //azy
	if(my_printf(philo_st, "\033[35;01mhas taken a fork\033[00m") < 0)
		return (-1);
	if (pthread_mutex_lock(philo_st->fork + num_fork_r))
		write(2, "Hey mote!\n", 10); //change ca
	if(my_printf(philo_st, "\033[35;01mhas taken a fork\033[00m") < 0)
		return (-1);
	philo_st->last_meal = reel_time(philo_st->arg->start);
	if(my_printf(philo_st, "\033[33;01mis eating\033[00m") < 0)
		return (-1);
	my_usleep(philo_st, philo_st->arg->time_to_eat, 'e');
	pthread_mutex_unlock(&(philo_st->fork[num_fork_l]));
	pthread_mutex_unlock(&(philo_st->fork[num_fork_r]));

	return (0);
}

int philo_sleep(t_philo *philo_st)
{
	if(my_printf(philo_st, "\033[34;01mis sleeping\033[00m") < 0)
		return (-1);
	my_usleep(philo_st, philo_st->arg->time_to_sleep, 's');
	return (0);
}

int philo_think(t_philo *philo_st)
{
	if(my_printf(philo_st, "\033[32;01mis thinking\033[00m") < 0)
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
	// while (!(philo_st->arg->dead_philo))
	if (pthread_create(&check_death, NULL, &death, (void *)(philo_st)))
		return (NULL);
	while (1)
	{
		// if (philo_st->arg->dead_philo)
		// 	break ;
		if (routine(philo_st))
			break ;
	}
	write(1, "youpo\n", 7);
	pthread_join(check_death, NULL);
	pthread_detach(check_death);
	return (NULL);
}



/* ici */
// int death(t_philo *philo_st)
// {
// 	//printf("time to die : %u, temp en cours : %u\n", philo_st->arg->time_to_die,(reel_time(philo_st->arg->start) - philo_st->last_meal));
// 	//printf("temps last meal : %u\n\n",philo_st->last_meal);
// 	if (philo_st->arg->time_to_die < (reel_time(philo_st->arg->start) - philo_st->last_meal))
// 	{
// 		philo_st->arg->dead_philo = philo_st->num_philo;
// 		return (1);
// 	}
// 	return (0);
// }

// int my_printf(t_philo *philo_st, char *str)
// {
// 	pthread_mutex_lock(&(philo_st->arg->speak));	
// 	printf("%u philo %u %s.\n",reel_time(philo_st->arg->start), philo_st->num_philo, str);
// 	if (death(philo_st) == 0)
// 		pthread_mutex_unlock(&(philo_st->arg->speak));
// 	else if (death > 0)
// 	{
// 		printf("%u philo %u %s",reel_time(philo_st->arg->start), philo_st->num_philo, "\033[31;01mis dead.\033[00m\n");
// 		return (-1) ;
// 	}
// 	return (0);
// }
// 	//pthread_mutex_lock(philo_st->fork); //&str[0] == str + 0 == str

// int philo_eat(t_philo *philo_st)
// {
// 	int num_fork_r;
// 	int num_fork_l;
// 	num_fork_r = (philo_st->num_philo) % (philo_st->arg->nb_philo);
// 	num_fork_l = (philo_st->num_philo) - 1;
	

// 	pthread_mutex_lock(&(philo_st->arg->speak));
// 	printf("Num fork right : %d, Fork left : %d.\n", num_fork_r, num_fork_l);
// 	pthread_mutex_unlock(&(philo_st->arg->speak));

// 	if (num_fork_l == num_fork_r)
// 	{
// 		printf("%u philo %u %s",reel_time(philo_st->arg->start), philo_st->num_philo, "\033[31;01mis dead.\033[00m\n");
// 		return (-1);
// 	}
// 	if (pthread_mutex_lock(philo_st->fork + num_fork_l))
// 		write(2, "Hey mate!\n", 10);
// 	if (my_printf(philo_st, "\033[35;01mhas taken a fork\033[00m") > 0)
// 		return (1);
// 	if (pthread_mutex_lock(philo_st->fork + num_fork_r))
// 		write(2, "Hey mote!\n", 10);
// 	if (my_printf(philo_st, "\033[35;01mhas taken a fork\033[00m") > 0)
// 		return (1);
// 	philo_st->last_meal = reel_time(philo_st->arg->start);
// 	if (my_printf(philo_st, "\033[33;01mis eating\033[00m") > 0)
// 		return (1);
// 	my_usleep(philo_st, philo_st->arg->time_to_eat, 'e');
// 	pthread_mutex_unlock(&(philo_st->fork[num_fork_l]));
// 	pthread_mutex_unlock(&(philo_st->fork[num_fork_r]));

// 	return (0);
// }

// int philo_sleep(t_philo *philo_st)
// {
// 	if (my_printf(philo_st, "\033[34;01mis sleeping\033[00m") > 0)
// 		return (1);
// 	//printf("time to sleep : %u\n", philo_st->arg->time_to_sleep);
// 	my_usleep(philo_st, philo_st->arg->time_to_sleep, 's');
// 	return (0);
// }

// int philo_think(t_philo *philo_st)
// {
// 	if (my_printf(philo_st, "\033[32;01mis thinking\033[00m") > 0)
// 		return(1);
// 	return (0);
// }

// void *routine_one(void *data)
// {
// 	t_philo *philo_st;

// 	philo_st = (t_philo *)data;
// 	if (philo_st->num_philo % 2 != 0)
// 		usleep(1000);
// 	while (!(philo_st->arg->dead_philo))
// 	{
// 		if (philo_eat(philo_st))
// 			break;
// 		if (philo_sleep(philo_st))
// 			break;
// 		if (philo_think(philo_st))
// 			break;
// 	}
// 	return (NULL);
// }
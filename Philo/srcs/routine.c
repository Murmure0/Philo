/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 09:36:14 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/28 15:48:15 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*death(void *data)
{
	t_philo	*philo_st;

	philo_st = (t_philo *)data;
	while (1)
	{
		usleep(1000);
		// usleep(philo_st->arg->time_to_die);
		if (philo_st->arg->time_to_die < (reel_time(philo_st->arg->start)
			- philo_st->last_meal) || philo_st->arg->dead_philo)
		{
			//my_printf(philo_st, "died");
			pthread_mutex_lock(&(philo_st->arg->speak));
			if (philo_st->arg->dead_philo)
			{
				pthread_mutex_unlock(&(philo_st->arg->speak));
				return NULL;
			}
			printf("%u %u died, temps de a mort : %u\n",reel_time(philo_st->arg->start),
		philo_st->num_philo, (reel_time(philo_st->arg->start)
			- philo_st->last_meal));
			philo_st->arg->dead_philo = philo_st->num_philo;
			pthread_mutex_unlock(&(philo_st->arg->speak));
			break ;
		}
	}
	return (NULL);
}

int	my_printf(t_philo *philo_st, char *str)
{
	usleep(100);
	pthread_mutex_lock(&(philo_st->arg->speak));
	if (philo_st->arg->dead_philo)
	{
		pthread_mutex_unlock(&(philo_st->arg->speak));
		return (-1);
	}
	// my_putstr(philo_st, str);
	printf("%u %u %s\n",reel_time(philo_st->arg->start),
		philo_st->num_philo, str);
	pthread_mutex_unlock(&(philo_st->arg->speak));
	return (0);
}
/*
void my_putstr(t_philo *philo_st, char *str_in)
{
	size_t timestamp_len;
	size_t num_philo_len;
	size_t str_len;
	size_t i;
	char *str;

	timestamp_len = ft_strlen(ft_itoa(reel_time(philo_st->arg->start)));
	num_philo_len = ft_strlen(ft_itoa(philo_st->num_philo));
	str_len = ft_strlen(str_in);
	i = timestamp_len + num_philo_len + str_len;
	str = malloc(sizeof(char) * i + 1);
	memset(str, 0, i);
	str[i] = '\0';
	i = -1;
	ft_strlcat(str, ft_itoa(reel_time(philo_st->arg->start)), ft_strlen(ft_itoa(reel_time(philo_st->arg->start))));
	ft_strlcat(str, ft_itoa(philo_st->num_philo),ft_strlen(ft_itoa(philo_st->num_philo)));
	ft_strlcat(str, str_in,ft_strlen(str_in));
	write(1, str, ft_strlen(str));
}
*/
int	philo_eat(t_philo *philo_st)
{
	int	num_fork_r;
	int	num_fork_l;

	num_fork_r = (philo_st->num_philo) % (philo_st->arg->nb_philo);
	num_fork_l = (philo_st->num_philo) - 1;

	// pthread_mutex_lock(&(philo_st->arg->speak));
	// printf(" Philo %u a pris les fork %d et %d\n", philo_st->num_philo, num_fork_l, num_fork_r);
	// pthread_mutex_unlock(&(philo_st->arg->speak));

	if (num_fork_l == num_fork_r || philo_st->arg->dead_philo)
	{
		my_printf(philo_st, "died");
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
	// usleep(philo_st->arg->time_to_eat * 1000);
	ft_usleep(philo_st->arg->time_to_eat);
	// my_usleep(philo_st, philo_st->arg->time_to_eat, 'e');
	pthread_mutex_unlock(&(philo_st->fork[num_fork_l]));
	pthread_mutex_unlock(&(philo_st->fork[num_fork_r]));
	return (0);
}

int philo_sleep(t_philo *philo_st)
{
	if(my_printf(philo_st, "is sleeping") < 0)
		return (-1);
	// usleep(philo_st->arg->time_to_sleep * 1000);
	ft_usleep(philo_st->arg->time_to_sleep);
	// my_usleep(philo_st, philo_st->arg->time_to_sleep, 's');
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
		usleep(100);
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

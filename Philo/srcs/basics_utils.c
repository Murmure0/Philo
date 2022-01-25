/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:29:11 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/25 11:57:30 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atoi(const char *str)
{
	long	res;

	res = 0;
	if (*str == '\0')
		return (0);
	while (*str)
	{
		while (*str >= '0' && *str <= '9')
			res = res * 10 + (*str++ - '0');
	}
	if (res > 4294967295)
	{
		printf("Please enter a raisonnable number for time_to_eat.\n");
		return (0);
	}
	return (res);
}

int	isnum(int n)
{
	if (n < '0'|| n > '9')
		return (0);
	return (1);
}

unsigned int my_get_time(void)
{
	unsigned int time;
	t_time t;
	time = 0;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

unsigned int reel_time(unsigned int start_time)
{
	t_time t;
	unsigned int timestamp;
	unsigned int timenow;

	gettimeofday(&t, NULL);
	timenow = (t.tv_sec * 1000 + t.tv_usec / 1000);
	timestamp = timenow - start_time;
	printf("starttime : %u,timenow : %u, timestamp : %u\n", start_time, timenow, timestamp);
	return (timestamp);
}

int free_all(int i, t_arg *arg, t_philo *philo_st, pthread_t *philo_th)
{
	if (i == 0)
		free(arg);
	else if (i == 1)
	{
		free(arg);
		philo_st->arg = NULL;
		free(philo_st);
	}
	else if (i == 2)
	{
		free(arg);
	//	free(fork);
		philo_st->arg = NULL;
		philo_st->fork = NULL;
		free(philo_st);
	}
	return (0);
} /*penser a free le contenu des tableaux : philo_th, fork, philo_st*/
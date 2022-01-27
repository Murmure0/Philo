/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:01:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/27 10:45:17 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
	//printf("\nstarttime : %u,timenow : %u, timestamp : %u\n", start_time, timenow, timestamp);
	return (timestamp);
}

// int my_usleep(unsigned int time_to)
int my_usleep(t_philo *philo_st, unsigned int time_to, char flag)
{
	if (flag == 'e')
		while ((reel_time(philo_st->arg->start) - philo_st->last_meal) != time_to)
			usleep(500);
	else if (flag == 's')
		while ((reel_time(philo_st->arg->start) - philo_st->last_meal) - philo_st->arg->time_to_eat != time_to)
			usleep(500);
	return (0);
}
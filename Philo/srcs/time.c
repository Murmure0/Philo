/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelle <maelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:01:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/02/08 10:08:02 by maelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned int	my_get_time(void)
{
	t_time			t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}

unsigned int	real_time(unsigned int start_time)
{
	unsigned int	timestamp;
	unsigned int	timenow;
	t_time			t;

	gettimeofday(&t, NULL);
	timenow = (t.tv_sec * 1000 + t.tv_usec / 1000);
	timestamp = timenow - start_time;
	return (timestamp);
}

void	ft_usleep(t_philo *philo_st, unsigned int time_to)
{
	unsigned int	start_time;

	start_time = 0;
	start_time = my_get_time();
	while ((my_get_time() - start_time) < time_to)
	{
		if (philo_st->arg->dead_philo)
			break ;
		usleep(500);
	}
}

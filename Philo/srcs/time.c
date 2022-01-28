/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:01:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/28 15:51:19 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	my_get_time(void)
{
	unsigned int	time;
	t_time			t;

	time = 0;
	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
}

unsigned int	reel_time(unsigned int start_time)
{
	unsigned int	timestamp;
	unsigned int	timenow;
	t_time			t;

	gettimeofday(&t, NULL);
	timenow = (t.tv_sec * 1000 + t.tv_usec / 1000);
	timestamp = timenow - start_time;
	return (timestamp);
}

// int	my_usleep(t_philo *philo_st, unsigned int time_to, char flag)
// {


// 	if (flag == 'e')
// 		while ((reel_time(philo_st->arg->start) - philo_st->last_meal)
// 			<= time_to)
// 			usleep(50);
// 	else if (flag == 's')
// 		while ((reel_time(philo_st->arg->start) - philo_st->last_meal)
// 			- philo_st->arg->time_to_eat <= time_to)
// 			usleep(50);
// 	return (0);
// }

void	ft_usleep(unsigned int time_to)
{
	unsigned int	start_time;

	start_time = 0;
	start_time = my_get_time();
	while ((my_get_time() - start_time) < time_to)
		usleep(500);
}

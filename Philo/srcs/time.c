/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/26 11:01:00 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/04 15:05:10 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

unsigned int	my_get_time(void)
{
	t_time			t;

	gettimeofday(&t, NULL);
	return (t.tv_sec * 1000 + t.tv_usec / 1000);
}


// unsigned int	real_time(unsigned int start_time)
// {
// 	unsigned long	timestamp;
// 	unsigned long	timenow;
// 	t_time			t;

// 	unsigned long tim = t.tv_sec * 1000;
// 	int usec = t.tv_usec / 1000;
// 	gettimeofday(&t, NULL);
// 	timenow = (tim + usec);
// 	timestamp = timenow - start_time;
// 	return (timestamp);
// }

unsigned int	real_time(unsigned int start_time)
{
	unsigned long	timestamp;
	unsigned long	timenow;
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
		if (check_death(philo_st))
			break ;
		usleep(500);
	}
}

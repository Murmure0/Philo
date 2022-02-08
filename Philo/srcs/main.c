/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelle <maelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:20:04 by mberthet          #+#    #+#             */
/*   Updated: 2022/02/08 10:52:45 by maelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

int	main(int argc, char **argv)
{
	t_arg			*arg;
	t_philo			*philo_st;
	pthread_mutex_t	*fork;
	pthread_t		*philo_th;

	if (ft_init_arg_and_check(&arg, argc, argv)
		|| ft_creat_philo_st_and_fork(&philo_st, &fork, &arg)
		|| ft_init_philost_mutex(&philo_st, &arg, &fork)
		|| ft_creat_philo_th(&philo_st, &arg, &fork, &philo_th))
		return (-1);
	else if (ft_pth_creat_philo(arg, philo_th, philo_st))
	{
		ft_clean(arg, philo_st, fork, philo_th);
		return (-1);
	}
	else if (ft_join_pthread(philo_th, arg, fork, philo_st))
		return (-1);
	ft_clean(arg, philo_st, fork, philo_th);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:20:04 by mberthet          #+#    #+#             */
/*   Updated: 2022/02/06 11:11:56 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	main(int argc, char **argv)
{
	t_arg			*arg;
	t_philo			*philo_st;
	pthread_mutex_t	*fork;
	pthread_t		*philo_th;

	if (ft_init_arg_and_check(&arg, argc, argv))
		return (-1);
	if (ft_creat_philost_and_fork(&philo_st, &fork, &arg))
		return (-1);
	if (ft_init_philost_mutex(&philo_st, &arg, &fork)
		|| ft_creat_philo_th(&philo_st, &arg, &fork, &philo_th))
		return (-1);
	if (ft_pth_creat_even(arg, philo_th, philo_st)
		|| ft_pth_creat_uneven(arg, philo_th, philo_st))
	{
		ft_clean(arg, philo_st, fork, philo_th);
		return (-1);
	}
	if (ft_join_pthread(philo_th, arg, fork, philo_st))
		return (-1);
	ft_clean(arg, philo_st, fork, philo_th);
	return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 17:19:41 by mberthet          #+#    #+#             */
/*   Updated: 2022/02/06 11:10:24 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	check_arg(int argc, char **argv)
{
	int	i;
	int	j;

	i = 0;
	if (argc < 5 || argc > 6)
	{
		printf("Wrong argument number : enter 4 or 5 numbers.\n");
		return (-1);
	}
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (!isnum(argv[i][j]))
			{
				printf("Wrong argument type : only positiv integer number.\n");
				return (-1);
			}
		}
	}
	return (0);
}

int	check_struct(t_arg *arg)
{
	if (arg->nb_philo == 0 || arg->nb_philo > 200)
	{
		printf("Number of philosophers must be between 1 and 200.\n");
		return (-1);
	}
	if (arg->time_to_die > 2147483647 || arg->time_to_eat > 2147483647
		|| arg->time_to_sleep > 2147483647)
	{
		printf("Please enter a correct amount of time.\n");
		return (-1);
	}
	else if (arg->time_to_die < 60 || arg->time_to_eat < 60
		|| arg->time_to_sleep < 60)
	{
		printf("Please enter a correct amount of time.\n");
		return (-1);
	}
	return (0);
}

int	ft_init_philost_mutex(t_philo **philo_st, t_arg **arg,
	pthread_mutex_t **fork)
{
	unsigned int	i;

	i = -1;
	while (++i < (*arg)->nb_philo)
	{
		(*philo_st)[i] = init_philo_st((*arg), i);
		(*philo_st)[i].fork = (*fork);
		if (pthread_mutex_init((*fork) + i, NULL))
		{
			free_all(2, (*arg), (*philo_st), (*fork));
			return (-1);
		}
	}
	return (0);
}

int	ft_creat_philo_th(t_philo **philo_st, t_arg **arg, pthread_mutex_t **fork,
	pthread_t **philo_th)
{
	(*philo_th) = malloc(sizeof(pthread_t) * (*arg)->nb_philo);
	if (!(*philo_th))
	{
		free_all(2, (*arg), (*philo_st), (*fork));
		return (-1);
	}
	return (0);
}

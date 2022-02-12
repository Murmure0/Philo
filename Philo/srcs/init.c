/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maelle <maelle@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:14:46 by mberthet          #+#    #+#             */
/*   Updated: 2022/02/12 13:45:42 by maelle           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo.h"

static void	inside_init_arg(int argc, char **argv, t_arg *arg)
{
	arg->nb_philo = ft_atoi(argv[1]);
	arg->time_to_die = ft_atoi(argv[2]);
	arg->time_to_eat = ft_atoi(argv[3]);
	arg->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		arg->nb_meal = ft_atoi(argv[5]);
	else
		arg->nb_meal = 0;
}

t_arg	*init_arg(int argc, char **argv)
{
	t_arg	*arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	inside_init_arg(argc, argv, arg);
	arg->start = my_get_time();
	arg->nb_meal_ok = 0;
	arg->dead_philo = 0;
	if (pthread_mutex_init(&(arg->speak), NULL))
	{
		free(arg);
		return (NULL);
	}
	return (arg);
}

t_philo	init_philo_st(t_arg *arg, int i)
{
	t_philo	philo_st;

	philo_st.arg = arg;
	philo_st.num_philo = i + 1;
	philo_st.last_meal = 0;
	philo_st.nb_meal = 0;
	philo_st.nb_meal_ok = 0;
	return (philo_st);
}

int	ft_init_arg_and_check(t_arg **arg, int argc, char **argv)
{
	if (check_arg(argc, argv))
		return -1;
	*arg = init_arg(argc, argv);
	if (!(*arg))
		return (-1);
	if (check_struct(*arg))
	{
		pthread_mutex_destroy(&(*arg)->speak);
		free_all(*arg, NULL, NULL, NULL);
		return (-1);
	}
	return (0);
}

int	ft_creat_philo_st_and_fork(t_philo **philo_st, pthread_mutex_t **fork,
	t_arg **arg)
{
	*philo_st = malloc(sizeof(t_philo) * (*arg)->nb_philo);
	if (!(*philo_st))
	{
		pthread_mutex_destroy(&(*arg)->speak);
		free_all((*arg), NULL, NULL, NULL);
		return (-1);
	}
	*fork = malloc(sizeof(pthread_mutex_t) * (*arg)->nb_philo);
	if (!(*fork))
	{
		pthread_mutex_destroy(&(*arg)->speak);
		free_all((*arg), (*philo_st), NULL, NULL);
		return (-1);
	}
	return (0);
}

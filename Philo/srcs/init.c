/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:14:46 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/26 13:27:57 by mberthet         ###   ########.fr       */
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
	while(argv[++i])
	{
		j = -1;
		while(argv[i][++j])
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

t_arg *init_arg(int argc, char ** argv)
{	int		i;
	t_arg *arg;

	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	i = 0;
	while (++i < argc)
	{
		if (i == 1)
			arg->nb_philo = ft_atoi(argv[i]);
		if (i == 2)
			arg->time_to_die = ft_atoi(argv[i]);
		if (i == 3)
			arg->time_to_eat = ft_atoi(argv[i]);
		if (i == 4)
			arg->time_to_sleep = ft_atoi(argv[i]);
		if (i == 5)
			arg->nb_meal = ft_atoi(argv[i]);
		else if (i == 4)
			arg->nb_meal = 0;
	}
	arg->start = my_get_time();
	arg->nb_meal_ok = 0;
	arg->dead_philo = 0;
	if (pthread_mutex_init(&(arg->speak), NULL))
		return (NULL);
	return (arg);
}

int	check_struct(t_arg *arg)
{
	if (arg->nb_philo == 0 || arg->nb_philo > 200)
	{
		printf("Wrong number of philosoph, enter between 1 and 200 philo please.\n");
		return (-1);
	}
	if (arg->time_to_die > 10000 || arg->time_to_eat > 10000 
	|| arg->time_to_sleep > 10000)
	{
		printf("Please enter a correct amount of time.\n");
		return (-1);
	}
	else if (arg->time_to_die < 60 || arg->time_to_eat < 60 
	|| arg->time_to_sleep < 60)
	{
		printf("You're trying to test under 60ms, dont't do that please.\n");
		return (-1);
	}
	return (0);
}

t_philo init_philo_st(t_arg *arg, int i)
{
	t_philo philo_st;
	philo_st.arg = arg;
	philo_st.num_philo = i + 1;
	philo_st.last_meal = 0;
	philo_st.nb_meal = 0;
	philo_st.nb_meal_ok = 0;
	return (philo_st);
}
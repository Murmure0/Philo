/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/22 11:08:30 by maelle            #+#    #+#             */
/*   Updated: 2022/01/25 10:28:50 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

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

int	init_struct(int argc, char **argv, t_arg **arg)
{
	int	i;

	i = 0;
	while (argv[++i])
	{
		if (i == 1)
			(*arg)->nb_philo = ft_atoi(argv[i]);
		else if (i == 2)
			(*arg)->time_to_die = ft_atoi(argv[i]);
		else if (i == 3)
			(*arg)->time_to_eat = ft_atoi(argv[i]);
		else if (i == 4)
			(*arg)->time_to_sleep = ft_atoi(argv[i]);
		else if (i == 5)
			(*arg)->nb_time_eat = ft_atoi(argv[i]);
	}
	if (argc < 6)
		(*arg)->nb_time_eat = 0;
	return (0);
}

int	check_struct(t_arg *arg)
{
	if (arg->nb_philo == 0 || arg->nb_philo > 200)
	{
		printf("Wrong number of philosoph, enter between 1 and 200 philo 
		please.\n");
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
t_arg *parse(int argc, char **argv)
{
	t_arg *arg;
	int i;

	i = 0;
	arg = malloc(sizeof(t_arg));
	if (!arg)
		return (NULL);
	if (check_arg(argc, argv))
		return(NULL);

	init_struct(argc, argv, &arg);
	if (check_struct(arg))
		return (NULL);
	return (arg);
}
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:29:11 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/27 12:57:42 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned int	ft_atoi(const char *str)
{
	long	res;

	res = 0;
	if (*str == '\0')
		return (0);
	while (*str)
		while (*str >= '0' && *str <= '9')
			res = res * 10 + (*str++ - '0');
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


int free_all(int i, t_arg *arg, t_philo *philo_st, pthread_t *philo_th)
{
	if (i == 0)
		free(arg);
	else if (i == 1)
	{
		free(arg);
		philo_st->arg = NULL;
		free(philo_st);
	}
	else if (i == 2)
	{
		free(arg);
	//	free(fork);
		philo_st->arg = NULL;
		philo_st->fork = NULL;
		free(philo_st);
	}
	return (0);
} /*penser a free le contenu des tableaux : philo_th, fork, philo_st*/
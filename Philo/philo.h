/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:10:42 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/24 17:35:11 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>

typedef struct timeval t_time;

typedef struct s_arg{
	unsigned int	nb_philo;
	unsigned int	time_to_die;
	unsigned int	time_to_eat;
	unsigned int	time_to_sleep;
	unsigned int	nb_meal;
	unsigned int	start;
	unsigned int	nb_meal_ok;
	unsigned int	dead_philo;
	pthread_mutex_t	speak;
}				t_arg;

typedef struct s_philo{
	t_arg			*arg;
	unsigned int	num_philo;
	unsigned int	last_meal;
	unsigned int	nb_meal;
	unsigned int	nb_meal_ok;
	pthread_mutex_t	*fork;
}				t_philo;

#endif
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:10:42 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/25 11:42:42 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>

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

/* init */
int				check_arg(int argc, char **argv);
int				check_struct(t_arg *arg);
t_arg			*init_arg(int argc, char ** argv);
t_philo			init_philo_st(t_arg *arg, int i);

/* basics utils */
int				isnum(int n);
unsigned int	ft_atoi(const char *str);
unsigned int	my_get_time(void);
unsigned int reel_time(unsigned int time);
int free_all(int i, t_arg *arg, t_philo *philo_st, pthread_t *philo_th);
#endif
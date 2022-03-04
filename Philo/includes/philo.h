/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:10:42 by mberthet          #+#    #+#             */
/*   Updated: 2022/03/04 16:20:38 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <stdio.h>
# include <sys/time.h>
# include <unistd.h>
# include <string.h>

typedef struct timeval	t_time;

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
	pthread_mutex_t	death;
}				t_arg;

typedef struct s_philo{
	t_arg			*arg;
	unsigned int	num_philo;
	unsigned int	last_meal;
	unsigned int	nb_meal;
	unsigned int	nb_meal_ok;
	pthread_mutex_t	meal;
	pthread_mutex_t	*fork;
}				t_philo;

/* check */
int				check_arg(int argc, char **argv);
int				check_struct(t_arg *arg);
int				ft_init_philost_mutex(t_philo **philo_st, t_arg **arg,
					pthread_mutex_t **fork);
int				ft_creat_philo_th(t_philo **philo_st, t_arg **arg,
					pthread_mutex_t **fork, pthread_t **philo_th);

/* init */
t_arg			*init_arg(int argc, char **argv);
t_philo			init_philo_st(t_arg *arg, int i);
int				ft_init_arg_and_check(t_arg **arg, int argc, char **argv);
int				ft_creat_philo_st_and_fork(t_philo **philo_st,
					pthread_mutex_t **fork, t_arg **arg);

/* process */
int				ft_join_pthread(pthread_t *philo_th, t_arg *arg,
					pthread_mutex_t *fork, t_philo *philo_st);
int				ft_pth_creat_philo(t_arg *arg, pthread_t *philo_th,
					t_philo *philo_st);

/* basics utils */
unsigned int	ft_atoi(const char *str);
int				isnum(int n);
void			ft_clean(t_arg *arg, t_philo *philo_st, pthread_mutex_t *fork,
					pthread_t *philo_th);
int				free_all(t_arg *arg, t_philo *philo_st,
					pthread_mutex_t *fork, pthread_t *philo_th);
int				check_last_meal(t_philo *philo_st);

/* routine */
int				philo_eat(t_philo *philo_st);
int				philo_sleep(t_philo *philo_st);
int				philo_think(t_philo *philo_st);
int				routine(t_philo *philo_st);
void			*routine_one(void *data);

/* routine utils */
void			unlock_fork(t_philo *philo_st);
int				my_printf(t_philo *philo_st, char *str);
int				take_fork_eat(int num_fork_r, int num_fork_l,
					t_philo *philo_st);

/* routine utils death */
int	check_death(t_philo *philo_st);
void			*death(void *data);
void			dead_unlock_fork(t_philo *philo_st);

/* time */
unsigned int	my_get_time(void);
unsigned int	real_time(unsigned int time);
void			ft_usleep(t_philo *philo_st, unsigned int time_to);

#endif
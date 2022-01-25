/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:20:04 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/25 13:56:51 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"



int my_printf(int i, t_philo *philo_st, t_arg *arg)
{
	pthread_mutex_lock(&(philo_st->fork[i]));
	printf("At %u Me, philo %u, got my fork ! Yumyum incomming !\n", reel_time(arg->start), philo_st->num_philo);
	pthread_mutex_lock(&(philo_st->fork[i-1]));
	printf("At %u Me, philo %u, got second fork ! Yumyum !\n\n", reel_time(arg->start), philo_st->num_philo);
	pthread_mutex_unlock(&(philo_st->fork[i]));
	pthread_mutex_unlock(&(philo_st->fork[i-1]));
	return (0);
}


void *routine(void *data)
{
	t_philo *philo_st;

	
	philo_st = malloc(sizeof(philo_st));
	philo_st = (t_philo *)data;
	int i;
	i = philo_st->num_philo;

	/*while(1)
	philo_eat
	philo_sleep
	philo_think
	check si philo mort
	si philo mort : lock de speak pour que plus personne ne puisse parler*/
	pthread_mutex_lock(&(philo_st->arg->speak));
	printf("Hello I'm %u\n", i);
	my_printf(i, philo_st, philo_st->arg);
	pthread_mutex_unlock(&(philo_st->arg->speak));
	return (0);
}

int main(int argc, char **argv)
{
	t_arg	*arg;
	t_philo	*philo_st;
	pthread_mutex_t *fork;
	pthread_t	*philo_th;

	// if (check_arg(argc, argv))
	// 	return (-1);
	// arg = malloc(sizeof(t_arg)); //recup les arguments passés au programme
	// if (!arg)
	// 	return(-1);
	arg = init_arg(argc, argv);
	if (!arg)
		return (-1);
	if (check_arg(argc, argv) || check_struct(arg))
	{
		free_all(0, arg, philo_st, philo_th);
		return (-1);
	}
	printf("nb philo : %u\ntime to die : %u\ntime to eat : %u\ntime to sleep : %u\nnb meal : %u\ntime at start : %u\nnb meal ok :%u\ndead philo : %u\n", arg->nb_philo, arg->time_to_die, arg->time_to_eat, arg->time_to_sleep, arg->nb_meal, arg->start, arg->nb_meal_ok, arg->dead_philo);

	philo_st = malloc(sizeof(t_philo) * arg->nb_philo);
	if (!philo_st)
	{
		free_all(0, arg, philo_st, philo_th);
		return (-1);
	} //tab de struct de philo : 1/philo
	fork = malloc(sizeof(pthread_mutex_t) * arg->nb_philo); //tab de fork = nb philo;
	if (!fork)
	{
		free_all(1, arg, philo_st, philo_th);
	}
	int i = -1;
	while(++i < arg->nb_philo)
	{
		philo_st[i].fork = fork; //tab de fork accessible via philo_st;
		philo_st[i] = init_philo_st(arg, i);
		if (!philo_st)
			return (-1);
		printf("Numero du philo : %u\n", philo_st[i].num_philo);
		if (pthread_mutex_init(fork + i, NULL)) //&str[i] == str+i mais en plus lent
			return (-1);
	}

	philo_th = malloc(sizeof(pthread_t) * arg->nb_philo); //on creer le nb de thread correspondant au nb de philo
	
	i = -1;
	while (++i < arg->nb_philo)
	{
		if (pthread_create(philo_th + i, NULL, &routine, (void *)(philo_st + i)))
			return (-1);	
	}

	i = -1;
	while (++i < arg->nb_philo)
		pthread_join(philo_th[i], NULL);

	/*section free*/
	free_all(2, arg, philo_st, philo_th);
	/*free(arg);
	free(fork);
	free(philo_st);
	free(philo_th);*/
	return (0);
}
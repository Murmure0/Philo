/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:20:04 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/27 17:00:54 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int main(int argc, char **argv)
{
	t_arg	*arg;
	t_philo	*philo_st;
	pthread_mutex_t *fork;
	pthread_t	*philo_th;
	pthread_t	check_death;

	
	arg = init_arg(argc, argv); //initialisation de la structure qui prend les arguments & check qu'ils sont ok
	if (!arg)
		return (-1);
	if (check_arg(argc, argv) || check_struct(arg))
	{
		free_all(0, arg, philo_st, philo_th);
		return (-1);
	}
	
	philo_st = malloc(sizeof(t_philo) * arg->nb_philo); //creat tableau de struct : 1 par philo
	if (!philo_st)
	{
		free_all(0, arg, philo_st, philo_th);
		return (-1);
	} //tab de struct de philo : 1/philo

	fork = malloc(sizeof(pthread_mutex_t) * arg->nb_philo); //creat tab de fork = nb philo;
	if (!fork)
	{
		free_all(1, arg, philo_st, philo_th);
	}
	int i = -1;
	while(++i < arg->nb_philo) //on initialise chaque struct de philo & on init. les mutex fork
	{
		philo_st[i] = init_philo_st(arg, i); //init des var du tab a 0
		philo_st[i].fork = fork; //tab des fork accessible via philo_st;
		if (pthread_mutex_init(fork + i, NULL)) //&str[i] == str+i mais en plus lent
			return (-1);
	}
	philo_th = malloc(sizeof(pthread_t) * arg->nb_philo); //creat nb de thread correspondant au nb de philo
	i = -1;
	while (++i < arg->nb_philo)
	{
		if (pthread_create(philo_th + i, NULL, &routine_one, (void *)(philo_st + i)))
			return (-1);
	}
	i = -1;
	while (++i < arg->nb_philo)
	{
		if (pthread_join(philo_th[i], NULL))
			return (-1);
	}

	pthread_mutex_unlock(&arg->speak);
	pthread_mutex_destroy(&(arg->speak));
	i = -1;
	while (++i < arg->nb_philo)
	{
		pthread_mutex_unlock(fork +i);
		pthread_mutex_destroy(fork + i);
		pthread_detach(philo_th[i]);
	}
	//pthread_detach(check_death);
	/*section free*/
	// free_all(2, arg, philo_st, philo_th);
	/*free(arg);
	free(fork);
	free(philo_st);
	free(philo_th);*/
	return (0);
}
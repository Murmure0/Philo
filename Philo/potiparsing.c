/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   potiparsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 09:20:04 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/24 17:57:44 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/time.h>
#include "philo.h"
#include <unistd.h>

unsigned int ft_atoi(const char *str)
{
	long	res;

	res = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + (*str++ - '0');
	}
	return (res);
}

unsigned int my_get_time(void)
{
	unsigned int time;
	t_time t;
	time = 0;

	gettimeofday(&t, NULL);
	time = t.tv_sec * 1000 + t.tv_usec / 1000;
	return (time);
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

// void	blabla(t_philo *philo_st)
// {
// 	pthread_mutex_lock(&(philo_st[i].fork[i]))
// }


void *ft_thread(void *data)
{
	t_philo *philo_st;

	philo_st = malloc(sizeof(philo_st));
	philo_st = (t_philo *)data;
	int i;
	i = philo_st->num_philo;

	pthread_mutex_lock(&(philo_st->arg->speak));
	// blabla(philo_st);
	printf("Hello I'm %u\n", i);
	pthread_mutex_unlock(&(philo_st->arg->speak));

	return (0);
}

int main(int argc, char **argv)
{
	t_arg	*arg;
	t_philo	*philo_st;
	pthread_mutex_t *fork;
	pthread_t	*philo_th;

	arg = malloc(sizeof(t_arg)); //recup les arguments passés au programme
	arg = init_arg(argc, argv);
	if (!arg)
		return (-1);
	printf("nb philo : %u\ntime to die : %u\ntime to eat : %u\ntime to sleep : %u\nnb meal : %u\ntime at start : %u\nnb meal ok :%u\ndead philo : %u\n", arg->nb_philo, arg->time_to_die, arg->time_to_eat, arg->time_to_sleep, arg->nb_meal, arg->start, arg->nb_meal_ok, arg->dead_philo);

	philo_st = malloc(sizeof(t_philo) * arg->nb_philo); //tab de struct de philo : 1/philo
	fork = malloc(sizeof(pthread_mutex_t) * arg->nb_philo); //tab de fork = nb philo;
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
		if (pthread_create(philo_th + i, NULL, &ft_thread, (void *)(philo_st + i)))
			return (-1);	
	}

	i = -1;
	while (++i < arg->nb_philo)
		pthread_join(philo_th[i], NULL);
	//free(arg);*/
	return (0);
}
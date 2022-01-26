/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 16:10:14 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/26 15:56:25 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_struct
{
	int				n;
	pthread_mutex_t	mutex;
} t_struct;

void *ft_thread(void *data)
{
	t_struct *s = (t_struct *)data;
	pthread_mutex_lock(&(s->mutex));
	printf("Im thread! Here's a number : %d\n", s->n);
	s->n++;
	pthread_mutex_unlock(&(s->mutex));
	return (NULL);
}

int main(int argc, char **argv)
{
	t_struct *s = malloc(sizeof(t_struct));
	s->n = 0;
	pthread_mutex_init(&(s->mutex), NULL);
	pthread_t *philos = malloc(sizeof(pthread_t) * 1000);
	int i = -1;
	while (++i < 1000)
		pthread_create(philos + i, (void *)0, &ft_thread, (void *)(s));
	i = -1;
	while (++i < 1000)
		pthread_join(philos[i], NULL);
	pthread_mutex_unlock(&(s->mutex));
	pthread_mutex_destroy(&(s->mutex));
	printf("The main is dead!\n");
}


// int main(int argc, char **argv)
// {
// 	int *n = malloc(sizeof(int));
// 	*n = 5;
// 	pthread_t thread;
// 	pthread_create(&thread, (void *)0, &ft_thread, (void *)n);
// 	pthread_join(thread, NULL);
// 	printf("The main is dead!\n");
// }

// int main(int argc, char **argv)
// {
// 	int *numbers = malloc(sizeof(int) * 5);
// 	pthread_t *philos = malloc(sizeof(pthread_t) * 5);
// 	int i = -1;
// 	while (++i < 5)
// 	{
// 		numbers[i] = i;
// 		pthread_create(philos + i, (void *)0, &ft_thread, (void *)(numbers + i));
// 	}
// 	i = -1;
// 	while (++i < 5)
// 		pthread_join(philos[i], NULL);
// 	printf("The main is dead!\n");
// }

#include <sys/time.h>
#include <unistd.h>

typedef struct timeval t_time;

int main(void)
{
	t_time t;
	gettimeofday(&t, NULL);
	printf("How many time since 1970 ?\n%ld seconds and %d microseconds\n", t.tv_sec, t.tv_usec);
	usleep(500);
	gettimeofday(&t, NULL);
	printf("And now ?\n%ld seconds and %d microseconds\n", t.tv_sec, t.tv_usec);
}

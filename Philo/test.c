/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 13:01:08 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/21 15:35:32 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

typedef struct s_struct
{
	int *n;
	pthread_mutex_t mutex;
} t_struct;

void *my_philo_say_hi(void *arg)
{
	int *n;
	n = malloc(sizeof(int));
	*n = 11;
	printf("thread pointer : %p\n", n);
	printf("thread result : %d\n", *n);

	t_struct *mutex = (t_struct *)arg;
	pthread_mutex_lock(&(mutex->mutex));
	printf("Hello, I'm philo number %d.\n", *mutex->n);
	(*mutex->n)++;
	pthread_mutex_unlock(&(mutex->mutex));
	return ((void*)n);
}

void *my_second_philo(void *arg)
{
	t_struct *mutex = (t_struct *)arg;
	pthread_mutex_lock(&(mutex->mutex));
	printf("Hello, I'm philo number %d, yeay.\n", *mutex->n);
	(*mutex->n)++;
	pthread_mutex_unlock(&(mutex->mutex));
	return (0);
}

int main(int argc, char **argv)
{
	pthread_t *philo;
	t_struct *mutex;
	int *n;
	int m;
	int i;
	void * n;

	i = 0;
	philo = malloc(sizeof(pthread_t)* 2);
	n = malloc(sizeof(int));
	mutex = malloc(sizeof(t_struct));
	mutex->n = malloc(sizeof(int));
	*mutex->n = 1;
	pthread_mutex_init(&(mutex->mutex), NULL);
	pthread_create(philo , NULL, &my_philo_say_hi, (void *)mutex);
	pthread_create(philo + 1, NULL, &my_second_philo, (void *)mutex);
	pthread_join(philo[i], (void **)&n);
	printf("retour du philo num %d : %d.\n",1, *n);
	i++;
	pthread_join(philo[i], NULL);

	printf("The end of %d philo.\n", (*mutex->n) - 1);
	pthread_mutex_unlock(&(mutex->mutex));
	pthread_mutex_destroy(&(mutex->mutex));
	return (0);
}

/*
	typedef struct s_tab
	{
		int n; //4bytes
		struct s_tab *next; //8 bytes
	} t_tab;

	int main(void)
	{
		t_tab *t;
		t = malloc(sizeof(t_tab) * 5);
	}
*/

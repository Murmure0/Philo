/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   example.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/24 13:13:12 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/24 13:13:12 by mberthet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <pthread.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/times.h>

typedef struct s_struct
{
	pthread_t	philo;
	int			num;
} t_struct;

typedef struct s_all
{
	t_struct *philos;
} t_all;

int main(void)
{
	t_all all;
	all.philos = malloc(sizeof(t_struct) * 5);
	for (int i = 0; i < 5; i++)
}
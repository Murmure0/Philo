/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basics_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mberthet <mberthet@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:29:11 by mberthet          #+#    #+#             */
/*   Updated: 2022/01/28 14:38:30 by mberthet         ###   ########.fr       */
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
	if (n < '0' || n > '9')
		return (0);
	return (1);
}
/*
size_t ft_strlen(const char *str)
{
	size_t i;
	i = 0;
	while (*str)
	{
		i++;
	}
	return(i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	len_src;
	size_t	len_dst;

	i = 0;
	len_src = ft_strlen(src);
	len_dst = ft_strlen(dst);
	if (dstsize - 1 < len_dst || dstsize == 0)
		return (len_src + dstsize);
	while (i < dstsize - len_dst - 1 && src[i])
	{
		dst[len_dst + i] = src[i];
		i++;
	}
	dst[len_dst + i] = '\0';
	return (len_dst + len_src);
}


unsigned int	ft_count(unsigned int n)
{
	unsigned int	i;

	i = 0;
	if (!n)
		return (1);
	while (n)
	{
		i++;
		n /= 10;
	}
	return (i);
}

char	*ft_itoa(unsigned int n)
{
	unsigned char	*str;
	int				j;

	j = ft_count(n);
	str = (unsigned char *)malloc(sizeof(char) * (j + 1));
	if (!str)
		return (NULL);
	*(str + j) = '\0';
	while (j-- > -1)
	{
		*(str + j) = (n % 10) + '0';
		n /= 10;
	}
	return ((char *)str);
}



int	free_all(int i, t_arg *arg, t_philo *philo_st, pthread_t *philo_th)
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
		philo_st->arg = NULL;
		philo_st->fork = NULL;
		free(philo_st);
	}
	return (0);
}*/

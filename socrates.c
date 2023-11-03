/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socrates.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:40:01 by saazcon-          #+#    #+#             */
/*   Updated: 2023/11/03 15:59:06 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long	ft_time(void)
{
	struct timeval	time;
	unsigned long	tl;
	unsigned long	sg;
	unsigned long	ms;

	gettimeofday(&time, NULL);
	sg = (time.tv_sec * 1000);
	ms = (time.tv_usec / 1000);
	tl = sg + ms;
	return (tl);
}

void	ft_usleep(t_philo	*ph, unsigned long time)
{
	unsigned long	start;

	if (ft_is_dead(ph))
		return ;
	start = ft_time() + time;
	while (ft_time() < start)
		usleep(100);
}

void	ft_destroy_mutex(t_philo	*ph)
{
	pthread_mutex_destroy(&ph->data->mutex_print);
	pthread_mutex_destroy(&ph->data->mutex_dead);
	pthread_mutex_destroy(&ph->data->mutex_stuff);
	pthread_mutex_destroy(&ph->data->mutex_end);
}

void	ft_free_round_list(t_philo	*ph)
{
	t_philo	*aux;
	t_philo	*top;

	ft_destroy_mutex(ph);
	top = ph->next;
	ph->next = NULL;
	while (top)
	{
		pthread_mutex_destroy(&ph->mutex_life);
		pthread_mutex_destroy(&ph->fork);
		aux = top;
		top = top->next;
		free(aux);
	}
}

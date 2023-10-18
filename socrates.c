/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socrates.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:40:01 by saazcon-          #+#    #+#             */
/*   Updated: 2023/10/18 18:18:41 by saazcon-         ###   ########.fr       */
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

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = ft_time() + time;
	while (ft_time() < start)
		usleep(100);
}

void	ft_print(t_philo	*ph, unsigned long time, char *msg)
{
	pthread_mutex_lock(&ph->data->mutex);
	if ((!ph->data->dead) && (ph->data->stuffed < ph->data->num_philo))
		printf("%lums  %d %s\n", time, ph->name_ph, msg);
	pthread_mutex_unlock(&ph->data->mutex);
}

void	ft_stuffed(t_philo	*ph)
{
	ph->n_eated++;
	if (ph->n_eated == ph->data->must_eat)
	{
		pthread_mutex_lock(&ph->data->mutex);
		(*(ph->data)).stuffed++;
		pthread_mutex_unlock(&ph->data->mutex);
	}
}

void	ft_free_round_list(t_philo	*ph)
{
	t_philo	*aux;
	t_philo	*top;

	top = ph->next;
	ph->next = NULL;
	while (top)
	{
		pthread_mutex_destroy(&ph->fork);
		aux = top;
		top = top->next;
		free(aux);
	}
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socrates.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:40:01 by saazcon-          #+#    #+#             */
/*   Updated: 2023/10/17 22:57:08 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_stuffed(t_philo	*ph)
{
	pthread_mutex_lock(&ph->data->mutex);
	(*(ph->data)).stuffed++;
	pthread_mutex_unlock(&ph->data->mutex);
}

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

	start = ft_time() + time;
	while (ft_time() < start)
		usleep(100);
	ft_is_dead(ph);
}

void	ft_print(t_philo	*ph, unsigned long time, char *msg)
{
	ft_is_dead(ph);		//creo que esta linea no es necesaria y se optimiza todo mucho
	pthread_mutex_lock(&ph->data->mutex);
	if ((ph->data->dead) == 0 && (ph->data->stuffed < ph->data->num_philo))
		printf("%lums  %d %s\n", time, ph->name_ph, msg);
	pthread_mutex_unlock(&ph->data->mutex);
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

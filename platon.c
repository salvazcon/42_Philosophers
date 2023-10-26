/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   platon.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 14:57:26 by saazcon-          #+#    #+#             */
/*   Updated: 2023/10/26 15:05:43 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int ft_is_dead(t_philo *ph)
{
	int rt;

	rt = 0;
	pthread_mutex_lock(&ph->data->mutex_dead);
	if ((*(ph->data)).dead == 1)
		rt = 1;
	pthread_mutex_unlock(&ph->data->mutex_dead);
	return (rt);
}

void	ft_stuffed(t_philo	*ph, int	n_philo)
{
	if(ph->data->must_eat > 0)
	{
		ph->n_eated++;
		if (ph->n_eated == ph->data->must_eat)
		{
			pthread_mutex_lock(&ph->data->mutex_dead);
			(*(ph->data)).stuffed++;
			if ((ph->data->stuffed >= n_philo))
				(*(ph->data)).dead = 1;
			pthread_mutex_unlock(&ph->data->mutex_dead);
		}
	}
}

void	ft_print(t_philo	*ph, unsigned long time, char *msg)
{
	pthread_mutex_lock(&ph->data->mutex_print);
	if (!ft_is_dead(ph))
		printf("%lums  %d %s\n", time, ph->name_ph, msg);
	pthread_mutex_unlock(&ph->data->mutex_print);
}

void	ft_life(t_philo	*ph)
{
	pthread_mutex_lock(&ph->data->mutex_life);
	ph->t_life = ft_time();
	pthread_mutex_unlock(&ph->data->mutex_life);
}
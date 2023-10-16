/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   socrates.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:40:01 by saazcon-          #+#    #+#             */
/*   Updated: 2023/10/16 18:22:33 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_dead(t_philo	*ph)
{
	pthread_mutex_lock(&ph->data->mutex);
	if (ft_time() - ph->t_life > (unsigned long)ph->data->t_die && \
	!ph->data->dead)
	{
		printf("%lums %d a muerto.\n", ft_time() - ph->data->time, ph->name_ph);
		(*(ph->data)).dead = 1;
	}
	pthread_mutex_unlock(&ph->data->mutex);
	if ((ph->data->dead) || (ph->data->stuffed == ph->data->num_philo))
		return (1);
	return (0);
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

void	ft_usleep(unsigned long time)
{
	unsigned long	start;

	start = ft_time() + time;
	while (ft_time() < start)
		usleep(100);
}

void	ft_print(t_philo	*ph, unsigned long time, char *msg)
{
	if (ft_is_dead(ph))
		return ;
	pthread_mutex_lock(&ph->data->mutex);
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

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:22:46 by saazcon-          #+#    #+#             */
/*   Updated: 2023/10/31 15:29:52 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_dead_philo(t_philo *ph)
{
	while (!ft_is_dead(ph))
	{
		pthread_mutex_lock(&ph->mutex_life);
		if (ft_time() - ph->t_life >= (unsigned long)ph->data->t_die)
		{
			pthread_mutex_unlock(&ph->mutex_life);
			ft_print(ph, ft_time() - ph->data->time, "died");
			pthread_mutex_lock(&ph->data->mutex_dead);
			(*(ph->data)).dead = 1;
			pthread_mutex_unlock(&ph->data->mutex_dead);
			if (ph->data->num_philo == 1)
				pthread_mutex_unlock(&ph->fork);
		}
		else
			pthread_mutex_unlock(&ph->mutex_life);
		ph = ph->next;
	}
}

void	*ft_philo(void *arg)
{
	t_philo	*ph;

	ph = ((t_philo *)arg);
	if (!ph)
		return (NULL);
	if ((ph->name_ph % 2) == 0)
		ft_usleep(ph, ph->data->t_eat);
	ft_life(ph);
	while (!ft_is_dead(ph))
	{
		pthread_mutex_lock(&ph->fork);
		ft_print(ph, ft_time() - ph->data->time, "has taken a fork");
		pthread_mutex_lock(&ph->next->fork);
		ft_print(ph, ft_time() - ph->data->time, "has taken a fork");
		ft_print(ph, ft_time() - ph->data->time, "is eating");
		ft_usleep(ph, ph->data->t_eat);
		ft_life(ph);
		pthread_mutex_unlock(&ph->fork);
		pthread_mutex_unlock(&ph->next->fork);
		ft_stuffed(ph, ph->data->num_philo);
		ft_print(ph, ft_time() - ph->data->time, "is sleeping");
		ft_usleep(ph, ph->data->t_sleep);
		ft_print(ph, ft_time() - ph->data->time, "is thinking");
	}
	return (NULL);
}

void	ft_init_philo(t_philo *ph)
{
	int			i;
	pthread_t	*tid;

	tid = ft_calloc(sizeof(pthread_t), ph->data->num_philo + 1);
	if (!tid)
		return ;
	i = -1;
	while (++i < ph->data->num_philo)
	{
		if (pthread_create(&tid[i], NULL, ft_philo, ph) != 0)
			break ;
		ph = ph->next;
	}
	ft_dead_philo(ph);
	while (--i >= 0)
		pthread_join(tid[i], NULL);
	free(tid);
}

int	main(int argc, char **argv)
{
	t_philo	*ph;
	t_data	dt;

	if (ft_check_args(argc, argv))
		return (1);
	dt = ft_data(argc, argv);
	if (dt.error == 1)
		return (1);
	ph = ft_lst(&dt);
	if (!ph)
	{
		ft_destroy_mutex(ph);
		return (1);
	}
	ft_init_philo(ph);
	ft_free_round_list(ph);
	return (0);
}

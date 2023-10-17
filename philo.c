/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:22:46 by saazcon-          #+#    #+#             */
/*   Updated: 2023/10/17 22:55:38 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_dead(t_philo	*ph)
{
	pthread_mutex_lock(&ph->data->mutex);
	if (ft_time() - ph->t_life >= (unsigned long)ph->data->t_die && \
	!ph->data->dead)
	{
		printf("%lums  %d a muerto\n", ft_time() - ph->data->time, ph->name_ph);
		(*(ph->data)).dead = 1;
	}
	pthread_mutex_unlock(&ph->data->mutex);
	if ((ph->data->dead) || (ph->data->stuffed >= ph->data->num_philo))
		return (1);
	return (0);
}

void	*ft_unique_philo(void *arg)
{
	t_philo			*ph;

	ph = ((t_philo *)arg);
	if (!ph)
		return (NULL);
	pthread_mutex_lock(&ph->fork);
	printf("%lums  %d has taken a fork\n", ft_time() - ph->data->time, \
	ph->name_ph);
	printf("%dms  %d died\n", ph->data->t_die, ph->name_ph);
	pthread_mutex_unlock(&ph->fork);
	return (NULL);
}

void	*ft_philo(void *arg)
{
	t_philo		*ph;

	ph = ((t_philo *)arg);
	if (!ph)
		return (NULL);
	ph->t_life = ft_time();
	while (!ft_is_dead(ph))
	{
		pthread_mutex_lock(&ph->fork);
		ft_print(ph, ft_time() - ph->data->time, "has taken a fork");
		pthread_mutex_lock(&ph->next->fork);
		ft_print(ph, ft_time() - ph->data->time, "has taken a fork");
		ft_print(ph, ft_time() - ph->data->time, "is eating");
		ft_usleep(ph, ph->data->t_eat);
		ph->t_life = ft_time();
		ph->n_eated++;
		if (ph->n_eated == ph->data->must_eat)
			ft_stuffed(ph);
		pthread_mutex_unlock(&ph->fork);
		pthread_mutex_unlock(&ph->next->fork);
		ft_print(ph, ft_time() - ph->data->time, "is sleeping");
		ft_usleep(ph, ph->data->t_sleep);
		ft_print(ph, ft_time() - ph->data->time, "is thinking");
	}
	return (NULL);
}

void	ft_init_philo(t_philo	*ph)
{
	pthread_t	*tid;
	int			i;

	tid = ft_calloc(sizeof(pthread_t), ph->data->num_philo);
	if (!tid)
		return ;
	i = -1;
	if (1 == ph->data->num_philo)
		if (pthread_create(&tid[++i], NULL, ft_unique_philo, ph) != 0)
			free(tid);
	while (++i < ph->data->num_philo)
	{
		if ((ph->name_ph % 2) == 0)
			usleep(200);
		if (1 < ph->data->num_philo)
			if (pthread_create(&tid[i], NULL, ft_philo, ph) != 0)
				break ;
		ph = ph->next;
	}
	while (--i >= 0)
		pthread_join(tid[i], NULL);
	free(tid);
}

int	main(int argc, char **argv)
{
	t_philo	*ph;
	t_data	dt;
	//atexit(ft_leaks);	//leaks
	if (ft_check_args(argc, argv))
		return (1);
	dt = ft_data(argc, argv);	//control de errores
	ph = ft_lst(&dt);
	if (!ph)
	{
		pthread_mutex_destroy(&dt.mutex);
		return (1);	//puedo gestionar algo con el return, creo
	}
	ft_init_philo(ph);
	ft_free_round_list(ph);
	pthread_mutex_destroy(&dt.mutex);
	return (0);
}

/* void	ft_leaks(void)
{
	system("leaks -q philo");
} */
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:22:46 by saazcon-          #+#    #+#             */
/*   Updated: 2023/10/16 17:29:24 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

unsigned long	in_time(void)
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

int	ft_is_dead(t_philo	*ph)
{
	pthread_mutex_lock(&ph->data->mutex);
	if (in_time() - ph->t_life > (unsigned long)ph->data->t_die && \
	!ph->data->dead)
	{
		printf("%lums %d a muerto.\n", in_time() - ph->data->time, ph->name_ph);
		(*(ph->data)).dead = 1;
	}
	pthread_mutex_unlock(&ph->data->mutex);
	if ((ph->data->dead) || (ph->data->stuffed == ph->data->num_philo))
		return (1);
	return (0);
}

void	print(t_philo	*ph, unsigned long time, char *msg)
{
	if (ft_is_dead(ph))
		return ;
	pthread_mutex_lock(&ph->data->mutex);
	printf("%lums  %d %s\n", time, ph->name_ph, msg);
	pthread_mutex_unlock(&ph->data->mutex);
}

void	*ft_unique_philo(void *arg)
{
	t_philo		*ph;

	ph = ((t_philo *)arg);
	if (!ph)
		return (NULL);
	printf("%lums %d has taken a fork.\n", in_time() - ph->data->time, \
	ph->name_ph);
	printf("%lums %d is dead.\n", in_time() - ph->data->time, ph->name_ph);
	return (NULL);
}

void	*ft_philo(void *arg)
{
	t_philo		*ph;

	ph = ((t_philo *)arg);
	if (!ph)
		return (NULL);
	if ((ph->name_ph % 2) == 0)
		usleep(10);
	ph->t_life = in_time();
	while (!ft_is_dead(ph))
	{
		pthread_mutex_lock(&ph->fork);
		print(ph, in_time() - ph->data->time, "has taken a fork");
		pthread_mutex_lock(&ph->next->fork);
		print(ph, in_time() - ph->data->time, "has taken a fork");
		print(ph, in_time() - ph->data->time, "is eating");
		ph->n_eated++;
		if (ph->n_eated == ph->data->must_eat)
			ph->data->stuffed++;
		usleep(ph->data->t_eat * 1000);
		ph->t_life = in_time();
		pthread_mutex_unlock(&ph->fork);
		pthread_mutex_unlock(&ph->next->fork);
		print(ph, in_time() - ph->data->time, "is sleeping");
		usleep(ph->data->t_sleep * 1000);
		print(ph, in_time() - ph->data->time, "is thinking");
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
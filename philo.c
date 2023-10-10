
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:22:46 by saazcon-          #+#    #+#             */
/*   Updated: 2023/10/02 18:58:51 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_is_dead(t_philo	*ph)
{
	if(ph->data->smell_dead)
		return (1);
	if (in_time() - ph->t_life > (unsigned long)ph->data->t_die)
	{
		printf("%lums %d a muerto.\n", in_time() - ph->data->time, ph->name_ph);
		(*(ph->data)).smell_dead = 1;
		return (1);
	}
	return (0);
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

void	print(t_philo	*ph, unsigned long time, char *msg)
{
	pthread_mutex_lock(&ph->data->mutex);
	printf("%lums  %d %s\n", time, ph->name_ph, msg);
	pthread_mutex_unlock(&ph->data->mutex);
}

void	*ft_init_philo(void *arg)
{
	t_philo		*ph;

	ph = ((t_philo *)arg);
	if(!ph)
		return (NULL);
	if((ph->name_ph % 2) == 0)
	{
		printf("paron\n");
		usleep(100);
	}
	ph->t_life = in_time();
	while(1)
	{
		/* if (ft_is_dead(ph))
			break	; */
		pthread_mutex_lock(&ph->fork);
		print(ph, in_time() - ph->data->time, "has taken a fork");
		pthread_mutex_lock(&ph->next->fork);
		print(ph, in_time() - ph->data->time, "has taken a fork");
		/* if (ft_is_dead(ph))
		{
			pthread_mutex_unlock(&ph->fork);
			pthread_mutex_unlock(&ph->next->fork);
			break	;
		} */
		print(ph, in_time() - ph->data->time, "is eating");
		/* ph->n_eated++;
		if (philo->ate == philo->var->must_eat)
			philo->var->total_ate++; */
		usleep(ph->data->t_eat * 1000);
		ph->t_life = in_time();
		pthread_mutex_unlock(&ph->fork);
		pthread_mutex_unlock(&ph->next->fork);
		print(ph, in_time() - ph->data->time, "is sleeping");
		usleep(ph->data->t_sleep * 1000);
		print(ph, in_time() - ph->data->time, "is thinking");
	}
	return (0);
}

void	ft_philo(t_philo	*ph)
{
	pthread_t	*tid;
	int			i;

	tid = ft_calloc(sizeof(pthread_t), ph->data->num_philo);
	if(!tid)
		return ;	//ft_free
	i = -1;
	while(++i < ph->data->num_philo)
	{
		if (pthread_create(&tid[i], NULL, ft_init_philo, ph) != 0)
		{
			free(tid);
			return ;
		}
		ph = ph->next;
	}
	i = -1;
	while(++i < ph->data->num_philo)
		pthread_join(tid[i], NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*ph;
	t_data	dt;
	//atexit(ft_leaks);	//leaks
	if (ft_check_args(argc, argv))
		return (1);
	dt = ft_data(argc, argv);	//control de errores
	ph = ft_lst(&dt);	//los nodos unicos dan fallos
	if (!ph)
		return(1);
	ft_philo(ph);
	return (0);
}

/* void	ft_leaks(void)
{
	system("leaks -q philo");
} */
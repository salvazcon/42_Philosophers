
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

void	ft_init_philo(t_philo	*ph)
{
	//long long	time;

	printf("el hilo %d esta dandole.\n", ph->name_ph);
	pthread_mutex_lock(&ph->mutex);
	//time = 0;
	/* while(1) //quiero que no entre nadie hasta que tenga todos los hilos listos
	{
		gettimeofday(&ph->data->end_t, NULL);
		if(ph->data->smell_dead)
		{
			printf("%d ms: El hilo %d huele a muerto.\n", ph->data->end_t.tv_usec - ph->data->start_t.tv_usec, ph->name_ph);
			break ;
		}
		time = ph->data->end_t.tv_usec - ph->data->start_t.tv_usec;
		printf("%d ms: El hilo %d durme. \n", ph->data->end_t.tv_usec - ph->data->start_t.tv_usec, ph->name_ph);
		while(1)
		{
			if(ph->data->end_t.tv_usec - ph->data->start_t.tv_usec <  \
			ph->data->end_t.tv_usec - ph->data->start_t.tv_usec + \
			ph->data->t_sleep)
				break ;
		}
		pthread_mutex_unlock(&ph->mutex);
		if(ph->data->end_t.tv_usec - ph->data->start_t.tv_usec + time >= ph->data->t_die)
		{
			printf("%d ms: El hilo %d ha muerto\n", ph->data->end_t.tv_usec - ph->data->start_t.tv_usec, ph->name_ph);
			ph->data->smell_dead = 1;
			break;
		}
		printf("%d ms: El hilo %d esta pensando.\n",ph->data->end_t.tv_usec - ph->data->start_t.tv_usec, ph->name_ph);
	} */
	pthread_mutex_unlock(&ph->mutex);
}

void	*ft_funcion_philo(void *arg)
{
	t_philo	*ph;

	ph = ((t_philo *)arg);
	if(!ph)
		return (NULL);
	ph->data->num_exec++;
	while(1)
	{
		if(ph->data->num_exec == ph->data->num_philo)
		{
			printf("Listo.\n");
			gettimeofday(&ph->data->start_t, NULL); //no se si esto es realmente uitil.
			ft_init_philo(ph);
			break;
		}
		else
			printf("el hilo %d esta waiting al resto bro.\n", ph->name_ph);
	}
	return (NULL);
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
		if (pthread_create(&tid[i], NULL, ft_funcion_philo, ph) != 0)
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
	dt = ft_data(argc, argv);
	ph = ft_lst(&dt);
	if (!ph)
		return(1);
	ft_philo(ph);
	return (0);
}

/* void	ft_leaks(void)
{
	system("leaks -q philo");
} */
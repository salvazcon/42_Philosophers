/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:22:46 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/30 07:28:54 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_funcion_philo(void *arg)
{
	/* struct timeval	start_time;
	struct timeval	end_time;
	long long	time; */
	t_philo	*ph;

	ph = ((t_philo *)arg);
	if(!ph)
		return (NULL);
	printf("El hilo %d dice hola\n", ph->name_ph);
	/* while(1)
	{
		//gettimeofday(&dt->end_time, NULL);
		//time = (dt->end_time.tv_usec - dt->start_time.tv_usec);
		if()
			break;
	} */
	return (NULL);
}

void	ft_philo(t_philo	*ph)
{
	pthread_t	*tid;
	int			i;

	tid = ft_calloc(sizeof(pthread_t), ph->data.num_philo);
	if(!tid)
		return ;//ft_free
	i = -1;
	while(++i < ph->data.num_philo)
	{
		if (pthread_create(&tid[i], NULL, ft_funcion_philo, ph) != 0)
		{
			free(tid);
			return ;
		}
		ph = ph->next;
		usleep(100);
	}
	i = -1;
	while(++i < ph->data.num_philo) // En desorden pero es paralelo
		pthread_join(tid[i], NULL);
}

int	main(int argc, char **argv)
{
	t_philo	*ph;

	//atexit(ft_leaks);	//leaks
	if (ft_check_args(argv))
		return (1);
	ph = ft_lst(argc, argv);
	if (!ph)
		return(1);
	ft_philo(ph);
	return (0);
}

/* void	ft_leaks(void)
{
	system("leaks -q philo");
} */
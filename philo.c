/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 12:22:46 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/29 00:23:43 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	*ft_funcion_philo(void *arg)
{
	//t_data *ph = ((t_data *)arg);
	//printf("estas en el nodo -> %d\n", ph->curl_node);
	//ph->curl_node++;
	(void)arg;
	return (NULL);
}

void	ft_init_philo(t_data	*ph)
{
	pthread_t	*tid;
	int			i;

	tid = ft_calloc(sizeof(pthread_t), ph->num_philo + 1);
	if(!tid)
		return ;	//ft_free
	i = -1;
	while(i++ < ph->num_philo - 1)
	{
		printf("estas posicion de philo -> %d\n", i);
		ft_create_list(ph, i);
		if (pthread_create(&tid[i], NULL, ft_funcion_philo, &ph) != 0)
		{
			free(tid);
			return ;
		}
		usleep(100);
	}
	printf("espero al hilo num: %d \n", i);
	while(i-- > 0)// En desorden pero es paralelo
	{
		printf("cerramos el: %d \n", i);
		pthread_join(tid[i], NULL);
	}
	//pthread_detach(*tid);
	printf("salgo \n");
}

/* void	ft_leaks(void)
{
	system("leaks -q philo");
} */

int	main(int argc, char **argv)
{
	t_data	ph;

	//atexit(ft_leaks);	//leaks
	if (ft_check_args(argv))
		return (1);
	ft_data(argc, argv, &ph);
	ft_init_philo(&ph);
	printf("fin \n");
	return (0);
}

// como crear los tendores que esten muteados
// tienen que coger un tendor y esperar o coger los dos a la vez cuando esten libres
// una vez creados tiene que empezar a comer dormir y pensar
// Los hilos se crean y hasta que se mueren no hay que cerrarlos
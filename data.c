/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:18:09 by saazcon-          #+#    #+#             */
/*   Updated: 2023/10/04 11:58:34 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_check_args(int argc, char **argv)
{
	int	i;
	int	j;

	if (argc < 4 || argc > 6)
		return (1);
	i = 1;
	while (argv[i])
	{
		j = 0;
		if(argv[i][j] == '+')
			i++;
		while (argv[i][j])
		{
			if (!ft_isdigit(argv[i][j]) || argv[i][0] == '0')
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

t_data	ft_data(int argc, char **argv)
{
	t_data	dt;

	dt.num_philo = ft_atoi(argv[1]);
	dt.t_die = ft_atoi(argv[2]);
	dt.t_eat = ft_atoi(argv[3]);
	dt.t_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		dt.must_eat = ft_atoi(argv[5]);
	else
		dt.must_eat = -1;	//no existe el argv
	dt.num_exec = 0;
	dt.smell_dead = 0;				//false
	return	(dt);
}

t_philo	*ft_node(t_data	*dt, int name)
{
	t_philo *n;

	n = ft_calloc(sizeof(t_philo), 1);
	if (!n)
		return (NULL);
	pthread_mutex_init(&n->mutex, NULL);
	n->fork = 0;				//false
	n->n_eated = 0;				// puede que con calloc se llenen solos
	n->name_ph = name;
	n->data = dt;
	n->next = NULL;
	return (n);
}

t_philo	*ft_lst(t_data	*dt)
{
	t_philo	*head;
	t_philo	*aux;
	t_philo	*nd;
	int		i;

	i = dt->num_philo + 1;
	while(--i)
	{
		nd = ft_node(dt, i);
		if(!nd)
			return (NULL);
		if(i == dt->num_philo)	//primer nodo
			head = nd;
		else
		{
			aux = head;
			while (aux->next)
				aux = aux->next;
			if (i == 1)				//ultimo nodo
				nd->next = head;
			aux->next = nd;
		}
	}
	return (head);	
}

/* 	aux = head;
	i = ft_atoi(argv[1]) + 1;
	while(--i)
	{
		printf("este es el nombre del nodo %d\n", aux->name_ph);
		aux = aux->next;
	}

	aux = head;
	i = 5;
	while(--i)
	{
		printf("este es el numero antes %d\n", (*(aux->data)).t_sleep);
		(*(aux->data)).t_sleep++;
		printf("este es el numero despues %d\n", (*(aux->data)).t_sleep);
		aux = aux->next;
		printf("este es el numero del sig %d\n", (*(aux->data)).t_sleep);
	}
*/
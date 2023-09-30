/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:18:09 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/30 06:34:08 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
		dt.must_eat = -1;	//no ha llegado a existir el dato.
	return	(dt);
}

t_philo	*ft_node(int argc, char **argv, int name)
{
	t_philo *n;

	n = ft_calloc(sizeof(t_philo), 1);
	if (!n)
		return (NULL);
	//pthread_mutex_init(&n->fork, NULL); //anadir datos ??
	n->n_eated = 0;
	n->name_ph = name;
	n->next = NULL;
	n->data = ft_data(argc, argv);
	return (n);
}

t_philo	*ft_lst(int argc, char **argv)
{
	t_philo	*head;
	t_philo	*aux;
	t_philo	*nd;
	int		i;

	i = ft_atoi(argv[1]) + 1;
	while(--i)
	{
		nd = ft_node(argc, argv, i);
		if(!nd)
			return (NULL);
		if(i == nd->data.num_philo)	//primer nodo
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

int	ft_check_args(char **argv)
{
	int	i;
	int	j;

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
	if (i < 4 || i > 6)
		return (1);
	return (0);
}

/* 	aux = head;
	i = ft_atoi(argv[1]) + 1;
	while(--i)
	{
		printf("este es el nombre del nodo %d\n", aux->name_ph);
		aux = aux->next;
	} */
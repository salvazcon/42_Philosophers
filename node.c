/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   node.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:18:09 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/29 00:20:27 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

t_philo	*ft_create_node(t_philo *n, int id)
{
	//pthread_mutex_init(&n->fork, NULL); //anadir datos ??
	n = ft_calloc(sizeof(t_philo), 1);
	if (!n)
		return (NULL);	//ft_error(n);
	n->n_eated = 0;
	n->name_ph = id;
	n->next = NULL;
	return (n);
}

void	ft_create_list(t_data *ph, int id)
{
	t_philo	*n;
	t_philo	*aux;

	n = NULL;
	n = ft_create_node(n, id);
	if (!n)
		return ;
 	if (!ph->cab)
		ph->cab = n;
	else
	{
		aux = ph->cab;
		while (aux->next)
			aux = aux->next;
		aux->next = n;
	}
}

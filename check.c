/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 20:18:09 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/28 21:32:33 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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
			if (!ft_isdigit(argv[i][j]))
				return (1);
			j++;
		}
		i++;
	}
	if (i < 4 || i > 6)
		return (1);
	return (0);
}

void	ft_data(int argc, char **argv, t_data *ph)
{
	int aux;
	
	aux = ft_atoi(argv[1]);
	if (aux > 0)
		ph->num_philo = aux;
	aux = ft_atoi(argv[2]);
	if (aux > 0)
		ph->t_die = aux;
	aux = ft_atoi(argv[3]);
	if (aux > 0)
		ph->t_eat = aux;
	aux = ft_atoi(argv[4]);
	if (aux > 0)
		ph->t_sleep = aux;
	if (argc == 6)
	{
		aux = ft_atoi(argv[6]);
		if (aux > 0)
			ph->must_eat = aux;
	}
	ph->curl_node = 0;
}
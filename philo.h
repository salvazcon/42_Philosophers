/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:21:32 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/28 22:00:11 by saazcon-         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/ioctl.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <stddef.h>
# include <dirent.h>
# include <pthread.h> //libreria hilos

typedef struct s_philo
{
	//pthread_mutex_t fork;
	int				n_eated;
	int				name_ph;
	struct	s_philo *next;
}	t_philo;

typedef struct s_data
{
	int	num_philo;
	int	t_die;
	int	t_eat;
	int	t_sleep;
	int	must_eat;
	int curl_node;
	struct	s_philo *cab;
}	t_data;

int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		ft_check_args(char **argv);
void	*ft_calloc(size_t count, size_t size);
void	ft_create_list(t_data *ph, int id);
void	ft_data(int argc, char **argv, t_data *ph);
t_philo	*ft_create_node(t_philo *n, int id);

#endif

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:21:32 by saazcon-          #+#    #+#             */
/*   Updated: 2023/09/30 07:29:33 by saazcon-         ###   ########.fr       */
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
# include <sys/time.h> //libreria hora/ms
# include <pthread.h> //libreria hilos

typedef struct s_data
{
	int				num_philo;
	int				t_die;
	int				t_eat;
	int				t_sleep;
	int				must_eat;
}	t_data;

typedef struct s_philo
{
	//pthread_mutex_t fork;
	int					n_eated;
	int					name_ph;
	struct	s_data		data;
	struct	s_philo		*next;
}	t_philo;

int		ft_isdigit(int c);
int		ft_atoi(char *str);
int		ft_check_args(char **argv);
void	*ft_calloc(size_t count, size_t size);
t_data	ft_data(int argc, char **argv);
t_philo	*ft_lst(int argc, char **argv);
t_philo *ft_node(int argc, char **argv, int name);

#endif

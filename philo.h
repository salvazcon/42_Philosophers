/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: saazcon- <saazcon-@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:21:32 by saazcon-          #+#    #+#             */
/*   Updated: 2023/10/18 11:09:35 by saazcon-         ###   ########.fr       */
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
	pthread_mutex_t		mutex;
	int					num_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					must_eat;
	int					stuffed;
	unsigned long		time;
	bool				dead;
}	t_data;

typedef struct s_philo
{
	pthread_mutex_t		fork;
	unsigned long		t_life;
	int					n_eated;
	int					name_ph;
	struct s_data		*data;
	struct s_philo		*next;
}	t_philo;

unsigned long	ft_time(void);
int				ft_isdigit(int c);
int				ft_atoi(char *str);
int				ft_strlen(const char *s);
int				ft_check_args(int argc, char **argv);
void			ft_stuffed(t_philo	*ph);
void			*ft_dead_philo(void	*arg);
void			ft_free_round_list(t_philo	*ph);
void			*ft_calloc(size_t count, size_t size);
void			ft_usleep(unsigned long time);
void			ft_print(t_philo	*ph, unsigned long time, char *msg);
t_data			ft_data(int argc, char **argv);
t_philo			*ft_lst(t_data	*dt);
t_philo			*ft_node(t_data	*dt, int name);
#endif

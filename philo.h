/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 13:21:32 by saazcon-          #+#    #+#             */
/*   Updated: 2023/11/03 17:21:19 by marvin           ###   ########.fr       */
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
# include <signal.h>
# include <errno.h>
# include <string.h>
# include <stdbool.h>
# include <stddef.h>
# include <dirent.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_data
{
	pthread_mutex_t		mutex_print;
	pthread_mutex_t		mutex_stuff;
	pthread_mutex_t		mutex_erase;
	pthread_mutex_t		mutex_dead;
	pthread_mutex_t		mutex_end;
	int					num_philo;
	int					t_die;
	int					t_eat;
	int					t_sleep;
	int					must_eat;
	int					stuffed;
	unsigned long		time;
	bool				erase;
	bool				dead;
	bool				end;
	bool				error;
}	t_data;

typedef struct s_philo
{
	pthread_mutex_t		mutex_life;
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
int				ft_is_dead(t_philo *ph);
int				ft_strlen(const char *s);
int				ft_check_args(int argc, char **argv);
void			ft_life(t_philo *ph);
void			ft_kill(t_philo	*ph);
void			ft_dead_philo(t_philo *ph);
void			ft_destroy_mutex(t_philo *ph);
void			ft_free_round_list(t_philo *ph);
void			ft_stuffed(t_philo *ph, int n_philo);
void			*ft_calloc(size_t count, size_t size);
void			ft_usleep(t_philo *ph, unsigned long time);
void			ft_print(t_philo *ph, unsigned long time, char *msg);
t_data			ft_data(int argc, char **argv);
t_philo			*ft_lst(t_data *dt);
t_philo			*ft_node(t_data *dt, int name);
#endif

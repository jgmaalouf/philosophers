/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 16:00:53 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/29 17:05:53 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/time.h>
# include <pthread.h>

typedef struct s_philo t_philo;

typedef struct s_data
{
	long				count_of_philo;
	long				amount_to_eat;
	long				time_to_die;
	long				time_to_eat;
	long				time_to_sleep;
	long				start_of_dining;
	bool				death_of_philo;
	pthread_t			grim_reaper;
	pthread_mutex_t		death_mutex;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		start_mutex;
	t_philo				*philos;
	pthread_mutex_t		*forks;
}				t_data;

typedef struct s_philo
{
	int				id;
	long			amount_to_eat;
	long			time_of_last_meal;
	pthread_mutex_t	meal_check;
	pthread_t		philo;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_data			*data;
}					t_philo;
/************* utils.c *************/

long	current_time_in_ms(void);
void	logger(int philo_id, char *action, t_data *data);
int		print_error_msg(void);
bool	is_pos_num(char *str);
long	ft_philo_atoi(char *str);
void	cleanup(t_data *data);
int		ms_sleep(long time_in_ms);
bool	dead_philo(t_data *data);

/***********************************/

/*********** init_data.c ***********/

int		init_input(t_data *data, int argc, char **argv);
int		init_forks(t_data *data);

/***********************************/

/********* philosophize.c **********/

int		create_philos(t_data *data);
void	*day_in_life_of_philo(void *param);
void	begin_simulation(t_data *data);
int		join_philos(t_data *data);

/***********************************/

/*********** grim_reaper ***********/

int		create_grim_reaper(t_data *data);
void	*harvest_dead_soul(void *param);

/***********************************/

// TODO: FIX cleanup() FUNCTION !!!!!!!!!!
#endif

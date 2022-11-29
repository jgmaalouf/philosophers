/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:16:08 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/29 15:44:37 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Frees whatever needs freeing
*/
void	cleanup(t_data *data)
{
	int	i;

	if (data->philos != NULL)
		free(data->philos);
	if (data->forks != NULL)
	{
		i = 0;
		while (i < data->count_of_philo)
		{
			if (pthread_mutex_destroy(&(data->forks[i++])) != 0)
				return ;
		}
		free(data->forks);
	}
	pthread_mutex_destroy(&(data->print_mutex));
	pthread_mutex_destroy(&(data->start_mutex));
}

/*
	Gives a more precise sleep function by utilizing usleep()
	but sleeping in milliseconds instead.
*/
int	ms_sleep(long time_in_ms)
{
	struct timeval	t0;
	long			elapsed_time;
	long			start_time;

	gettimeofday(&t0, NULL);
	start_time = ((t0.tv_sec * 1000) + (t0.tv_usec / 1000));
	while (1)
	{
		elapsed_time = current_time_in_ms() - start_time;
		if (elapsed_time >= time_in_ms)
			return (0);
		usleep(100);
	}
}

/*
	Returns the current time in ms.
	Returns -1 if error.
*/
long	current_time_in_ms(void)
{
	struct timeval	t0;

	gettimeofday(&t0, NULL);
	return ((t0.tv_sec * 1000) + (t0.tv_usec / 1000));
}

bool	dead_philo(t_data *data)
{
	bool	death;

	pthread_mutex_lock(&(data->death_mutex));
	death = data->death_of_philo;
	pthread_mutex_unlock(&(data->death_mutex));
	return (death);
}

/*
	Prints out the elapsed time, and which philo doing what action.
	In the form of: (time) (philo_id) (action).
	If elapsed time == -1, there is an error.
*/
void	logger(int philo_id, char *action, t_data *data)
{
	long			elapsed_time;

	pthread_mutex_lock(&(data->print_mutex));
	if (!dead_philo(data))
	{
		elapsed_time = current_time_in_ms() - data->start_of_dining;
		printf("%ld\t%d %s\n", elapsed_time, philo_id, action);
	}
	pthread_mutex_unlock(&(data->print_mutex));
}

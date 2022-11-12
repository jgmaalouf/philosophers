/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 16:16:08 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/09 19:03:33 by jmaalouf         ###   ########.fr       */
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
		while (pthread_mutex_destroy(&(data->forks[i++])) == 0)
		;
		// free(data->forks);
	}
}

/*
	Gives a more precise sleep function by utilizing usleep()
	but sleeping in milliseconds instead.
*/
int	ms_sleep(long time_in_ms)
{
	long			elapsed_time;
	struct timeval	t0;

	gettimeofday(&t0, NULL);
	while (1)
	{
		elapsed_time = current_time_in_ms()
			- ((t0.tv_sec * 1000) + (t0.tv_usec / 1000));
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

/*
	Prints out the elapsed time, and which philo doing what action.
	In the form of: (time) (philo_id) (action).
	If elapsed time == -1, there is an error.
	
	TODO: Figure out if you need to have a mutex.
*/
void	logger(int philo_id, char *action, t_data *data)
{
	long			elapsed_time;
	struct timeval	tn;
	

	pthread_mutex_lock(&(data->print_mutex));
	gettimeofday(&tn, NULL);
	elapsed_time = ((tn.tv_sec * 1000) + (tn.tv_usec / 1000))
		- data->start_of_dining;
	printf("%ld\t%d %s\n", elapsed_time, philo_id, action);
	pthread_mutex_unlock(&(data->print_mutex));
}

/*
	Prints error message.
	@return 0
*/
int	print_error_msg()
{
	printf("Wrong input!\n");
	return (0);
}
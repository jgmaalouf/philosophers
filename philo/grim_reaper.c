/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:48:57 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/29 19:26:00 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Checks for the death of a philo by comparing the time since he last
	ate with the time_to_die given.
	@return 1 if philo died
*/
static bool	philo_died(t_philo *philo)
{
	long	current_time;

	current_time = current_time_in_ms();
	pthread_mutex_lock(&(philo->meal_check));
	if ((current_time - philo->time_of_last_meal) > philo->data->time_to_die)
	{
		pthread_mutex_unlock(&(philo->meal_check));
		return (true);
	}
	pthread_mutex_unlock(&(philo->meal_check));
	return (false);
}

static void	*announce_dead_philo(t_philo *philo)
{
	long	elapsed_time;

	pthread_mutex_lock(&(philo->data->death_mutex));
	philo->data->death_of_philo = true;
	pthread_mutex_unlock(&(philo->data->death_mutex));
	pthread_mutex_lock(&(philo->data->print_mutex));
	elapsed_time = current_time_in_ms() - philo->data->start_of_dining;
	printf("%ld\t%d died\n", elapsed_time, philo->id);
	pthread_mutex_unlock(&(philo->data->print_mutex));
	return (NULL);
}

void	*harvest_dead_soul(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *) param;
	pthread_mutex_lock(&(data->start_mutex));
	pthread_mutex_unlock(&(data->start_mutex));
	usleep(700);
	while (true)
	{
		i = -1;
		while (++i < data->count_of_philo)
			if (philo_died(&(data->philos[i])))
				return (announce_dead_philo(&(data->philos[i])));
	}
	return (NULL);
}
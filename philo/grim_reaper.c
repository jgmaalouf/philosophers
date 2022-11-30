/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   grim_reaper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:48:57 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/30 16:20:57 by jmaalouf         ###   ########.fr       */
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

	pthread_mutex_lock(&(philo->meal_lock));
	current_time = current_time_in_ms();
	if ((current_time - philo->time_of_last_meal) > philo->time_to_die)
	{
		pthread_mutex_unlock(&(philo->meal_lock));
		return (true);
	}
	pthread_mutex_unlock(&(philo->meal_lock));
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

static bool philo_full(t_philo *philo)
{
	pthread_mutex_lock(&(philo->meal_lock));
	if (philo->amount_to_eat != 0)
	{
		pthread_mutex_unlock(&(philo->meal_lock));
		return (false);
	}
	pthread_mutex_unlock(&(philo->meal_lock));
	return (true);
}

static bool	philos_full(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->count_of_philo)
		if (philo_full(&(data->philos[i])))
			return (true);
	return (false);
}

void	*harvest_dead_soul(void *param)
{
	t_data	*data;
	int		i;

	data = (t_data *) param;
	pthread_mutex_lock(&(data->start_mutex));
	pthread_mutex_unlock(&(data->start_mutex));
	while (!philos_full(data))
	{
		ms_sleep(3);
		i = -1;
		while (++i < data->count_of_philo)
			if (!philo_full(&(data->philos[i])))
				if (philo_died(&(data->philos[i])))
					return (announce_dead_philo(&(data->philos[i])));
	}
	return (NULL);
}

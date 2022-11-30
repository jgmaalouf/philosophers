/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 13:48:57 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/30 15:56:14 by jmaalouf         ###   ########.fr       */
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
	if ((current_time - philo->time_of_last_meal) > philo->time_to_die)
	{
		return (true);
	}
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

bool philo_full(t_philo *philo)
{
	if (philo->amount_to_eat != 0)
		return (false);
	return (true);
}

void	check_death(t_philo *philo)
{
	if (!dead_philo(philo->data))
		if (philo_died(philo))
			announce_dead_philo(philo);
}

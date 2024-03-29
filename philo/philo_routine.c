/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:44:59 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/30 17:03:37 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	eat(t_philo *philo)
{
	pthread_mutex_lock(&(philo->meal_lock));
	philo->amount_to_eat--;
	philo->time_of_last_meal = current_time_in_ms();
	pthread_mutex_unlock(&(philo->meal_lock));
	logger(philo->id, "is eating", philo->data);
	ms_sleep(philo->data->time_to_eat);
}

void	philo_sleep(t_philo *philo)
{
	logger(philo->id, "is sleeping", philo->data);
	ms_sleep(philo->data->time_to_sleep);
	logger(philo->id, "is thinking", philo->data);
}

void	pickup_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pickup_fork(philo->id, philo->left_fork, philo->data);
		pickup_fork(philo->id, philo->right_fork, philo->data);
	}
	else
	{
		pickup_fork(philo->id, philo->right_fork, philo->data);
		pickup_fork(philo->id, philo->left_fork, philo->data);
	}
}

void	putdown_forks(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		putdown_fork(philo->left_fork);
		putdown_fork(philo->right_fork);
	}
	else
	{
		putdown_fork(philo->right_fork);
		putdown_fork(philo->left_fork);
	}
}

void	*day_in_life_of_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	pthread_mutex_lock(&(philo->data->start_mutex));
	pthread_mutex_unlock(&(philo->data->start_mutex));
	while (philo->amount_to_eat != 0 && !dead_philo(philo->data))
	{
		pickup_forks(philo);
		eat(philo);
		putdown_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

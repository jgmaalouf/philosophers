/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:44:59 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/28 16:14:25 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	pickup_fork(int id, pthread_mutex_t *fork, t_data *data)
{
	pthread_mutex_lock(fork);
	logger(id, "has taken a fork", data);
}

void	eat(t_philo *philo)
{
	logger(philo->id, "is eating", philo->data);
	ms_sleep(philo->data->time_to_eat);
	philo->amount_to_eat--;
}

void	putdown_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
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
	while (philo->amount_to_eat != 0)
	{
		pickup_forks(philo);
		eat(philo);
		putdown_forks(philo);
		philo_sleep(philo);
	}
	return (NULL);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/26 11:44:59 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/09 18:02:42 by jmaalouf         ###   ########.fr       */
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
}

void	putdown_fork(pthread_mutex_t *fork)
{
	pthread_mutex_unlock(fork);
}

void	schlafen(t_philo *philo)
{
	logger(philo->id, "is sleeping", philo->data);
	ms_sleep(philo->data->time_to_sleep);
}

void	*day_in_life_of_philo(void *param)
{
	t_philo	*philo;

	philo = (t_philo *) param;
	while (philo->data->start_of_dining == -1)
		;
	while(philo->data->death_of_philo == false)
	{
		pickup_fork(philo->id, philo->left_fork, philo->data);
		// pickup_fork(philo->id, philo->right_fork, philo->data);
		eat(philo);
		// putdown_fork(philo->right_fork);
		putdown_fork(philo->left_fork);
		schlafen(philo);
		
	}
	return (NULL);
}

// pthread_mutex_t	print_lock;
// void	*day_in_life_of_philo(void *param)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *) param;
// 	while (philo->data->start_of_dining == -1)
// 		;
// 	pthread_mutex_init(&print_lock, NULL);
// 	pthread_mutex_lock(&print_lock);
// 	while(philo->data->death_of_philo == false)
// 	{
// 		logger(philo->id, "says hello", philo->data);
// 		ms_sleep(200);
// 		pthread_mutex_unlock(&print_lock);
// 	}
// 	return (NULL);
// }

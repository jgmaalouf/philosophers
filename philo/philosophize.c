/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:49:10 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/30 19:19:53 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Assigns the necessary info in struct s_philo for one philo at a time.
	We assume that the philosophers are sitting at a round table
	and their ID value is increasing in a counter clockwise manner around
	the table.
	@return 0 in case of an error.
*/
int	create_one_philo(t_data *data, int i)
{
	data->philos[i].id = i + 1;
	data->philos[i].amount_to_eat = data->amount_to_eat;
	data->philos[i].time_to_die = data->time_to_die;
	data->philos[i].left_fork = &(data->forks[i]);
	data->philos[i].right_fork = &(data->forks[(i + 1) % data->count_of_philo]);
	data->philos[i].data = data;
	pthread_mutex_init(&(data->philos[i].meal_lock), NULL);
	if (pthread_create(&(data->philos[i].philo), NULL,
			&day_in_life_of_philo, (void*) &(data->philos[i])) != 0)
		return (0);
	if (data->count_of_philo == 1)
		pthread_detach(data->philos[i].philo);
	return (1);
}

/*
	Creates count_of_philo s_philo structs and puts them in an allocated array.
	@return 0 in case of an error.
*/
int	create_philos(t_data *data)
{
	int	i;

	pthread_mutex_lock(&(data->start_mutex));
	data->philos = malloc(sizeof(t_philo) * (data->count_of_philo));
	if (data->philos != NULL)
	{
		i = -1;
		while (++i < data->count_of_philo)
			if (!create_one_philo(data, i))
				return (0);
		return (1);
	}
	return (0);
}

/*
	Creates thread that checks death of a philo and detaches it.
	@return 0 in case of error.
*/
int	create_grim_reaper(t_data *data)
{
	if (pthread_create(&(data->grim_reaper), NULL,
			&harvest_dead_soul, (void *)(data)) != 0)
		return (0);
	if (pthread_detach(data->grim_reaper) != 0)
		return (0);
	return (1);
}

void	begin_simulation(t_data *data)
{
	int	i;

	data->start_of_dining = current_time_in_ms();
	i = -1;
	while (++i < data->count_of_philo)
		data->philos[i].time_of_last_meal = data->start_of_dining;
	pthread_mutex_unlock(&(data->start_mutex));
	while (!dead_philo(data) && !philos_full(data))
		ms_sleep(1);
}

/*
	Uses pthread_join to join all philos created
	@return 0 in case of error
*/
int	join_philos(t_data *data)
{
	int	i;

	i = -1;
	if (data->count_of_philo == 1)
		i++;
	while (++i < data->count_of_philo)
		if (pthread_join(data->philos[i].philo, NULL) != 0)
			return (0);
	return (1);
}

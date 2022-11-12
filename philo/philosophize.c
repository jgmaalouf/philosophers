/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophize.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 10:49:10 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/10/31 12:17:47 by jmaalouf         ###   ########.fr       */
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
	data->philos[i].state = waiting_launch;
	data->philos[i].left_fork = &(data->forks[i]);
	data->philos[i].right_fork = &(data->forks[(i + 1) % data->count_of_philo]);
	data->philos[i].data = data;
	if (pthread_create(&(data->philos[i].philo), NULL,
			&day_in_life_of_philo, (void*) &(data->philos[i])) != 0)
		return (0);
	return (1);
}

/*
	Creates amount_of_philo s_philo structs and puts them in an allocated array.
	@return 0 in case of an error.
*/
int	create_philos(t_data *data)
{
	int	i;

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

void	begin_simulation(t_data *data)
{
	data->start_of_dining = current_time_in_ms();
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 16:56:10 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/28 10:45:15 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Initializes the amount_to_eat, time_to_*, and amount_to_eat
	variables in struct s_data and checks for correct input.
	@return 0 in case of an error.
*/
int	init_input(t_data *data, int argc, char **argv)
{
	if (argc < 5 || argc > 6)
		return (0);
	data->count_of_philo = ft_philo_atoi(argv[1]);
	data->amount_to_eat = -1;
	data->time_to_die = ft_philo_atoi(argv[2]);
	data->time_to_eat = ft_philo_atoi(argv[3]);
	data->time_to_sleep = ft_philo_atoi(argv[4]);
	if (data->count_of_philo == -1 || data->time_to_die == -1
		|| data->time_to_eat == -1 || data->time_to_sleep == -1)
		return (0);
	if (argc == 6)
	{
		data->amount_to_eat = ft_philo_atoi(argv[5]);
		if (data->amount_to_eat == -1)
			return (0);
	}
	return (1);
}

/*
	Allocates an array of pthread_mutex_t and initializes the mutexes.
	@return 0 in case of error.
*/
int	init_forks(t_data *data)
{
	int	i;

	data->forks = malloc(sizeof(pthread_mutex_t) * data->count_of_philo);
	if (data->forks != NULL)
	{
		i = -1;
		while (++i < data->count_of_philo)
			if (pthread_mutex_init(&(data->forks[i]), NULL) != 0)
				return (0);
		return (1);
	}
	return (0);
}

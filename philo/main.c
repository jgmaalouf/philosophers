/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:31:49 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/09 18:36:36 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Initializes all the data in struct
	s_data, and does necessary parsing.
	@return 0 in case of an error.
*/
int	init_data(t_data *data, int argc, char **argv)
{
	if (!init_timings(data, argc, argv))
		return (print_error_msg());
	data->start_of_dining = -1;
	data->death_of_philo = false;
	data->philos = NULL;
	data->forks = NULL;
	pthread_mutex_init(&(data->print_mutex), NULL);
	return (1);
}

/*
	Initializes any mutexes needed.
*/
int	init_locks(t_data *data)
{
	if (!init_forks(data))
	{
		cleanup(data);
		return (0);
	}
	return (1);
}

int	philosophize(t_data *data)
{
	if (!create_philos(data))
		return (0);
	begin_simulation(data);
	while (1)
		;
	// check_death(data);
	// if (!join_philos(data))
	// 	return (0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!init_data(&data, argc, argv))
		return (EXIT_FAILURE);
	if (!init_locks(&data))
		return (EXIT_FAILURE);
	if (!philosophize(&data))
		return (EXIT_FAILURE);
	cleanup(&data);
	return (EXIT_SUCCESS);
}

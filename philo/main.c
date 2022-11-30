/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/24 15:31:49 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/30 16:58:17 by jmaalouf         ###   ########.fr       */
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
	if (!init_input(data, argc, argv))
		return (print_error_msg());
	data->death_of_philo = false;
	data->philos = NULL;
	data->forks = NULL;
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
	if (pthread_mutex_init(&(data->death_mutex), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->print_mutex), NULL) != 0)
		return (0);
	if (pthread_mutex_init(&(data->start_mutex), NULL) != 0)
		return (0);
	return (1);
}

int	philosophize(t_data *data)
{
	if (!create_philos(data))
		return (0);
	if (!create_grim_reaper(data))
		return (0);
	begin_simulation(data);
	if (!join_philos(data))
		return (0);
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

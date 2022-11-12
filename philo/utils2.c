/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaalouf <jmaalouf@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/29 18:08:34 by jmaalouf          #+#    #+#             */
/*   Updated: 2022/11/09 18:49:20 by jmaalouf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

/*
	Checks if str provided represents a positive number.
	@return false if str is anything else.
*/
bool	is_pos_num(char *str)
{
	int	i;

	i = 0;
	while (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		if (str[i] < '0' || str[i] > '9')
			return (false);
		i++;
	}
	return (true);
}

/*
	Takes in a str representing a positive int.
	@return int representation of str.
	-1 in case of an error.
*/
long	ft_philo_atoi(char *str)
{
	int		i;
	long	ret;

	ret = 0;
	if (!is_pos_num(str))
		return (-1);
	i = 0;
	while (str[i] == '+')
		i++;
	while (str[i] != '\0')
	{
		ret = ret * 10 + (long)(str[i] - '0');
		if (ret > INT_MAX)
			return (-1);
		i++;
	}
	return (ret);
}
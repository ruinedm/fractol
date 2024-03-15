/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conversion_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 19:45:43 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/15 21:14:53 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

// 0.000000

static int is_valid(char *str)
{
	int p_count;
	int i;

	i = 0;
	p_count = 0;
	if(!ft_strlen(str))
		return (0);
	if(str[i] == '-' || str[i] == '+')
		i++;
	while(str[i])
	{
		if(str[i] == '.')
		{
			if(!p_count)
				p_count++;
			else
				return (0);
		}
		else if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}

static int is_zero(char *str)
{
	int count;
	int i;

	i = 0;
	while (str[i] && str[i] == '0')
		i++;
	if (str[i] == '.')
	{
		i++;
		count = 0;
		while (str[i] && str[i] == '0')
		{
			count++;
			i++;
			if (count == 6)
				return (1);
		}
	}
	return (0);
}

double str_to_double(char *str, int i, double sign)
{
	long double check;
	long double divider;

	check = 0.0;
	divider = 0.1;
	while (str[i] >= '0' && str[i] <= '9')
	{
		check = check * 10 + (str[i] - '0');
		i++;
	}
	i++;
	while(str[i] >= '0' && str[i] <= '9')
	{
		check = check + (str[i] - '0') * divider;
		divider /= 10;
		i++;
	}
	return ((double)check * sign);
}

double	ft_atof(char *str)
{
	size_t	i;
	double sign;
	double	result;

	result = 0.00000;
	i = 0;
	sign = 1.0;
	if(!is_valid(str))
	{
		printf("Not valid\n"); 
		exit(EXIT_FAILURE);
	}
	if(is_zero(str))
		return (result);
	while (str[i] && (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13)))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1.0;
		i++;
	}
	while (str[i] == '0')
		i++;
	return (str_to_double(str, i, sign));
}

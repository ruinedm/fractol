/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 19:48:45 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/20 01:27:08 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static void	print_error(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		write(2, &str[i], 1);
		i++;
	}
}

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	reset_struct(t_fractal *fractal)
{
	fractal->zoom_factor = 1.0;
	fractal->random_flag = 0;
	fractal->random_color = 1.0;
	fractal->start.real = -2;
	fractal->end.real = 2;
	fractal->start.imaginary = 2;
	fractal->end.imaginary = -2;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
}

void	error_handler(int flag)
{
	if (flag == MLX_ERROR)
		print_error("MiniLibX Error, please try again\n");
	else if (flag == INPUT_ERROR)
	{
		print_error("Incorrect input!\n");
		print_error("Please use one of the following options:\n");
		print_error("./fractol mandelbrot\n");
		print_error("./fractol julia (2 numerical options)\n");
		print_error("./fractol tricorn\n");
	}
	exit(EXIT_FAILURE);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] || s2[i]))
	{
		if (s1[i] != s2[i])
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		i++;
	}
	return (0);
}

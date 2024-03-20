/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   study_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:17:05 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/20 01:38:37 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol_bonus.h"

void	convert_to_complex(int x, int y, t_complex *c, t_fractal *fractal)
{
	t_complex	scale;

	scale.real = (fractal->end.real - fractal->start.real) / 800.0;
	scale.imaginary = (fractal->end.imaginary - fractal->start.imaginary)
		/ 800.0;
	c->real = fractal->start.real + scale.real * x;
	c->imaginary = fractal->start.imaginary + scale.imaginary * y;
}

static int	iterate_and_calculate(t_complex z, t_complex c, t_fractal *fractal)
{
	int		count;
	double	hold;

	count = 0;
	while (count < MAX_ITERATIONS)
	{
		hold = z.real;
		z.real = z.real * z.real - z.imaginary * z.imaginary + c.real;
		z.imaginary = 2 * hold * z.imaginary + c.imaginary;
		if (fractal->fractal_type == TRICORN)
			z.imaginary *= -1;
		if (isinf(z.real) || isinf(z.imaginary))
			return (count);
		count++;
	}
	return (CONVERGE);
}

int	analyze_z(int x, int y, t_fractal *fractal)
{
	t_complex	c;
	t_complex	z;
	int			count;

	count = 0;
	if (fractal->fractal_type == MANDELBROT || fractal->fractal_type == TRICORN)
	{
		z.real = 0.0;
		z.imaginary = 0.0;
		convert_to_complex(x, y, &c, fractal);
		c.real += fractal->shift_x;
		c.imaginary += fractal->shift_y;
	}
	else if (fractal->fractal_type == JULIA)
	{
		c.real = fractal->julia_real;
		c.imaginary = fractal->julia_imaginary;
		convert_to_complex(x, y, &z, fractal);
		z.real += fractal->shift_x;
		z.imaginary += fractal->shift_y;
	}
	else
		return (-11);
	return (iterate_and_calculate(z, c, fractal));
}

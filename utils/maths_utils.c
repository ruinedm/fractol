/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:17:05 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/14 21:11:37 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"


static void convert_to_complex(int x, int y, t_complex *c, t_fractal *fractal)
{
    c->real = (float)x / (200.0 * fractal->zoom_factor) - 2.0 + fractal->shift_x; // + left // - right
    c->imaginary = (float)y / (200.0 * fractal->zoom_factor) - 2.0 + fractal->shift_y; // + up // - down
}


int analyze_z(int x, int y, t_fractal *fractal)
{
    t_complex c;
    t_complex z;
    int count;
    double hold;

    count = 0;
    if (fractal->fractal_type == MANDELBROT)
    {
        z.real = 0.0;
        z.imaginary = 0.0;
        convert_to_complex(x, y ,&c, fractal);
    }
    else if (fractal->fractal_type == JULIA)
    {
        c.real = fractal->julia_real;
        c.imaginary = fractal->julia_immaginary;
        convert_to_complex(x, y ,&z, fractal);
    }
    while(count < MAX_ITERATIONS)
    { 
        hold = z.real;
        z.real = z.real * z.real - z.imaginary * z.imaginary + c.real;
        z.imaginary = 2 * hold * z.imaginary + c.imaginary;
        if (isinf(z.real) || isinf(z.imaginary))
            return (count);
        count++;
    }
    return (CONVERGE);
}

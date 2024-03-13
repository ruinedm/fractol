/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:17:05 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/13 22:29:10 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"


static void convert_to_complex(int x, int y, t_complex *c, int zoom_factor)
{
    c->real = (float)x / (200.0 * zoom_factor) - 2.0;
    c->imaginary = (float)y / (200.0 * zoom_factor) - 2.0;
}

int analyze_z(int x, int y, int fractal_type, int zoom_factor)
{
    t_complex c;
    t_complex z;
    int count;
    double hold;

    count = 0;
    if (fractal_type == MANDELBROT)
    {  
        z.real = 0.0;
        z.imaginary = 0.0;
        convert_to_complex(x, y ,&c, zoom_factor);
    }
    else if (fractal_type == JULIA)
    {
        c.real = -0.745429;
        c.imaginary = 0.05;
        convert_to_complex(x, y ,&z, zoom_factor);
    }
    while(count < MAX_ITERATIONS)
    { 
        hold = z.real;
        z.real = (z.real) * (z.real) - (z.imaginary) * (z.imaginary) + c.real;
        z.imaginary = 2 * hold * z.imaginary + c.imaginary;
        if (isinf(z.real) || isinf(z.imaginary))
            return (count);
        count++;
    }
    return (CONVERGE);
}

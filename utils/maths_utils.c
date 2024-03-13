/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:17:05 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/13 03:09:54 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"


static void convert_to_complex(int x, int y, t_complex *c)
{
    c->real = (float)x / 200.0 - 2.0;
    c->imaginary = (float)y / 200.0 - 2.0;                                               
}

int analyze_z(int x, int y, int fractal_type)
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
        convert_to_complex(x, y ,&c);
    }
    else if (fractal_type == JULIA)
    {
        c.real = 0.36;
        c.imaginary = 0.1;
        convert_to_complex(x, y ,&z);
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

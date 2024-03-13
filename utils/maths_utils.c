/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   maths_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/10 21:17:05 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/13 00:38:49 by mboukour         ###   ########.fr       */
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

    convert_to_complex(x, y ,&c);
    count = 0;
    if(fractal_type == MANDELBROT)
    {        
        z.real = 0.0;
        z.imaginary = 0.0;
    }
    else
    {
        z.real = -0.745429;
        z.imaginary = 0.05;
    }
    while(count < MAX_ITERATIONS)
    {
        hold = z.real;
        z.real = (z.real) * (z.real) - (z.imaginary) * (z.imaginary) + c.real;
        z.imaginary = 2 * hold * z.imaginary + c.imaginary;
        if (isnan(z.real) || isnan(z.imaginary) || isinf(z.real) || isinf(z.imaginary)) 
            return (DIVERGE);
        count++;
    }
    return (CONVERGE);
}

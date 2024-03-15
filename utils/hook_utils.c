/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 05:37:26 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/15 05:54:47 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"


int button_close(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->win);
	exit(EXIT_SUCCESS);
	return (0);
}


int	key_hook(int keycode, t_fractal *fractal)
{
	if(keycode == ESC)
		button_close(fractal);
	else if(keycode == ENTER)
	{
		fractal->zoom_factor = 1.0;
		fractal->shift_margin = 0.5;
		fractal->shift_x = 0.0;
		fractal->shift_y = 0.0;
	}
	else if(keycode == UP)
		fractal->shift_y -= fractal->shift_margin;
	else if(keycode == DOWN)
		fractal->shift_y += fractal->shift_margin;
	else if(keycode == RIGHT)
		fractal->shift_x += fractal->shift_margin;
	else if(keycode == LEFT)
		fractal->shift_x -= fractal->shift_margin;
	else
		return (1);
	render_fractal(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}

int mouse_hook(int mousecode, int x, int y, t_fractal *fractal)
{
	double old_shift_margin;

	old_shift_margin = fractal->shift_margin;
    if (mousecode == ZOOM_IN)
    {
        fractal->zoom_factor *= 1.1;
        fractal->shift_margin /= 1.1;
    }
    else if (mousecode == ZOOM_OUT)
    {
        fractal->zoom_factor /= 1.1;
        fractal->shift_margin *= 1.1;
    }
    else
        return (x * y);
    fractal->shift_x -= fractal->shift_margin - old_shift_margin;
    fractal->shift_y -= fractal->shift_margin - old_shift_margin;
    render_fractal(fractal);
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    return (0);
}

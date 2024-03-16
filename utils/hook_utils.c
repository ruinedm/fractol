/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 05:37:26 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/16 01:57:24 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int button_close(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->win);
	exit(EXIT_SUCCESS);
	return (0);
}

void	reset_struct(t_fractal *fractal)
{
		fractal->zoom_factor = 1.0;
		fractal->shift_margin = 0.5;
		fractal->shift_x = 0.0;
		fractal->shift_y = 0.0;
		fractal->random_flag = 0;
		fractal->random_color = 1.0;
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if(keycode == ESC)
		button_close(fractal);
	else if(keycode == SPACE)
	{
		fractal->random_color += 10;
		fractal->random_flag = 1;
	}
	else if(keycode == ENTER)
		reset_struct(fractal);
	else if(keycode == UP)
		fractal->shift_y -= 1.1 / fractal->zoom_factor;
	else if(keycode == DOWN)
		fractal->shift_y += 1.1 / fractal->zoom_factor;
	else if(keycode == RIGHT)
		fractal->shift_x += 1.1 / fractal->zoom_factor;
	else if(keycode == LEFT)
		fractal->shift_x -= 1.1 / fractal->zoom_factor;
	else
		return (1);
	render_fractal(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}

int mouse_hook(int mousecode, int x, int y, t_fractal *fractal)
{
    if (mousecode == ZOOM_IN)
        fractal->zoom_factor *= 1.1;
    else if (mousecode == ZOOM_OUT)
        fractal->zoom_factor /= 1.1;
    else
        return (x * y);
    render_fractal(fractal);
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    return (0);
}

/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 05:37:26 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/20 01:27:43 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	button_close(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->win);
	exit(EXIT_SUCCESS);
	return (0);
}

static void	setup_shift(int keycode, t_fractal *fractal)
{
	t_complex	scale;

	scale.real = (fractal->end.real - fractal->start.real) / 800.0;
	scale.imaginary = (fractal->end.imaginary - fractal->start.imaginary)
		/ 800.0;
	if (keycode == UP)
		fractal->shift_y -= 20 * scale.imaginary * fractal->zoom_factor;
	else if (keycode == DOWN)
		fractal->shift_y += 20 * scale.imaginary * fractal->zoom_factor;
	else if (keycode == RIGHT)
		fractal->shift_x += 20 * scale.real * fractal->zoom_factor;
	else if (keycode == LEFT)
		fractal->shift_x -= 20 * scale.real * fractal->zoom_factor;
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == ESC)
		button_close(fractal);
	else if (keycode == SPACE)
	{
		fractal->random_color += 10;
		fractal->random_flag = 1;
	}
	else if (keycode == ENTER)
		reset_struct(fractal);
	else if (keycode == UP || keycode == DOWN || keycode == RIGHT
		|| keycode == LEFT)
		setup_shift(keycode, fractal);
	else
		return (1);
	render_fractal(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}

int	mouse_hook(int mousecode, int x, int y, t_fractal *fractal)
{
	t_complex	z_mouse;

	if (mousecode == ZOOM_IN)
		fractal->zoom_factor = 1.1;
	else if (mousecode == ZOOM_OUT)
		fractal->zoom_factor = 0.9;
	else
		return (x * y);
	convert_to_complex(x, y, &z_mouse, fractal);
	fractal->start.real = (fractal->start.real - z_mouse.real)
		* fractal->zoom_factor + z_mouse.real;
	fractal->start.imaginary = (fractal->start.imaginary - z_mouse.imaginary)
		* fractal->zoom_factor + z_mouse.imaginary;
	fractal->end.real = (fractal->end.real - z_mouse.real)
		* fractal->zoom_factor + z_mouse.real;
	fractal->end.imaginary = (fractal->end.imaginary - z_mouse.imaginary)
		* fractal->zoom_factor + z_mouse.imaginary;
	render_fractal(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}

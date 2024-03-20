/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 05:37:26 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/20 01:49:59 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

int	button_close(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx, fractal->win);
	exit(EXIT_SUCCESS);
	return (0);
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if (keycode == ESC)
		button_close(fractal);
	else if (keycode == ENTER)
		reset_struct(fractal);
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
		fractal->zoom_factor *= 1.1;
	else
		fractal->zoom_factor *= 0.9;
	convert_to_complex(x, y, &z_mouse, fractal);
	render_fractal(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}

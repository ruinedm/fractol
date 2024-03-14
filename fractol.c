/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:52:59 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/14 21:09:26 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fractol.h"


void better_mlx_pixel_put(t_fractal *data, int x, int y, unsigned int color)
{
	int offset;
	char *to_color;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	to_color = data->addr + offset;
	*(unsigned int *)to_color = color;
}

static void color_divergence(t_fractal *fractal, int x, int y, int divergence)
{
    int base_color;
    int scaled_divergence;
	int new_color;
    t_trgb hold;

    base_color = create_trgb(0, 0, 255, 255);
	scaled_divergence = (divergence * 255) / MAX_ITERATIONS;
    hold.red = (get_r(base_color) * scaled_divergence) / 255;
    hold.green = (get_g(base_color) * scaled_divergence) / 255;
   	hold.blue = (get_b(base_color) * scaled_divergence) / 255;
    new_color = create_trgb(0, hold.red, hold.green, hold.blue);
    better_mlx_pixel_put(fractal, x, y, new_color);
}

static void render_fractal(t_fractal *fractal)
{
	int x;
	int y;
	int study_result;

	y = 0;
	while (y < 800)
	{
		x = 0;
		while (x < 800)
		{
			study_result = analyze_z(x, y, fractal);
			if(study_result != CONVERGE)
				color_divergence(fractal, x, y , study_result);
			else
				better_mlx_pixel_put(fractal, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

int	key_hook(int keycode, t_fractal *fractal)
{
	if(keycode == ESC)
		exit(EXIT_SUCCESS); // ADD CLEARING AND SHIT
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
        return (1);
    fractal->shift_x -= fractal->shift_margin - old_shift_margin;
    fractal->shift_y -= fractal->shift_margin - old_shift_margin;
    render_fractal(fractal);
    mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    return (0);
}

int	main(int ac, char **av)
{
	t_fractal fractal;

	if(ac < 2 || ac > 4)
		error_handler();
	fractal.shift_margin = 0.5;
	fractal.zoom_factor = 1.0;
	if(!ft_strcmp(av[1], "mandelbrot"))
		fractal.fractal_type = MANDELBROT;
	else if(!ft_strcmp(av[1], "julia"))
	{
		if(ac != 4)
			error_handler();
		fractal.fractal_type = JULIA;
	}
	else
		error_handler();
	fractal.shift_x = 0.0;
	fractal.shift_y = 0.0;
	fractal.mlx = mlx_init();
	if(!fractal.mlx)
		error_handler();
	fractal.win = mlx_new_window(fractal.mlx, 800, 800, "The void calls");
	fractal.img = mlx_new_image(fractal.mlx, 800, 800);
	fractal.addr = mlx_get_data_addr(fractal.img, &fractal.bits_per_pixel, &fractal.line_length, &fractal.endian);
	render_fractal(&fractal);
	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_key_hook(fractal.win, key_hook, &fractal);
	mlx_mouse_hook(fractal.win, mouse_hook, &fractal);
	mlx_loop(fractal.mlx);
}

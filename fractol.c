/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:52:59 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/13 22:46:28 by mboukour         ###   ########.fr       */
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

	printf("ZOOM FACTOR: %f\n", fractal->zoom_factor);
	y = 0;
	while (y < 800)
	{
		x = 0;
		while (x < 800)
		{
			study_result = analyze_z(x, y, fractal->fractal_type, fractal->zoom_factor);
			if(study_result != CONVERGE)
				color_divergence(fractal, x, y , study_result);
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
		fractal->zoom_factor = 1.0;
	render_fractal(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
	return (0);
}

int mouse_hook(int mousecode, int x, int y, t_fractal *fractal)
{
    if (mousecode == ZOOM_IN)
		fractal->zoom_factor = fractal->zoom_factor * 1.2;
	else if (mousecode == ZOOM_OUT)
		fractal->zoom_factor = fractal->zoom_factor / 1.2;
	if (fractal->zoom_factor < 1.0)
		fractal->zoom_factor = 1.0;
	render_fractal(fractal);
	mlx_put_image_to_window(fractal->mlx, fractal->win, fractal->img, 0, 0);
    return (0);
}



int	main(void)
{
	t_fractal img;

	img.zoom_factor = 1.0;
	img.fractal_type = JULIA;
	img.mlx = mlx_init();
	if(!img.mlx)
		return (0);
	img.win = mlx_new_window(img.mlx, 800, 800, "The void calls");
	img.img = mlx_new_image(img.mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	render_fractal(&img);
	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	mlx_key_hook(img.win, key_hook, &img);
	mlx_mouse_hook(img.win, mouse_hook, &img);
	mlx_loop(img.mlx);
}

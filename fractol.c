/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:52:59 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/13 00:35:27 by mboukour         ###   ########.fr       */
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

static void render_fractal(t_fractal *fractal, int fractal_type)
{
	int x;
	int y;

	y = 0;
	while (y < 800)
	{
		x = 0;
		while (x < 800)
		{
			if(analyze_z(x, y, fractal_type) == CONVERGE)
				better_mlx_pixel_put(fractal, x, y , 0xFFFFFF);
			x++;
		}
		y++;
	}
}


int	main(void)
{
	// atexit(f);
	void *mlx;
	void *window;
	t_fractal img;
	mlx = mlx_init();
	if(!mlx)
		return (0);
	window = mlx_new_window(mlx, 800, 800, "The void calls");
	img.img = mlx_new_image(mlx, 800, 800);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	render_fractal(&img, JULIA);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}

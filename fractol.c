/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:52:59 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/09 01:11:13 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "fractol.h"


void f()
{
	system("leaks fractol");
}


void better_mlx_pixel_put(t_data *data, int x, int y, unsigned int color)
{
	int offset;
	void *to_color;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	to_color = data->addr + offset;
	*(unsigned int *)to_color = color;
}

void draw_square(t_data *img)
{
	int ref = 50;
	int len = ref + 40;
	int x = ref;
	int y = ref;

	while (y < len)
	{
		while (x < len * 2)
		{
			better_mlx_pixel_put(img, x, y , 0x00FF0000);
			x++;
		}
		x = ref;
		y++;
	}
}


int	main(void)
{
	// atexit(f);
	void *mlx;
	void *window;
	t_data img;
	mlx = mlx_init();
	if(!mlx)
		return (0);
	window = mlx_new_window(mlx, 1920, 1080, "The void calls");
	img.img = mlx_new_image(mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	draw_square(&img);
	mlx_put_image_to_window(mlx, window, img.img, 0, 0);
	mlx_loop(mlx);
}

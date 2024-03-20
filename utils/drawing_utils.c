/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/15 05:39:03 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/20 01:26:10 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fractol.h"

static void	better_mlx_pixel_put(t_fractal *data, int x, int y,
		unsigned int color)
{
	int		offset;
	char	*to_color;

	offset = (y * data->line_length + x * (data->bits_per_pixel / 8));
	to_color = data->addr + offset;
	*(unsigned int *)to_color = color;
}

static void	color_divergence(t_fractal *fractal, int x, int y, int divergence)
{
	int		base_color;
	int		scaled_divergence;
	int		new_color;
	t_trgb	hold;

	base_color = create_trgb(0, 255, 255, 255);
	scaled_divergence = (divergence * 255) / MAX_ITERATIONS;
	hold.red = (get_r(base_color) * scaled_divergence * fractal->random_color)
		/ 255;
	hold.green = (get_g(base_color) * scaled_divergence * fractal->random_color)
		/ 255;
	hold.blue = (get_b(base_color) * scaled_divergence * fractal->random_color)
		/ 255;
	if (fractal->random_flag)
	{
		hold.red *= 3;
		hold.green *= 5;
		hold.blue *= 7;
	}
	new_color = create_trgb(0, hold.red, hold.green, hold.blue);
	better_mlx_pixel_put(fractal, x, y, new_color);
}

void	render_fractal(t_fractal *fractal)
{
	int	x;
	int	y;
	int	study_result;

	y = 0;
	while (y < 800)
	{
		x = 0;
		while (x < 800)
		{
			study_result = analyze_z(x, y, fractal);
			if (study_result != CONVERGE)
				color_divergence(fractal, x, y, study_result);
			else
				better_mlx_pixel_put(fractal, x, y, 0x000000);
			x++;
		}
		y++;
	}
}

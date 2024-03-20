/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:52:59 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/20 01:38:41 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol_bonus.h"

static void	setup_fractol_struct(int ac, char **av, t_fractal *fractal)
{
	if (ac < 2 || ac > 4 || ac == 3)
		error_handler(INPUT_ERROR);
	if (!ft_strcmp(av[1], "mandelbrot"))
		fractal->fractal_type = MANDELBROT;
	else if (!ft_strcmp(av[1], "julia"))
	{
		if (ac != 4)
			error_handler(INPUT_ERROR);
		fractal->fractal_type = JULIA;
		fractal->julia_real = ft_atof(av[2]);
		fractal->julia_imaginary = ft_atof(av[3]);
	}
	else if (!ft_strcmp(av[1], "tricorn"))
		fractal->fractal_type = TRICORN;
	else
		error_handler(INPUT_ERROR);
	reset_struct(fractal);
}

static void	init_mlx(t_fractal *fractal, char **av)
{
	fractal->mlx = mlx_init();
	if (!fractal->mlx)
		error_handler(MLX_ERROR);
	fractal->win = mlx_new_window(fractal->mlx, 800, 800, av[1]);
	if (!fractal->win)
		error_handler(MLX_ERROR);
	fractal->img = mlx_new_image(fractal->mlx, 800, 800);
	if (!fractal->img)
		error_handler(MLX_ERROR);
	fractal->addr = mlx_get_data_addr(fractal->img, &fractal->bits_per_pixel,
			&fractal->line_length, &fractal->endian);
	if (!fractal->addr)
	{
		mlx_destroy_image(fractal->mlx, fractal->win);
		error_handler(MLX_ERROR);
	}
}

int	main(int ac, char **av)
{
	t_fractal	fractal;

	setup_fractol_struct(ac, av, &fractal);
	init_mlx(&fractal, av);
	render_fractal(&fractal);
	mlx_put_image_to_window(fractal.mlx, fractal.win, fractal.img, 0, 0);
	mlx_hook(fractal.win, DESTROY_NOTIFY, 0, button_close, &fractal);
	mlx_key_hook(fractal.win, key_hook, &fractal);
	mlx_mouse_hook(fractal.win, mouse_hook, &fractal);
	mlx_loop(fractal.mlx);
	return (0);
}

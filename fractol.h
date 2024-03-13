/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mboukour <mboukour@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/03 16:53:05 by mboukour          #+#    #+#             */
/*   Updated: 2024/03/13 00:23:35 by mboukour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <mlx.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>


typedef struct s_complex
{
	double real;
	double imaginary;
} t_complex;

typedef struct	s_fractal
{
	t_complex z;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_fractal;

# define MAX_ITERATIONS 200

enum e_METHODS
{
	DIVERGE,
	CONVERGE
};

enum e_FRACTALS
{
	MANDELBROT,
	JULIA
};

int analyze_z(int x, int y, int fractal_type);

// COLOR UTILS
int create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
unsigned char	get_t(int trgb);
unsigned char	get_r(int trgb);
unsigned char	get_g(int trgb);
unsigned char	get_b(int trgb);
